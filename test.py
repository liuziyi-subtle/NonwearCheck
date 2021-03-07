# from tsfresh.feature_extraction.feature_calculators import percentage_of_reoccurring_values_to_all_values
from glob import glob
import os
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

# a = np.array([45906, 45881, 45858, 45832, 45818, 45781, 45734, 45777, 45846,
#               45877, 45892, 45908, 45912, 45898, 45895, 45897, 45908, 45909,
#               45916, 45929, 45921, 45880, 45800, 45779, 45887, 45958, 46029,
#               46096, 46140, 46203, 46274, 46312, 46330, 46350, 46357, 46378,
#               46373, 46380, 46367, 46343, 46340, 46341, 46347, 46353, 46349,
#               46330, 46307, 46287, 46253, 46223, 46204, 46172, 46150, 46113,
#               46064, 46070, 46081, 46076, 46074, 46071, 46060, 46042, 46035,
#               46015, 45993, 45965, 45944, 45921, 45902, 45891, 45858, 45843,
#               45857, 45859, 45854, 45857, 45861, 45860, 45872, 45871, 45883,
#               45892, 45870, 45886, 45885, 45890, 45879, 45846, 45838, 45849,
#               45861, 45847, 45814, 45786, 45768, 45773, 45751, 45743, 45736,
#               45748, 45751, 45748, 45727, 45699, 45656, 45632, 45661, 45736,
#               45769, 45786, 45813, 45824, 45825, 45850, 45859, 45868, 45852,
#               45834, 45807, 45786, 45772, 45798, 45827, 45842, 45866, 45897,
#               45918, 45931])

# b = percentage_of_reoccurring_values_to_all_values(a)
# print(b)


def preprocess_t(sig):
    th = 500
    ref = sig[0]
    sub = 0
    for i in range(1, len(sig)):
        if abs(sig[i] - ref) > th:
            sub = sub + (sig[i] - ref)
        ref = sig[i]
        sig[i] = sig[i] - sub
    return sig


record = pd.read_csv(
    "/Users/liuziyi/Documents/Lifesense/Data/NonwearCheck/450/Results/Records/20201129001.csv", header=None,
    error_bad_lines=False, warn_bad_lines=False,
    verbose=False)

record = record.loc[record[0] != "APP_MSG"]
record[0] = record[0].astype(np.int32)

ppg = record.loc[record[0] == 161, 1].values
ppg = np.array(ppg, dtype=np.uint16)

ppg_t = preprocess_t(ppg.copy())

np.savetxt("./test_data.txt", ppg, fmt='%d,', delimiter=', ')

fig, axes = plt.subplots(2, 1, figsize=(15, 8))
axes[0].plot(ppg)
axes[1].plot(ppg_t)
plt.show()
print(1)


# k_root_dir = "/Users/liuziyi/Documents/Lifesense/Data/NonwearCheck/450/Results"
# k_record_dir = os.path.join(k_root_dir, "Records")
# record_paths = glob(os.path.join(k_record_dir, "*.csv"))
# record_paths.sort()

# manual_infos = pd.read_csv(os.path.join(k_root_dir, "manual_info.csv"))
# manual_infos = manual_infos.loc[(manual_infos["face_to"]
#                                  == "skin") & (manual_infos["light"] == "green"), "file_name"]

# print(manual_infos)

# diff = []
# for mi in manual_infos.values:
#     record = pd.read_csv(os.path.join(k_record_dir, mi), header=None,
#                          error_bad_lines=False, warn_bad_lines=False,
#                          verbose=False)
#     record = record.loc[record[0] != "APP_MSG"]
#     record[0] = record[0].astype(np.int32)
#     ppg = record.loc[record[0] == 161, 1].values
#     diff.extend(list(ppg[1:] - ppg[:-1]))

# print("aaa")
