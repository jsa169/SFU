#np_summary.py
#
#Auther: Jichuan
#
#Date: 2020-02-20
#
#

import numpy as np

data = np.load('monthdata.npz')
totals = data['totals']
counts = data['counts']


sum_row = np.sum(totals, 1)
lowest_total = np.argmin(sum_row)
print ('Row with lowest total precipitation:\n', lowest_total)


avg_percep_month = np.sum(totals, 0,dtype = np.single) / np.sum(counts, 0)
print('Average precipitation in each month:\n',avg_percep_month)


avg_percep_city = np.sum(totals, 1,dtype = np.single) / np.sum(counts, 1)
print('Average precipitation in each city:\n',avg_percep_city)

rows = np.size(totals, 0)
quarter = totals.reshape(rows*4,3)
quarter = quarter.sum(1)
quarter = quarter.reshape(rows, 4) 
print('Quarterly precipitation totals:\n', quarter)




