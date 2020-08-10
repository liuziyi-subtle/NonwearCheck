import numpy as np
import os
import json
import pandas as pd
from datetime import datetime
import time
from scipy import signal


object_id_iter = iter(range(10000000))


# def resample(record):
#     n_sample = int(record.shape[0] / 4)
#     record = record.iloc[::4, :]
#     return record


def resample(record):
    '''简单降采样
       TODO: 需要基于最小公倍数作采样
    '''
    record = record.iloc[::2, :]
    return record


def hp(record):
    sos = signal.butter(4, 0.4, 'high', fs=25, output='sos')
    record['ppg'] = signal.sosfilt(sos, record['ppg'])
    record = record[200:]
    return record


def log_transform(record):
    # print('before log_transform: ', list(record['ppg'][1000:1064]))
    record['ppg'] = np.around(np.log2(np.abs(record['ppg']) + 1), decimals=6)
    # print('after log_transform: ', list(record['ppg'][1000:1064]))
    return record


def scale(data):
    data = (data - 5000000) / 1000.0
    # data = (data - 5000000) / 256
    return data


preprocess_func_map = {'resample': resample,
                       'hp': hp,
                       'log_transform': log_transform,
                       'scale': scale}


def local2utc(localtime):
    localtime = datetime.strptime(localtime, "%Y-%m-%d %H:%M:%S")
    utc = time.mktime(localtime.timetuple())
    return utc


def parse_annotation(annotations, value_category_ids=None, face_to_list=None, color_list=None):
    ''' TODO: 假如多个检索条件的联合判断，筛选出需要的annotations.
    '''
    annotation_index = {}

    # record_id: segment键值对
    for segment_annotation in annotations['segment_annotations']:
        condition_1, condition_2, condition_3 = False, False, False
        if segment_annotation['value_category_id'] in value_category_ids:
            condition_1 = True
        if 'face_to' in segment_annotation.keys():
            if segment_annotation['face_to'] in face_to_list:
                condition_2 = True
        if 'color' in segment_annotation.keys():
            if segment_annotation['color'] in color_list:
                condition_3 = True
        # if segment_annotation['value_category_id'] in value_category_ids:
        if condition_1 and (condition_2 or condition_3):
            record_id = segment_annotation['record_id']
            if record_id not in annotation_index:
                annotation_index[record_id] = []
            annotation_index[record_id].append(segment_annotation)
    return annotation_index


def replace_timestamp(timestamp):
    return timestamp.replace('T', ' ').split('.')[0]


def segment2object(segment, object_length):
    objects = []
    # for i in range(0, segment.shape[0] - object_length, int(object_length / 2)):
    for i in range(0, segment.shape[0] - object_length, int(object_length)):
        object = segment.iloc[i:i+object_length, :].copy()
        # print(object)
        # object = precess_func(object)
        # object['ppg'] = object['ppg'] - object['ppg'].mean()
        # object.rename(columns={'id': 'segment_id'}, inplace=True)
        object['id'] = next(object_id_iter)
        objects.append(object)
    # objects = process_func(objects)
    return objects


def create_object(record_annotation,
                  annotation_list,
                  value_categories,
                  record_dir,
                  object_length=256,
                  target_fs=25,
                  preprocess_func_s=None):
    for value_category in value_categories:
        if value_category['id'] == annotation_list[0]['value_category_id']:
            break
    record = pd.read_csv(os.path.join(record_dir, record_annotation['name']),
                         header=None, error_bad_lines=False)
    record = record[record[0] == value_category['id']]
    # print(record)
    record.rename(columns={1: 'ppg'}, inplace=True)
    record = record[['ppg']]
    # print(record.columns)
    # record = record['ppg']

    # resample
    sample_step = int(value_category['sample_rate'] / target_fs)
    # record = record[::sample_step]

    # preprocess
    if preprocess_func_s:
        print(preprocess_func_s)
        for pfs in preprocess_func_s.split(','):
            record['ppg'] = preprocess_func_map[pfs](record['ppg'].values)

    object_list = []
    for segment_annotation in annotation_list:
        start = int(segment_annotation['start'])
        end = int(segment_annotation['end'])
        segment = record.iloc[start:end].copy()
        segment['wear_category_id'] = segment_annotation['wear_category_id']
        segment['segment_id'] = segment_annotation['id']
        # segment = segment[::sample_step]
        cut_start = 500
        cut_end = len(segment) - 500
        segment = segment[cut_start:cut_end:sample_step]
        objects = segment2object(segment, object_length)
        object_list.extend(objects)
    return object_list


if __name__ == '__main__':
    '''
    usage:
    python3 ./create_dataset.py --annotations_path /data/workspace/data/nonwear-check/O/results/annotations.json \
                                --record_dir /data/workspace/data/nonwear-check/O/results/records \
                                --object_length 128 \
                                --preprocess_func_s scale \
                                --save_path /data/workspace/data/nonwear-check/O/results/objects__ppg-g_scale.csv
    python3 ./create_dataset.py --annotations_path /data/workspace/data/nonwear-check/O/results/annotations.json \
                                --record_dir /data/workspace/data/nonwear-check/O/results/records \
                                --object_length 128 \
                                --save_path /data/workspace/data/nonwear-check/O/results/objects__ppg-g__object_length_128.csv
<<<<<<< HEAD
    python3 ./create_dataset.py --annotations_path /data/data/nonwear-check/O/results/annotations.json \
                                --record_dir /data/data/nonwear-check/O/results/records \
                                --object_length 24 \
                                --save_path /data/data/nonwear-check/O/results/objects__ppg-g__object_length_24.csv
=======
    python3 ./create_dataset.py --annotations_path /data-temp/data/nonwear-check/O/results/annotations.json \
                                --record_dir /data-temp/data/nonwear-check/O/results/records \
                                --object_length 36 \
                                --save_path /data-temp/data/nonwear-check/O/results/objects__ppg-g__object_length_36__cut_500.csv
>>>>>>> ed2ff8c3ada47cc26d09150e35210f331d246c89
    '''
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument('--annotations_path', type=str, help='')
    parser.add_argument('--record_dir', type=str, help='')
    parser.add_argument('--object_length', type=int, default=128, help='')
    parser.add_argument('--preprocess_func_s', type=str, default=None, help='')
    parser.add_argument('--save_path', type=str, help='')
    args = parser.parse_args()

    with open(args.annotations_path, 'r') as f:
        annotations = json.load(f)

    annotation_index = parse_annotation(
        annotations, value_category_ids=[1, 131], face_to_list=['air'], color_list=['p4', 'p5', 'p6'])  # [1, 131]
    record_annotations = annotations['record_annotations']

    object_list = []
    for record_annotation in record_annotations:
        if record_annotation['id'] not in annotation_index:
            continue
        annotation_list = annotation_index[record_annotation['id']]
        objects = create_object(
            record_annotation,
            annotation_list,
            annotations['value_categories'],
            args.record_dir,
            object_length=args.object_length,
            target_fs=25,
            preprocess_func_s=args.preprocess_func_s)
        object_list.extend(objects)
    df_objects = pd.concat(object_list)
    df_objects.to_csv(args.save_path, index=False)
    print("Done.")
