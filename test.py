import pandas as pd
from scipy.stats import kurtosis

x = [22435, 22432, 22438, 22419, 22417, 22423, 22432, 22421, 22417, 22421, 22426,
    22416, 22420, 22422, 22423, 22419, 22421, 22420, 22420, 22421, 22419, 22419,
    22419, 22418, 22414, 22419, 22420, 22420, 22415, 22419, 22420, 22417, 22417,
    22415, 22416, 22415, 22415, 22415, 22415, 22416, 22412, 22412, 22415, 22409,
    22411, 22413, 22411, 22410, 22410, 22411, 22413, 22412, 22411, 22412, 22409,
    22407, 22413, 22410, 22405, 22410, 22411, 22409, 22409, 22408]

# a = kurtosis(x, fisher=True, bias=False)
# x = pd.Series(x)
# a = pd.Series.kurtosis(x)

from tsfresh.feature_extraction.feature_calculators import change_quantiles

from statsmodels.tsa.ar_model import AR

model = AR(x)
model_fit = model.fit(maxlag=10).params

print()