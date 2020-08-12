from matplotlib.widgets import RectangleSelector
import numpy as np
import matplotlib.pyplot as plt
import json
from glob import glob
import os
import pandas as pd
from datetime import datetime
import shutil

SEGMENT_ID_GENERATOR = iter(range(1000000))

RECORD_MOVE_DIR = None
REFERENCE_MOVE_DIR = None
ANNOTATION_SAVE_DIR = None
VALUE_DESCRIPTIONS = None


def str2id(s):
    return int.from_bytes(s.encode('utf-8'), 'little')


def shift_bit(data):
    data = data.astype(np.uint32) & 0x000000000001ffff
    return data


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
        toggle_selector.dict_segment_channel1.update(
            {'start': max(int(toggle_selector.RS.corners[0][0]), 0),
             'end': min(int(toggle_selector.RS.corners[0][2]), toggle_selector.length_channel1),
             'id': next(SEGMENT_ID_GENERATOR) + int(datetime.now().timestamp()),
             })
        toggle_selector.dict_segment_channel1.update(
            dict(toggle_selector.manual_info.drop(['file_name', 'creation_date'])))
        wear_category_name = 'wear' if 'person' in \
            toggle_selector.dict_segment_channel1.keys() else 'nonwear'
        for vd in VALUE_DESCRIPTIONS['wear_categories']:
            if wear_category_name == vd['name']:
                toggle_selector.dict_segment_channel1['wear_category_id'] = vd['id']
        toggle_selector.dict_segment_channel1['value_category_id'] = toggle_selector.value_category_id_channel1

        toggle_selector.dict_segment_channel2 = \
            toggle_selector.dict_segment_channel1.copy()
        toggle_selector.dict_segment_channel2['end'] = min(
            toggle_selector.dict_segment_channel2['end'],
            toggle_selector.length_channel2)
        toggle_selector.dict_segment_channel2['id'] = next(
            SEGMENT_ID_GENERATOR) + int(datetime.now().timestamp())
        toggle_selector.dict_segment_channel2['value_category_id'] = \
            toggle_selector.value_category_id_channel2

        print("x-> 保存!")
    if event.key in ['X', 'x']:
        json_dict = {'record': toggle_selector.dict_record,
                     'segment': toggle_selector.dict_segment_channel1}
        json_dict = json.dumps(json_dict)
        json_name = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
        json_name = json_name.replace(' ', '(') + ')_channel1.json'
        json_path = os.path.join(ANNOTATION_SAVE_DIR, json_name)
        with open(json_path, 'w') as f:
            f.write(json_dict)

        json_dict = {'record': toggle_selector.dict_record,
                     'segment': toggle_selector.dict_segment_channel2}
        json_dict = json.dumps(json_dict)
        json_name = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
        json_name = json_name.replace(' ', '(') + ')_channel2.json'
        json_path = os.path.join(ANNOTATION_SAVE_DIR, json_name)
        with open(json_path, 'w') as f2:
            f2.write(json_dict)


def annotate_segment(record_path, manual_info, toggle_selector):
    record = pd.read_csv(record_path, header=None,
                         error_bad_lines=False, warn_bad_lines=False, verbose=False)
    record[1] = shift_bit(record[1].values)
    record[2] = shift_bit(record[2].values)

    toggle_selector.value_category_id_channel1 = 154
    toggle_selector.length_channel1 = record[2].shape[0]
    channel1 = record[2]

    toggle_selector.value_category_id_channel2 = 151
    toggle_selector.length_channel2 = record[1].shape[0]
    channel2 = record[1]

    toggle_selector.manual_info = manual_info
    toggle_selector.dict_record = annotate_record(manual_info)

    toggle_selector.dict_segment_channel1 = {
        'record_id': toggle_selector.dict_record['id']}

    fig, (ax_channel1, ax_channel2) = plt.subplots(2, 1, sharex=True)
    ax_channel1.plot(range(channel1.shape[0]), channel1)
    ax_channel1.set_xlim(0, channel1.shape[0] - 1)
    ax_channel2.plot(range(channel2.shape[0]), channel2)
    ax_channel2.set_xlim(0, channel2.shape[0] - 1)

    # 将record汇总到records文件夹中，reference汇总到references文件夹中.
    record.to_csv(os.path.join(RECORD_MOVE_DIR,
                               manual_info['file_name']), header=None, index=None)
    src_reference_path = os.path.join(record_path.split(
        'records')[0] + 'references', manual_info['reference'])
    dst_reference_path = os.path.join(
        REFERENCE_MOVE_DIR, manual_info['reference'])
    shutil.copyfile(src_reference_path, dst_reference_path)

    toggle_selector.RS = RectangleSelector(ax_channel1, line_select_callback,
                                           drawtype='box', useblit=True,
                                           # don't use middle button
                                           button=[1, 3],
                                           minspanx=5, minspany=5,
                                           spancoords='pixels',
                                           interactive=True)

    plt.connect('key_press_event', toggle_selector)
    plt.title(record_path.split('/')[-1])
    plt.show()


def annotate_record(manual_info):
    return dict({'name': manual_info['file_name'],
                 'id': str2id(manual_info['file_name']),
                 'creation_date': manual_info['creation_date']})


RECORD_MOVE_DIR = '/Users/liuziyi/Documents/Lifesense/data/nonwear-check/R/results/records'
REFERENCE_MOVE_DIR = '/Users/liuziyi/Documents/Lifesense/data/nonwear-check/R/results/references'
ANNOTATION_SAVE_DIR = '/Users/liuziyi/Documents/Lifesense/data/nonwear-check/R/results/jsons'
with open('/Users/liuziyi/Documents/Lifesense/data/nonwear-check/R/raw/value_descriptions.json') as f:
    VALUE_DESCRIPTIONS = json.load(f)

record_paths = glob(
    '/Users/liuziyi/Documents/Lifesense/data/nonwear-check/R/raw/20200412/records/*.csv')
record_paths.sort()

manual_infos = pd.read_csv(
    '/Users/liuziyi/Documents/Lifesense/data/nonwear-check/R/raw/测试数据说明_汇总_R.csv')
manual_infos[manual_infos['file_name'].notnull()]

for rp in record_paths:
    manual_info = manual_infos[manual_infos['file_name']
                               == rp.split('/')[-1]].iloc[0]
    manual_info = manual_info[manual_info.notnull()]
    print(rp, manual_info)

    annotate_segment(rp, manual_info, toggle_selector)

    finish = input("继续下一个样本: y/n")
