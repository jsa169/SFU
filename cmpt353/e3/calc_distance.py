import numpy as np
import pandas as pd
import xml.etree.ElementTree as et
from pykalman import KalmanFilter
import sys


def distance(df):
    df1 = (df)
    df2 = df.shift(-1,axis=0) 
    diff = np.deg2rad(df2-df1)  #calculate difference
    r = 6371000
    a = np.sin(diff['lat']/2) * np.sin(diff['lat']/2)  #formula from wikipedia
    b = np.cos(np.deg2rad(df1['lat']))*np.cos(np.deg2rad(df2['lat']))*np.sin(diff['lon']/2)*np.sin(diff['lon']/2)
    d = 2*r*np.arcsin(np.sqrt(a+b))
    return d.sum()

def smooth(df):
    initial_state = df.iloc[0]
    observation_covariance = np.diag([15,20]) ** 2 # 
    transition_covariance = np.diag([10,9]) ** 2 
    transition = [[1,0],[0,1]] 
    kf = KalmanFilter(
    initial_state_mean=initial_state,
    observation_covariance=observation_covariance,
    transition_covariance=transition_covariance,
    transition_matrices=transition
    )
    kalman_smoothed, _ = kf.smooth(df)
    return pd.DataFrame(kalman_smoothed, columns=['lat', 'lon'])

def output_gpx(points, output_filename):
    """
    Output a GPX file with latitude and longitude from the points DataFrame.
    """
    from xml.dom.minidom import getDOMImplementation
    def append_trkpt(pt, trkseg, doc):
        trkpt = doc.createElement('trkpt')
        trkpt.setAttribute('lat', '%.8f' % (pt['lat']))
        trkpt.setAttribute('lon', '%.8f' % (pt['lon']))
        trkseg.appendChild(trkpt)
    
    doc = getDOMImplementation().createDocument(None, 'gpx', None)
    trk = doc.createElement('trk')
    doc.documentElement.appendChild(trk)
    trkseg = doc.createElement('trkseg')
    trk.appendChild(trkseg)
    
    points.apply(append_trkpt, axis=1, trkseg=trkseg, doc=doc)
    
    with open(output_filename, 'w') as fh:
        doc.writexml(fh, indent=' ')


parse_result = et.parse(sys.argv[1]) #openfile
root = parse_result.getroot()

coord = []
for i in root.iter('{http://www.topografix.com/GPX/1/0}trkpt'):
    coord.append([i.attrib['lat'],i.attrib['lon']])

df = pd.DataFrame (coord, columns = ['lat','lon'], dtype=float) #append data to dataframe

print('Unfiltered distance: %0.2f' % (distance(df)))
smoothed_points = pd.DataFrame(smooth(df))
print('Filtered distance: %0.2f' % (distance(smoothed_points)))

output_gpx(smoothed_points, 'out.gpx')  #save to file
