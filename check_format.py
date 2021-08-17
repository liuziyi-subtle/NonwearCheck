import pandas as pd
from glob import glob
import os
import shutil

k_root_dir = "/Users/liuziyi/Desktop/Temp/439-temp"

# modify all file_name as  *.csv
# manual_info = pd.read_csv("./manual_info.csv")
# manual_info["file_name"] = manual_info["file_name"].map(
#     lambda x: x.split(".")[0] + ".csv")
# manual_info.to_csv("./manual_info_new.csv", encoding='utf_8_sig', index=None)

record_paths = glob(os.path.join(k_root_dir, "Records/*.csv"))
for rp in record_paths:
    record = pd.read_csv(rp, header=None, error_bad_lines=False,
                         warn_bad_lines=False, verbose=False)

    # 1-st row must contain at least 4 fields: value_id, x, y, z, timestamp.
    if 4 not in record.columns:
        record = pd.read_csv(rp, header=None, error_bad_lines=False,
                             warn_bad_lines=False, verbose=False, skiprows=1)
        if 4 not in record.columns:
            record = pd.read_csv(rp, header=None, error_bad_lines=False,
                                 warn_bad_lines=False, verbose=False, skiprows=2)
            if 4 not in record.columns:
                record = pd.read_csv(rp, header=None, error_bad_lines=False,
                                     warn_bad_lines=False, verbose=False, skiprows=3)
                if 4 not in record.columns:
                    record = pd.read_csv(rp, header=None, error_bad_lines=False,
                                         warn_bad_lines=False, verbose=False, skiprows=4)

    rp = rp.replace("Records", "Records-new")  # .replace(".dat", ".csv")
    record.to_csv(rp, index=None, header=None)
