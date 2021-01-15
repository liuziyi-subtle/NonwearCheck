import json
from random import randint, sample
import pandas as pd
import numpy as np
import pickle
import seaborn as sns
import matplotlib.pyplot as plt

from sklearn.tree import DecisionTreeClassifier
from sklearn.metrics import classification_report
from sklearn.linear_model import LogisticRegression
from sklearn.preprocessing import StandardScaler
from sklearn.pipeline import make_pipeline
from sklearn.utils import shuffle
from sklearn.svm import SVC
from sklearn.metrics import confusion_matrix
from sklearn.metrics import accuracy_score
from sklearn.metrics import confusion_matrix
from sklearn.preprocessing import MinMaxScaler
from sklearn.model_selection import KFold

import xgboost
import treelite

import datetime
import time

import datatable as dt

sns.set(style="ticks")
np.set_printoptions(suppress=True)

pd.set_option('display.max_rows', 150)

df_feats = dt.fread(
    "/data/data/NonwearCheck/450/Results/df_feat_ppg_ir.csv").to_pandas()
df_feats = df_feats.iloc[shuffle(range(len(df_feats)), random_state=0), :]

df_objects = dt.fread(
    "/data/data/NonwearCheck/450/Results/df_object_ppg_ir.csv").to_pandas()

feats_cols = [c for c in df_feats.columns if "ppg" in c]
target_col = "wear_category_id"

X_cols = feats_cols
y_col = target_col

X_train, y_train = df_feats.loc[:,
                                X_cols].values, df_feats.loc[:, y_col].values
X_test,  y_test = df_feats.loc[:, X_cols].values, df_feats.loc[:, y_col].values

shuffle_index = shuffle(range(len(X_train)), random_state=0)
X_train = X_train[shuffle_index, :]
y_train = y_train[shuffle_index]

scaler = MinMaxScaler()
X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)

D_train = xgboost.DMatrix(X_train, label=y_train)
D_test = xgboost.DMatrix(X_test, label=y_test)

params = {'max_depth': 6, 'objective': 'binary:logistic'}
num_iter = 20
bst_all = xgboost.train(params, D_train, num_iter, [
                        (D_train, 'train')], verbose_eval=False)

probs = bst_all.predict(D_test)
preds = np.array(probs) > 0.7

print("accuracy_score: ", accuracy_score(y_test, preds))

bst_all.feature_names = X_cols
key_value = bst_all.get_score(importance_type="gain")
key_value = sorted(key_value.items(), key=lambda kv: (kv[1], kv[0]))[::-1][:50]
top_feats = [kv[0] for kv in key_value]

"""
Select Features
"""
X_cols_candidates = top_feats
y_col = target_col

params = {'max_depth': 6, 'objective': 'binary:logistic', "n_jobs": -1}
num_iter = 20

accs = []
append_feats = []
feats_tobe_combined = []
corrcoefs = []

df_results = pd.DataFrame({})

# split segment_ids
# segment_ids = df_feats['segment_id'].unique().values
segment_ids_wear = df_feats.loc[df_feats["wear_category_id"] == 0, [
    "segment_id"]]
segment_ids_nonwear = df_feats.loc[df_feats["wear_category_id"] == 1, [
    "segment_id"]]
kf = KFold(n_splits=20, shuffle=True, random_state=42)
segment_index_wear = list(kf.split(segment_ids_wear["segment_id"].unique()))
segment_index_nonwear = list(
    kf.split(segment_ids_nonwear["segment_id"].unique()))
test_ids_list = []
for (train_index_wear, test_index_wear), (train_index_nonwear, test_index_nonwear) in zip(segment_index_wear, segment_index_nonwear):
    test_ids_wear = segment_ids_wear.values[test_index_wear]
    test_ids_nonwear = segment_ids_nonwear.values[test_index_nonwear]
    test_ids_list.append(np.concatenate([test_ids_wear, test_ids_nonwear]))
print("len(test_ids_list)", len(test_ids_list))

for f in X_cols_candidates:
    combined_feats = feats_tobe_combined.copy()
    if f not in combined_feats:
        combined_feats.append(f)
    else:
        continue

    y_probs_list, y_preds_list, y_test_list = [], [], []

    print("start training: ", datetime.datetime.now())

    for test_ids in test_ids_list:
        test_index = np.in1d(df_feats["segment_id"], test_ids)
        # print("test_index: ", test_index)
        X_train, y_train = df_feats.loc[~test_index,
                                        combined_feats].values, df_feats.loc[~test_index, y_col].values
        X_test,  y_test = df_feats.loc[test_index,
                                       combined_feats].values, df_feats.loc[test_index, y_col].values

        scaler = MinMaxScaler()
        X_train = scaler.fit_transform(X_train)
        X_test = scaler.transform(X_test)

        D_train = xgboost.DMatrix(X_train, label=y_train)
        D_test = xgboost.DMatrix(X_test, label=y_test)

        bst = xgboost.train(params, D_train, num_iter, [
                            (D_train, 'train')], verbose_eval=False)
        probs = bst.predict(D_test)
        preds = np.array(probs) > 0.7

        y_preds_list.extend(preds)
        y_test_list.extend(list(y_test))

    print("end training: ", datetime.datetime.now())

    acc = accuracy_score(y_test_list, y_preds_list)
    print("accuracy_score: ", acc)

    accs.append(acc)
    append_feats.append(f)
    if feats_tobe_combined:
        for ftc in feats_tobe_combined:
            corrcoef = np.corrcoef(df_feats[f], df_feats[ftc])[0][1]
            corrcoefs.append(corrcoef)


accs = np.array(accs).reshape(-1, 1)
append_feats = np.array(append_feats).reshape(-1, 1)
if feats_tobe_combined:
    corrcoefs = np.array(corrcoefs).reshape(-1, len(feats_tobe_combined))
    print("accs, append_feats, corrcoefs", accs.shape,
          append_feats.shape, corrcoefs.shape)
    df_results = np.concatenate(
        [append_feats, corrcoefs, accs], axis=1)
    columns = ["append_feats"] + feats_tobe_combined + ["accs"]
    df_results = pd.DataFrame(df_results, columns=columns)
else:
    df_results = np.concatenate([append_feats, accs], axis=1)
    columns = ["append_feats"] + ["accs"]
    df_results = pd.DataFrame(df_results, columns=columns)

df_results.to_csv("df_results_1feats__0114ir.csv", index=None)
