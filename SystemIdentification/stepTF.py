import numpy as np
from matplotlib import pyplot as plt
import pandas as pd
from scipy import signal
import math

# Import data from excel
WS = pd.read_excel('logV3_allCyl.xlsx')

# Parameters for the butterworth low-pass filter
filter_cutoff = 15
filter_order = 1


# Convert data to Numpy-arrays
t = np.array(WS['Timestamp'])/1e6
t = t - t[0]
u = np.array(WS['Input'])

x1 = np.array(WS['Pos1'])
x1 = x1 - x1[0]

x2 = np.array(WS['Pos2'])
x2 = x2 - x2[0]

x3 = np.array(WS['Pos3'])
x3 = x3 - x3[0]

x4 = np.array(WS['Pos4'])
x4 = x4 - x4[0]

x5 = np.array(WS['Pos5'])
x5 = x5 - x5[0]

x6 = np.array(WS['Pos6'])
x6 = x6 - x6[0]


# Define filter params
b, a = signal.butter(filter_order, filter_cutoff, analog=False, fs=100)

# Filter reading in both directions with filfilt
x1_ff = signal.filtfilt(b, a, x1)
x2_ff = signal.filtfilt(b, a, x2)
x3_ff = signal.filtfilt(b, a, x3)
x4_ff = signal.filtfilt(b, a, x4)
x5_ff = signal.filtfilt(b, a, x5)
x6_ff = signal.filtfilt(b, a, x6)


# Using only the step = +1 part of the curve
u = u[t > 0.5]

x1_ff = x1_ff[t > 0.5]
x1 = x1[t > 0.5]

x2_ff = x2_ff[t > 0.5]
x2 = x2[t > 0.5]

x3_ff = x3_ff[t > 0.5]
x3 = x3[t > 0.5]

x4_ff = x4_ff[t > 0.5]
x4 = x4[t > 0.5]

x5_ff = x5_ff[t > 0.5]
x5 = x5[t > 0.5]

x6_ff = x6_ff[t > 0.5]
x6 = x6[t > 0.5]

t = t[t > 0.5]


u = u[t < 2.5]

x1_ff = x1_ff[t < 2.5]
x1 = x1[t < 2.5]

x2_ff = x2_ff[t < 2.5]
x2 = x2[t < 2.5]

x3_ff = x3_ff[t < 2.5]
x3 = x3[t < 2.5]

x4_ff = x4_ff[t < 2.5]
x4 = x4[t < 2.5]

x5_ff = x5_ff[t < 2.5]
x5 = x5[t < 2.5]

x6_ff = x6_ff[t < 2.5]
x6 = x6[t < 2.5]

t = t[t < 2.5]


# Calculate the derivative and double-derivate of each actuator reading

x1_dot = np.array([])
for i in range(t.size):
    if i == 0:
        x1_dot = np.append(x1_dot, [0.0])
    else:
        x1_dot = np.append(x1_dot, [(x1_ff[i] - x1_ff[i-1]) / (t[i] - t[i-1]) ])

x1_ddot = np.array([])
for i in range(t.size):
    if i == 0:
        x1_ddot = np.append(x1_ddot, [0.0])
    else:
        x1_ddot = np.append(x1_ddot, [(x1_dot[i] - x1_dot[i-1]) / (t[i] - t[i-1]) ])


x2_dot = np.array([])
for i in range(t.size):
    if i == 0:
        x2_dot = np.append(x2_dot, [0.0])
    else:
        x2_dot = np.append(x2_dot, [(x2_ff[i] - x2_ff[i-1]) / (t[i] - t[i-1]) ])

x2_ddot = np.array([])
for i in range(t.size):
    if i == 0:
        x2_ddot = np.append(x2_ddot, [0.0])
    else:
        x2_ddot = np.append(x2_ddot, [(x2_dot[i] - x2_dot[i-1]) / (t[i] - t[i-1]) ])


x3_dot = np.array([])
for i in range(t.size):
    if i == 0:
        x3_dot = np.append(x3_dot, [0.0])
    else:
        x3_dot = np.append(x3_dot, [(x3_ff[i] - x3_ff[i-1]) / (t[i] - t[i-1]) ])

x3_ddot = np.array([])
for i in range(t.size):
    if i == 0:
        x3_ddot = np.append(x3_ddot, [0.0])
    else:
        x3_ddot = np.append(x3_ddot, [(x3_dot[i] - x3_dot[i-1]) / (t[i] - t[i-1]) ])


x4_dot = np.array([])
for i in range(t.size):
    if i == 0:
        x4_dot = np.append(x4_dot, [0.0])
    else:
        x4_dot = np.append(x4_dot, [(x4_ff[i] - x4_ff[i-1]) / (t[i] - t[i-1]) ])

x4_ddot = np.array([])
for i in range(t.size):
    if i == 0:
        x4_ddot = np.append(x4_ddot, [0.0])
    else:
        x4_ddot = np.append(x4_ddot, [(x4_dot[i] - x4_dot[i-1]) / (t[i] - t[i-1]) ])


x5_dot = np.array([])
for i in range(t.size):
    if i == 0:
        x5_dot = np.append(x5_dot, [0.0])
    else:
        x5_dot = np.append(x5_dot, [(x5_ff[i] - x5_ff[i-1]) / (t[i] - t[i-1]) ])

x5_ddot = np.array([])
for i in range(t.size):
    if i == 0:
        x5_ddot = np.append(x5_ddot, [0.0])
    else:
        x5_ddot = np.append(x5_ddot, [(x5_dot[i] - x5_dot[i-1]) / (t[i] - t[i-1]) ])


x6_dot = np.array([])
for i in range(t.size):
    if i == 0:
        x6_dot = np.append(x6_dot, [0.0])
    else:
        x6_dot = np.append(x6_dot, [(x6_ff[i] - x6_ff[i-1]) / (t[i] - t[i-1]) ])

x6_ddot = np.array([])
for i in range(t.size):
    if i == 0:
        x6_ddot = np.append(x6_ddot, [0.0])
    else:
        x6_ddot = np.append(x6_ddot, [(x6_dot[i] - x6_dot[i-1]) / (t[i] - t[i-1]) ])


# Calculate K and a for each actuator

A1 = np.column_stack((u, -x1_ddot))

A1_t = np.transpose(A1)

theta1 = np.linalg.inv(A1_t @ A1) @ A1_t @ np.vstack(x1_dot)  

K1 = theta1[0][0]   
tau1 = theta1[1][0] 

print("K_1:\t", round(K1, 5), "\ntau_1:\t", round(tau1, 5))


A2 = np.column_stack((u, -x2_ddot))

A2_t = np.transpose(A2)

theta2 = np.linalg.inv(A2_t @ A2) @ A2_t @ np.vstack(x2_dot)  

K2 = theta2[0][0]   
tau2 = theta2[1][0] 

print("\n\nK_2:\t", round(K2, 5), "\ntau_2:\t", round(tau2, 5))


A3 = np.column_stack((u, -x3_ddot))

A3_t = np.transpose(A3)

theta3 = np.linalg.inv(A3_t @ A3) @ A3_t @ np.vstack(x3_dot) 

K3 = theta3[0][0]   
tau3 = theta3[1][0] 

print("\n\nK_3:\t", round(K3, 5), "\ntau_3:\t", round(tau3, 5))


A4 = np.column_stack((u, -x4_ddot))

A4_t = np.transpose(A4)

theta4 = np.linalg.inv(A4_t @ A4) @ A4_t @ np.vstack(x4_dot) 

K4 = theta4[0][0]   
tau4 = theta4[1][0] 

print("\n\nK_4:\t", round(K4, 5), "\ntau_4:\t", round(tau4, 5))


A5 = np.column_stack((u, -x5_ddot))

A5_t = np.transpose(A5)

theta5 = np.linalg.inv(A5_t @ A5) @ A5_t @ np.vstack(x5_dot) 

K5 = theta5[0][0]   
tau5 = theta5[1][0] 

print("\n\nK_5:\t", round(K5, 5), "\ntau_5:\t", round(tau5, 5))


A6 = np.column_stack((u, -x6_ddot))

A6_t = np.transpose(A6)

theta6 = np.linalg.inv(A6_t @ A1) @ A6_t @ np.vstack(x6_dot)

K6 = theta6[0][0]   
tau6 = theta6[1][0] 

print("\n\nK_6:\t", round(K6, 5), "\ntau_6:\t", round(tau6, 5))


# Calculate mean, sample variance and sample standard deviation for both K and a
n = 6

mean_K = (K1 + K2 + K3 + K4 + K5 + K6) / n
sample_variance_K = ((K1 - mean_K)**2 + (K2 - mean_K)**2 + (K3 - mean_K)**2 + (K4 - mean_K)**2 + (K5 - mean_K)**2 + (K6 - mean_K)**2) / (n-1)
sample_sd_K = math.sqrt(sample_variance_K)

mean_tau = (tau1 + tau2 + tau3 + tau4 + tau5 + tau6) / n
sample_variance_a = ((tau1 - mean_tau)**2 + (tau2 - mean_tau)**2 + (tau3 - mean_tau)**2 + (tau4 - mean_tau)**2 + (tau5 - mean_tau)**2 + (tau6 - mean_tau)**2) / (n-1)
sample_sd_a = math.sqrt(sample_variance_a)

print("\n\n\nTransferfunction:\n\n   ", round(mean_K, 3), "\n-------------\n", round(mean_tau, 3), "s + 1" "\n\n") 

print("Sample variance:\ntau:\t", round(sample_variance_a, 6), "\nK:\t", round(sample_variance_K, 6), "\n\n")

print("Sample standard deviation:\ntau:\t", round(sample_sd_a, 5), "\nK:\t", round(sample_sd_K, 5), "\n\n")


# Simulate a step respone with the transferfunction using the calculated means above
num = [mean_K]
den = [mean_tau, 1]
sys_sim = signal.TransferFunction(num, den)
t_sim, y_sim = signal.step(sys_sim, X0=None, T = t[u==1])


# Plot input, posistion, velocity and acceleration for one of the actuator readings
fig, (ax1, ax2, ax3, ax4) = plt.subplots(4, 1)
ax1.plot(t, u, label='u(t)')
ax1.legend()

# Replace number below to choose which actuator to plot for
ax2.plot(t, x1_ff, label="y(t)")
ax2.legend()

ax3.plot(t, x1_dot, label="y'(t)")
ax3.plot(t_sim, y_sim, label='step_sim')
ax3.legend()

ax4.plot(t, x1_ddot, label="y''(t)")
ax4.legend()

plt.show()
