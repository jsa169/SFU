import time
import numpy as np
import pandas as pd
import scipy.stats as stats

from implementations import all_implementations

data = pd.DataFrame(
                    columns=['qs1','qs2','qs3','qs4',
                             'qs5','merge','partition'],dtype=float
                    )

for i in range (1200):
    test_result = []
    random_array = np.random.randint(0,500,size=(500))
    for sort in all_implementations:
        st = time.time()
        res = sort(random_array)
        en = time.time()
        test_result.append(en-st)

    data.loc[len(data), :] = test_result
    test_result.clear()
data.to_csv('data.csv',index=False)
