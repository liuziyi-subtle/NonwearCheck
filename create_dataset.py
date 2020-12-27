# Copyright (c) 2020 Liu Ziyi

import argparse
import numpy as np
import os
import json
import pandas as pd
from datetime import datetime
import time
from scipy import signal

OBJECT_ID_GENERATOR = iter(range(10000000))


def parse_annotation(annotations, value_category_id):
    def sort_segments(segment_list):
        starts = [s["start"] for s in segment_list]
        sorted_starts = sorted(range(len(starts)), key=lambda k: starts[k])
        sorted_segment_list = [segment_list[k] for k in sorted_starts]
        return sorted_segment_list

    annotation_index = {}
    for segment_annotation in annotations['segment_annotations']:
        # filter out unwanted segments.
        # if segment_annotation["value_category_id"] != value_category_id:
        #     continue
        if value_category_id not in segment_annotation["value_category_id"]:
            continue

        record_id = segment_annotation['record_id']
        if record_id not in annotation_index:
            annotation_index[record_id] = []
        annotation_index[record_id].append(segment_annotation)

    # make sure segment annotations store in ascent order.
    for key, value in annotation_index.items():
        annotation_index[key] = sort_segments(value)

    return annotation_index


def segment2object(segment, object_length, overlap):
    objects = []
    for i in range(0, segment.shape[0] - object_length, overlap):
        object = segment.iloc[i:i+object_length, :].copy()
        object['id'] = next(OBJECT_ID_GENERATOR)
        objects.append(object)
    return objects


def create_object(record_annotation,
                  annotation_list,
                  value_category,
                  record_dir,
                  groundtruth_dir,
                  object_length,
                  target_fs,
                  preprocess_funcs=None,
                  target_id=None):
    # read mtk format record.
    record = pd.read_csv(os.path.join(record_dir, record_annotation['name']),
                         header=None, error_bad_lines=False)

    # downsample to target_fs
    record = record.iloc[::int(value_category["sample_rate"] / target_fs), :]

    # TODO: using one sos.
    if "acc" in value_category["value_type"]:
        record = record.loc[record[0] == value_category['id'], [1, 2, 3]]
        record.rename(columns={1: 'AccX', 2: 'AccY', 3: 'AccZ'}, inplace=True)

        # record['AccX'] = np.array(record['AccX'], np.int16) >> 6
        sos = signal.butter(4, [0.4, 4], "bandpass", fs=25, output='sos')
        record['AccX'] = signal.sosfilt(sos, record['AccX'])

        # record['AccY'] = np.array(record['AccY'], np.int16) >> 6
        sos = signal.butter(4, [0.4, 4], "bandpass", fs=25, output='sos')
        record['AccY'] = signal.sosfilt(sos, record['AccY'])

        # record['AccZ'] = np.array(record['AccZ'], np.int16) >> 6
        sos = signal.butter(4, [0.4, 4], "bandpass", fs=25, output='sos')
        record['AccZ'] = signal.sosfilt(sos, record['AccZ'])

        record['Resultant'] = np.power(
            record['AccX'], 2) + np.power(record['AccY'], 2) + np.power(record['AccZ'], 2)
    else:
        record = record.loc[record[0] ==
                            value_category['id'], [1]].astype(np.int32)
        record = record.applymap(lambda x: x & 0xffffff - 2 ** 23)
        record.rename(columns={1: value_category["value_type"]}, inplace=True)
        sos = signal.butter(4, [0.4, 4], "bandpass", fs=25, output='sos')
        record[value_category["value_type"]] = signal.sosfilt(
            sos, record[value_category["value_type"]])

    object_list = []
    for segment_annotation in annotation_list:
        start = int(segment_annotation['start'] * target_fs)
        end = int(segment_annotation['end'] * target_fs)
        segment = record.iloc[start:end].copy()
        if target_id:
            segment[target_id] = segment_annotation[target_id]
        segment['record_id'] = str(segment_annotation['record_id'])
        segment['segment_id'] = segment_annotation['id']
        # record to segments with overlapping.
        objects = segment2object(segment, object_length, target_fs)
        # downsample groundtruth and get mean from each 8 secconds.
        ground_truth = pd.read_csv(os.path.join(
            groundtruth_dir, segment_annotation["groundtruth_name"]))
        ground_truth = ground_truth.iloc[start:end]
        ground_truth = ground_truth.iloc[::target_fs, :].values
        ground_truth = [ground_truth[i: i + 8]
                        for i in range(len(ground_truth) - 8)]
        # objects and ground_truth must have the same length.
        min_length = np.min([len(ground_truth), len(objects)])
        print(min_length, len(ground_truth), len(objects))
        ground_truth = ground_truth[:min_length]
        objects = objects[:min_length]

        for object, gt in zip(objects, ground_truth):
            # print(gt)
            pre_hrs = np.array(gt[:7]).T
            object["prev_hrs"] = np.repeat(
                pre_hrs, object_length, axis=0).tolist()
            hr = np.array([gt[7]] * object_length).reshape(object_length, 1)
            object["hr"] = hr
        object_list.extend(objects)
    return object_list


"""
usage:
python3 create_datasets.py --annotations_path /Users/liuziyi/Documents/Lifesense/Data/HeartRate/GoodixDemoWatch/Results/annotations.json \
                           --value_category_id 2 \
                           --record_dir /Users/liuziyi/Documents/Lifesense/Data/HeartRate/GoodixDemoWatch/Results/RecordsMTKFormat \
                           --groundtruth_dir /Users/liuziyi/Documents/Lifesense/Data/HeartRate/GoodixDemoWatch/Results/GroundTruthMTKFormat \
                           --object_length 200 \
                           --save_path /Users/liuziyi/Documents/Lifesense/Data/HeartRate/GoodixDemoWatch/Results/df_object_acc.csv
python3 create_datasets.py --annotations_path /data/data/HeartRate/GoodixDemoWatch/Results/annotations.json \
                           --value_category_id 131 \
                           --record_dir /data/data/HeartRate/GoodixDemoWatch/Results/RecordsMTKFormat \
                           --groundtruth_dir /data/data/HeartRate/GoodixDemoWatch/Results/GroundTruthMTKFormat \
                           --object_length 200 \
                           --save_path /data/data/HeartRate/GoodixDemoWatch/Results/df_object_ppg.csv
"""

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--annotations_path', type=str, help='')
    parser.add_argument('--value_category_id', type=int, help='')
    parser.add_argument('--record_dir', type=str, help='')
    parser.add_argument('--groundtruth_dir', type=str, help='')
    parser.add_argument('--object_length', type=int, default=256, help='')
    parser.add_argument('--preprocess_funcs', type=str, default=None, help='')
    parser.add_argument('--save_path', type=str, help='')
    args = parser.parse_args()

    with open(args.annotations_path, 'r') as f:
        annotations = json.load(f)

    # example: {record_id: [segment_annotation, segment_annotation, ...], ...}
    annotation_index = parse_annotation(annotations, args.value_category_id)

    # all record annotations.
    record_annotations = annotations['record_annotations']

    # get value_category of which id be the same with args.value_category_id.
    for vc in annotations['value_categories']:
        if vc["id"] == args.value_category_id:
            value_category = vc
            break

    # get objects from each record.
    object_list = []
    for record_annotation in record_annotations:
        if record_annotation['id'] not in annotation_index:
            continue

        # segment annotations in one record.
        annotation_list = annotation_index[record_annotation['id']]
        if len(annotation_list) > 1:
            print(annotation_list)

        objects = create_object(record_annotation,
                                annotation_list,
                                value_category,
                                args.record_dir,
                                args.groundtruth_dir,
                                object_length=args.object_length,
                                target_fs=25,
                                preprocess_funcs=args.preprocess_funcs)
        object_list.extend(objects)

    df_objects = pd.concat(object_list)
    print(df_objects)
    df_objects.to_csv(args.save_path, index=False)
    print(args.save_path)
    print("Done.")
