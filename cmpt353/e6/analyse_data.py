
import pandas as pd
import numpy as np
from scipy import stats
from statsmodels.stats.multicomp import pairwise_tukeyhsd

filename = 'data.csv'
df = pd.read_csv(filename)

anova = stats.f_oneway(df['qs1'], df['qs2'], df['qs3'],
                        df['qs4'], df['qs5'], df['merge'], df['partition'])
if anova.pvalue < 0.05:
    print("anova p-value is:", anova.pvalue)
    print("With p < 0.05, we conclude that there is a differnce between the means of run time of different sorting funtions.")
    print("Post Hoc Analysis:")
    melt = pd.melt(df) #Code taken from class
    posthoc = pairwise_tukeyhsd(
        melt['value'], melt['variable'],
        alpha=0.05)
    print(posthoc)





