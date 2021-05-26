# -*- coding: utf-8

from matplotlib.widgets import RectangleSelector
import numpy as np
import matplotlib.pyplot as plt
import json
from glob import glob
import os
import pandas as pd
from datetime import datetime
import shutil


def str2id(s):
    return int.from_bytes(s.encode('utf-8'), 'little')


def line_select_callback(eclick, erelease):
    'eclick and erelease are the press and release events'
    x1, y1 = eclick.xdata, eclick.ydata
    x2, y2 = erelease.xdata, erelease.ydata
    print("(%3.2f, %3.2f) --> (%3.2f, %3.2f)" % (x1, y1, x2, y2))
    print(" The button you used were: %s %s" %
          (eclick.button, erelease.button))
    return eclick, erelease


def toggle_selector(event):
    print(' Key pressed.')
    if event.key in ['Q', 'q'] and toggle_selector.RS.active:
        print(' RectangleSelector deactivated.')
        toggle_selector.RS.set_active(False)
    if event.key in ['A', 'a'] and not toggle_selector.RS.active:
        print(' RectangleSelector activated.')
        toggle_selector.RS.set_active(True)
    if event.key in ['E', 'e']:
        # segment start
        toggle_selector.dict_segment['start'] = int(
            toggle_selector.RS.corners[0][0] /
            toggle_selector.annotation_sample_rate)
        toggle_selector.dict_segment['start'] = max(
            toggle_selector.dict_segment['start'], 0)

        # segment end
        toggle_selector.dict_segment['end'] = int(
            toggle_selector.RS.corners[0][2] /
            toggle_selector.annotation_sample_rate)
        toggle_selector.dict_segment['end'] = min(
            toggle_selector.dict_segment['end'], toggle_selector.length)

        # segment_id
        toggle_selector.dict_segment['id'] = next(k_segment_id_generator)

        toggle_selector.dict_segment.update(
            dict(toggle_selector.manual_info.drop(['file_name',
                                                   'creation_date'])))
        # value_category_id - [131, 2]
        toggle_selector.dict_segment['value_category_id'] = toggle_selector.value_category_id
        # wear_category_id
        wear_category_id = 0 if "person" in toggle_selector.dict_segment.keys() else 1
        toggle_selector.dict_segment['wear_category_id'] = wear_category_id
        # # groundtruth
        # toggle_selector.dict_segment['groundtruth_name'] = toggle_selector.groundtruth_name
        # # comparison_hr
        # toggle_selector.dict_segment['comparison_hr_name'] = toggle_selector.comparison_hr_name

        print("x-> 保存!")
    if event.key in ['X', 'x']:
        json_dict = {'record': toggle_selector.dict_record,
                     'segment': toggle_selector.dict_segment}
        print(json_dict)
        if 'age' in json_dict["segment"]:
            json_dict["segment"]['age'] = int(json_dict["segment"]['age'])
        json_dict = json.dumps(json_dict, ensure_ascii=False)
        json_name = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
        json_name = json_name.replace(' ', '(') + ')_channel1.json'
        json_path = os.path.join(k_json_dir, json_name)
        with open(json_path, 'w') as f:
            f.write(json_dict)


def annotate_segment(record_path, toggle_selector, manual_info):
    record = pd.read_csv(record_path, header=None,
                         error_bad_lines=False, warn_bad_lines=False,
                         verbose=False)

    record = record.loc[record[0] != "APP_MSG"]
    record[0] = record[0].astype(np.int32)

    ppg_sample_rate = 50  # 本次数据green和ir的采样率均为50Hz.
    acc_sample_rate = 25
    value_category_id = [1, 2, 4]
    toggle_selector.annotation_sample_rate = ppg_sample_rate
    toggle_selector.value_category_id = value_category_id

    # Plot
    gr_data_id = 1  # green
    ir_data_id = 4  # ir
    acc_data_id = 2
    ppg_gr = record.loc[record[0] == gr_data_id, 1].values.astype(np.int32)
    ppg_ir = record.loc[record[0] == ir_data_id, 1].values.astype(np.int32)
    acc = record.loc[record[0] == acc_data_id,
                     [1, 2, 3]].values.astype(np.int16)

    toggle_selector.manual_info = manual_info
    toggle_selector.dict_record = annotate_record(manual_info)
    min_length = min(
        int(ppg_gr.shape[0] / ppg_sample_rate),
        int(ppg_ir.shape[0] / ppg_sample_rate),
        int(acc.shape[0] / acc_sample_rate))
    toggle_selector.length = min_length
    toggle_selector.dict_segment = {
        'record_id': toggle_selector.dict_record['id']}

    fig, (ax_ppg_gr, ax_ppg_ir, ax_acc) = plt.subplots(3, 1)

    ax_ppg_gr.plot(range(ppg_gr.shape[0]), ppg_gr)
    ax_ppg_gr.set_xlim(0, ppg_gr.shape[0] - 1)
    ax_ppg_gr.set_title(record_path.split('/')[-1])

    ax_ppg_ir.plot(range(ppg_ir.shape[0]), ppg_ir)
    ax_ppg_ir.set_xlim(0, ppg_ir.shape[0] - 1)

    ax_acc.plot(range(acc.shape[0]), acc)
    ax_acc.set_xlim(0, acc.shape[0] - 1)
    ax_acc.legend(['AccX', 'AccY', 'AccZ'])

    toggle_selector.RS = RectangleSelector(ax_ppg_gr, line_select_callback,
                                           drawtype='box', useblit=True,
                                           # don't use middle button
                                           button=[1, 3],
                                           minspanx=5, minspany=5,
                                           spancoords='pixels',
                                           interactive=True)

    plt.connect('key_press_event', toggle_selector)
    # plt.title(record_path.split('/')[-1])
    plt.show()


def annotate_record(manual_info):
    return dict({'name': manual_info['file_name'],
                 'id': next(k_record_id_generator),  # 程序运行的起始时间+生成器.
                 'creation_date': manual_info['creation_date']})


""" Settings
"""
generator_start = int(datetime.now().timestamp() + str2id("record"))
k_record_id_generator = iter(range(generator_start, generator_start + 100000))
generator_start = int(datetime.now().timestamp() + str2id("segment"))
k_segment_id_generator = iter(range(generator_start, generator_start + 100000))

k_root_dir = "/Users/liuziyi/Documents/Lifesense/Data/NonwearCheck/456/Results"
k_record_dir = os.path.join(k_root_dir, "Records")
k_reference_dir = os.path.join(k_root_dir, "References")
# k_groundtruth_dir = os.path.join(k_root_dir, "GroundTruthMTKFormat")
# k_comparison_hr_dir = os.path.join(k_root_dir, "ComparisonHRMTKFormat")
k_json_dir = os.path.join(k_root_dir, "Jsons")

with open(os.path.join(k_root_dir, "value_descriptions.json")) as f:
    k_value_descriptions = json.load(f)

record_paths = glob(os.path.join(k_record_dir, "*.dat"))
record_paths.sort()

manual_infos = pd.read_csv(os.path.join(k_root_dir, "manual_info.csv"))

print(record_paths)

for record_path in record_paths:
    print(record_path)

    manual_info = manual_infos[manual_infos['file_name']
                               == record_path.split('/')[-1]].iloc[0]
    manual_info = manual_info[manual_info.notnull()]

    # print(record_path, manual_infos.shape)

    annotate_segment(record_path, toggle_selector, manual_info)

    finish = input("继续下一个样本: y/n")
