
import numpy as np
import pandas as pd
import sys
import matplotlib.pyplot as plt




filename1 = sys.argv[1]
filename2 = sys.argv[2]




file1 = pd.read_csv(filename1, sep=' ', header=None, index_col=1,
        names=['lang', 'page', 'views', 'bytes'])



file1 = file1.sort_values('views',ascending=False)



file2 = pd.read_csv(filename2, sep=' ', header=None, index_col=1,
        names=['lang', 'page', 'views2', 'bytes'])


combined = pd.concat([file1, file2], axis=1)


plt.figure(figsize=(10, 5)) # change the size to something sensible
plt.subplot(1, 2, 1) # subplots in #1 row, 2 columns, select the first
plt.title("Popularity Distribution")
plt.xlabel("Rank")
plt.ylabel("views")
plt.plot(file1['views'].values) # build plot 1
plt.subplot(1, 2, 2) # ... and then select the second
plt.plot(combined['views'].values, combined['views2'].values,'o', color='blue',ms = 4) # build plot 2
plt.xscale('log')
plt.yscale('log')
plt.title("Daily Correlation")
plt.xlabel("Day 1 views")
plt.ylabel("Day 2 views")
plt.gcf()
plt.savefig('wikipedia.png')
plt.show()





