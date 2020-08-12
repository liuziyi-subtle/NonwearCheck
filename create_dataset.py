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
    return data


preprocess_func_map = {'resample': resample,
                       'hp': hp,
                       'log_transform': log_transform,
                       'scale': scale}


def local2utc(localtime):
    localtime = datetime.strptime(localtime, "%Y-%m-%d %H:%M:%S")
    utc = time.mktime(localtime.timetuple())
    return utc


def parse_annotation(annotations, value_category_ids=None):
    annotation_index = {}
    # record_id: segment键值对
    for segment_annotation in annotations['segment_annotations']:
        if segment_annotation['value_category_id'] in value_category_ids:
            record_id = segment_annotation['record_id']
            if record_id not in annotation_index:
                annotation_index[record_id] = []
            annotation_index[record_id].append(segment_annotation)
    return annotation_index


def replace_timestamp(timestamp):
    return timestamp.replace('T', ' ').split('.')[0]


def segment2object(segment, object_length):
    objects = []
    for i in range(0, segment.shape[0] - object_length, int(object_length / 2)):
        object = segment.iloc[i:i+object_length, :].copy()
        # object.rename(columns={'id': 'segment_id'}, inplace=True)
        object['id'] = next(object_id_iter)
        objects.append(object)
    return objects


def create_object(record_annotation,
                  annotation_list,
                  value_categories,
                  record_dir,
                  object_length=256,
                  preprocess_func_s=None):
    for value_category in value_categories:
        if value_category['id'] == annotation_list[0]['value_category_id']:
            break
    record = pd.read_csv(os.path.join(record_dir, record_annotation['name']),
                         header=None, index_col=0, error_bad_lines=False)
    record = record[150:]
    if value_category['value_type'] == 'ppg-g':
        record = record[[1]]
        record.rename(columns={1: 'ppg'}, inplace=True)
    else:
        record = record[[2]]
        record.rename(columns={2: 'ppg'}, inplace=True)
    # record.rename(columns={2: 'ppg'}, inplace=True)
    record = record[['ppg']]
    # print(record.columns)
    # record = record['ppg']

    # preprocess
    if preprocess_func_s:
        print(preprocess_func_s)
        for pfs in preprocess_func_s.split(','):
            record['ppg'] = preprocess_func_map[pfs](record.values)

    object_list = []
    for segment_annotation in annotation_list:
        start = int(segment_annotation['start'])
        end = int(segment_annotation['end'])
        segment = record.iloc[start:end].copy()
        segment['wear_category_id'] = segment_annotation['wear_category_id']
        segment['segment_id'] = segment_annotation['id']
        objects = segment2object(segment, object_length)
        object_list.extend(objects)
    return object_list


if __name__ == '__main__':
    '''
    usage:
    python3 ./create_dataset.py --annotation_path /data/workspace/data/annotations.json \
                                --record_dir /data/workspace/data/records \
                                --save_path /data/workspace/data/objects.csv
    python3 ./create_dataset.py --annotation_path /data/workspace/data/annotations.json \
                                --record_dir /data/workspace/data/records \
                                --preprocess_func_s split_body_gravity \
                                --save_path /data/workspace/data/objects.csv
    python3 ./create_dataset.py --annotation_path /data/workspace/data/annotations.json \
                                --record_dir /data/workspace/data/records \
                                --preprocess_func_s resample,split_body_gravity \
                                --object_length 64
                                --save_path /data/workspace/data/objects.csv
    python3 ./create_dataset.py --annotation_path /data/workspace/data/annotations.json \
                            --record_dir /data/workspace/data/records \
                            --preprocess_func_s resample \
                            --object_length 64 \
                            --save_path /data/workspace/data/objects_25hz.csv
    python3 ./create_dataset.py --annotation_path /Users/liuziyi/Workspace/data/annotations.json \
                            --record_dir /Users/liuziyi/Workspace/data/records \
                            --object_length 64 \
                            --save_path /Users/liuziyi/Workspace/data/objects.csv
    python3 ./create_dataset.py --annotation_path /data/workspace/data/annotations.json \
                            --record_dir /data/workspace/data/records \
                            --object_length 64 \
                            --preprocess_func_s hp \
                            --save_path /data/workspace/data/objects_hp_0.4hz.csv
    python3 ./create_dataset.py --annotation_path /data/workspace/data/annotations.json \
                            --record_dir /data/workspace/data/records \
                            --object_length 64 \
                            --preprocess_func_s hp \
                            --save_path /data/workspace/data/objects_ir_hp_0.4hz.csv
    python3 ./create_dataset.py --annotation_path /data/workspace/data/annotations.json \
                            --record_dir /data/workspace/data/records \
                            --object_length 64 \
                            --preprocess_func_s resample,hp \
                            --save_path /data/workspace/data/objects_ir-resample_25hz-hp_0.4hz.csv
    python3 ./create_dataset.py --annotation_path /data/workspace/data/annotations.json \
                            --record_dir /data/workspace/data/records \
                            --object_length 64 \
                            --preprocess_func_s resample \
                            --save_path /data/workspace/data/objects_ir-resample_25hz.csv
    python3 ./create_dataset.py --annotation_path /data/workspace/data/annotations.json \
                        --record_dir /data/workspace/data/records \
                        --object_length 64 \
                        --preprocess_func_s resample,log_transform \
                        --save_path /data/workspace/data/objects_ir-resample_25hz_log2.csv
    python3 ./create_dataset.py --annotation_path /data/workspace/data/annotations.json \
                            --record_dir /data/workspace/data/records \
                            --object_length 64 \
                            --preprocess_func_s resample,scale \
                            --save_path /data/workspace/data/objects_ir-resample_25hz_scale.csv
    python3 ./create_dataset.py --annotation_path /data/workspace/data/annotations.json \
                            --record_dir /data/workspace/data/records \
                            --object_length 64 \
                            --preprocess_func_s scale \
                            --save_path /data/workspace/data/objects_green-scale.csv
    python3 ./create_dataset.py --annotation_path /data/workspace/data/annotations-R.json \
                        --record_dir /data/workspace/data/records-R \
                        --object_length 64 \
                        --preprocess_func_s scale \
                        --save_path /data/workspace/data/objects_R-scale.csv
    python3 ./create_dataset.py --annotations_path /data/workspace/data/nonwear-check/O/results/annotations.json \
                                --value_descriptions_path /data/workspace/data/nonwear-check/O/raw/value_descriptions.json \
                                --record_dir /data/workspace/data/nonwear-check/O/results/records \
                                --object_length 64 \
                                --preprocess_func_s scale \
                                --save_path /data/workspace/data/nonwear-check/O/results/objects_ppg-g_scale.csv
    python3 ./create_dataset.py --annotations_path /data/workspace/data/nonwear-check/R/results/annotations.json \
                                --record_dir /data/workspace/data/nonwear-check/R/results/records \
                                --object_length 64 \
                                --save_path /data/workspace/data/nonwear-check/R/results/objects_ppg-g_scale.csv
    python3 ./create_dataset.py --annotations_path /data/workspace/data/nonwear-check/R/results/annotations.json \
                                --record_dir /data/workspace/data/nonwear-check/R/results/records \
                                --object_length 64 \
                                --save_path /data/workspace/data/nonwear-check/R/results/objects_ppg-ir_scale.csv
    '''
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument('--annotations_path', type=str, help='')
    # parser.add_argument('--value_descriptions_path', type=str, help='')
    parser.add_argument('--record_dir', type=str, help='')
    parser.add_argument('--object_length', type=int, default=256, help='')
    parser.add_argument('--preprocess_func_s', type=str, default=None, help='')
    parser.add_argument('--save_path', type=str, help='')
    args = parser.parse_args()

    with open(args.annotations_path, 'r') as f:
        annotations = json.load(f)

    annotation_index = parse_annotation(
        annotations, value_category_ids=[154])
    record_annotations = annotations['record_annotations']

    value_categories = annotations['value_categories']

    object_list = []
    for record_annotation in record_annotations:
        if record_annotation['id'] not in annotation_index:
            continue
        annotation_list = annotation_index[record_annotation['id']]
        objects = create_object(
            record_annotation,
            annotation_list,
            value_categories,
            args.record_dir,
            object_length=args.object_length,
            # target_fs=25,
            preprocess_func_s=args.preprocess_func_s)
        object_list.extend(objects)
    df_objects = pd.concat(object_list)
    df_objects.to_csv(args.save_path, index=False)
    print("Done.")
