#pd_summary.py
#
#Auther: Jichuan
#
#Date: 2020-02-20
#
#
import numpy as np
import pandas as pd


totals = pd.read_csv('totals.csv').set_index(keys=['name'])

total = totals.sum(1)
min_ = total.idxmin()
print ('City with lowest total precipitation:\n', min_)

counts = pd.read_csv('counts.csv').set_index(keys=['name'])

total_month_percep = totals.sum(0)
total_month_count = counts.sum(0)
print ('Average precipitation in each month:\n', total_month_percep/total_month_count)


annual_city_precep = totals.sum(1)
annual_city_count = counts.sum(1)
print ('Average precipitation in each city:\n', annual_city_precep/annual_city_count)



