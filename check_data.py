from matplotlib.widgets import RectangleSelector
import numpy as np
import matplotlib.pyplot as plt
import json
from glob import glob
import os
import pandas as pd
from datetime import datetime
import shutil
from scipy import signal

record_paths = glob('/Users/liuziyi/R/raw/20200408/records/*.csv')


def lp(record):
    sos = signal.butter(8, 10, 'low', fs=25, output='sos')
    record = signal.sosfilt(sos, record)
    # record = record[200:]
    return record


for rp in record_paths:
    print(rp)
    record = pd.read_csv(rp, header=None)
    fig, (ax_1, ax_2) = plt.subplots(2, 1, sharex=True)
    ax_1.plot(range(record.shape[0]), lp(record[1].values.flatten()))
    ax_2.plot(range(record.shape[0]), lp(record[2].values.flatten()))
    plt.show()
    finish = input("继续下一个样本: y/n")
