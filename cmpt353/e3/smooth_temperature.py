
import pandas as pd
import numpy as np
import statsmodels.nonparametric.smoothers_lowess
import matplotlib.pyplot as plt
from pykalman import KalmanFilter
import sys


cpu_data = pd.read_csv(sys.argv[1], parse_dates = [0]) #readfile

plt.figure(figsize=(12, 4)) #data scatter plot
plt.plot(cpu_data['timestamp'], cpu_data['temperature'], 'b.', alpha=0.5)

loess_smoothed = statsmodels.nonparametric.smoothers_lowess.lowess(cpu_data['temperature'], cpu_data['timestamp'],frac = 0.06                                                   )
plt.plot(cpu_data['timestamp'], loess_smoothed[:, 1], 'r-')#lowess smoothed plot

kalman_data = cpu_data[['temperature', 'cpu_percent', 'sys_load_1', 'fan_rpm']]
initial_state = kalman_data.iloc[0]
observation_covariance = np.diag([70, 20, 20, 0.001]) ** 2 # TODO: shouldn't be zero
transition_covariance = np.diag([0.002, 0.8, 0.8, 0.0001]) ** 2 # TODO: shouldn't be zero
transition = [[0.97,0.5,0.2,-0.001], [0.1,0.4,2.2,0], [0,0,0.95,0], [0,0,0,1]] # TODO: shouldn't (all) be zero
kf = KalmanFilter(
    initial_state_mean=initial_state,
    initial_state_covariance=observation_covariance,
    observation_covariance=observation_covariance,
    transition_covariance=transition_covariance,
    transition_matrices=transition
)
kalman_smoothed, _ = kf.smooth(kalman_data) #kalman smoothed

plt.figure(figsize=(12, 4)) #plot everything and save 
plt.plot(cpu_data['timestamp'], cpu_data['temperature'], 'b.', alpha=0.5)
plt.plot(cpu_data['timestamp'], loess_smoothed[:, 1], 'r-')
plt.plot(cpu_data['timestamp'], kalman_smoothed[:, 0], 'g-')
plt.legend(['data points,', 'LOESS-smoothed line', 'Kalman-smoothed line'])
plt.xlabel('Timestamp')
plt.ylabel('Temperature')
plt.savefig('cpu.svg')
