from matplotlib.widgets import RectangleSelector
import numpy as np
import matplotlib.pyplot as plt
import json
from glob import glob
import os
import pandas as pd
from datetime import datetime
import shutil
from scipy import signal, fft

# # record_paths = glob('/Users/liuziyi/R/raw/20200408/records/*.csv')
prefix = '/Users/liuziyi/Documents/Lifesense/data/nonwear-check/O/results/records/'
records_paths = ['20200413_blackcloth_001.csv',
                 'weartest_14_20200223.csv',
                 'weartest_36_20200224.csv',
                 '20200416_syn_2.csv',
                 '20200413_bluesurface_002.csv',
                 '20200413_bluesurface_001.csv',
                 'weartest_19_20200312.csv',
                 '20200416_hsx_2.csv',
                 '20200413_blackcloth_002.csv',
                 '20200413_bluesurface_003.csv',
                 'weartest_2_20200223.csv',
                 '20200413_skyblue_surface_003.csv',
                 '20200413_blue_surface_001.csv',
                 'weartest_7_20200305.csv',
                 '20200416_xyk_2.csv',
                 'weartest_6_20200319.csv',
                 'weartest_10_20200302.csv',
                 'weartest_21_20200223.csv',
                 '20200420_white_glass_2.csv',
                 'weartest_4_20200319.csv',
                 '20200420_white_glass_1.csv',
                 '20200413_blue_surface_paper_001.csv']
records_paths = map(lambda x: prefix + x, records_paths)


# def lp(record):
#     sos = signal.butter(8, 10, 'low', fs=25, output='sos')
#     record = signal.sosfilt(sos, record)
#     # record = record[200:]
#     return record


# for rp in records_paths:
#     print(rp)
#     record = pd.read_csv(rp, header=None, error_bad_lines=False)
#     ppg_g = record[record[0] == 1][1].values.flatten()
#     spectrum = fft.rfft(ppg_g)
#     # ppg_ir = record[record[0] == 4][1].values.flatten()
#     fig, (ax_1, ax_2) = plt.subplots(2, 1, sharex=True)
#     print(ppg_g)
#     ax_1.plot(ppg_g)
#     ax_2.plot(spectrum)
#     plt.show()
#     finish = input("继续下一个样本: y/n")


def plot_spectrum(x, save_path):
    y = abs(fft.rfft(x))
    fig, ax = plt.subplots(1, 1, sharex=True)
    ax.plot(y, 'o')
    ax.set_ylim(0, 200)
    plt.savefig(save_path)
    plt.close()


df_features = pd.read_csv('./features_ppg-g_scale.csv', index_col=None)

segment_ids = [1586843769, 1586843563, 1586843825]

columns = [c for c in df_features.columns if (
    'ppg__fft' in c) and ('abs' in c)]

for segment_id in segment_ids:
    df = df_features[df_features['segment_id'] == segment_id]
    features = df_features[columns].values
    i = 0
    for f in features:
        fig, ax = plt.subplots(1, 1, sharex=True)
        ax.plot(f[1:33], 'o')
        ax.set_ylim(0, 200)
        # plt.show()
        plt.savefig('./bad/' + str(segment_id) + '_' + str(i) + '.png')
        plt.close()
        i += 1
        # finish = input("继续下一个样本: y/n")
