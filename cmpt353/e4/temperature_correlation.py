

import pandas as pd
import numpy as np
import sys
import matplotlib.pyplot as plt

def distance(city, stations):
    lon_1 = city['longitude']
    lat_1 = city['latitude']
    lon_2 = stations['longitude']
    lat_2 = stations['latitude']
    
    diff_lon = lon_2-lon_1 #calculate difference
    diff_lat = lat_2-lat_1
    
    r = 6371000
    a = np.sin(diff_lat/2) * np.sin(diff_lat/2)  #formula from wikipedia
    b = np.cos(np.deg2rad(lat_1))*np.cos(np.deg2rad(lat_2))*np.sin(diff_lon/2)*np.sin(diff_lon/2)
    d = 2*r*np.arcsin(np.sqrt(a+b))
    
    stations['distance'] = d

def best_tmax(city,stations):
    distance(city,stations)
    closest = np.argmin(stations['distance'])
    best_tmax = stations['avg_tmax'][closest]
    return best_tmax

stations = pd.read_json(sys.argv[1], lines=True) #read file
stations.avg_tmax = stations.avg_tmax/10

city = pd.read_csv(sys.argv[2]).dropna() #read file
city['area'] = city['area']/1000000
city = city[city['area'] <= 10000]

city['avg_temp'] = city.apply(best_tmax, stations = stations, axis = 1) #get value from closest station
city['density'] = city['population']/city['area'] #calc pop. density


plt.scatter(city['avg_temp'],city['density'])	#draw
plt.xlabel('Avg Max Temperature (\u00b0C)')
plt.ylabel('Population Density (people/km\u00b2)')
plt.title('Temperature vs Population Density')
plt.savefig(sys.argv[3])




