import sys
import matplotlib.pyplot as plt
import numpy as np
from scipy import interpolate
#from sklearn.pipeline import Pipeline
#from sklearn.preprocessing import PolynomialFeatures
#from sklearn.linear_model import LinearRegression

from math import *

throat_diameter = 0.03375 #m
At = pi*pow(throat_diameter/2, 2)

p_cc_nom = 0 #psi, used as the inital guess for finding p_cc and mdot

K = 0.02581988897 # kg/sec / sqrt(psi)

mdot_idx = 15
of_idx = 0
p_cc_idx = 1

########################## import RPA data ###############################
filename = sys.argv[1]

data = open(filename, 'r').read()
data = data.splitlines()

num_data = []
for line in data:
    line.strip()
    if '#' not in line:
        float_line = [float(x) for x in line.split()]
        num_data.append(float_line)

# Calculate new values
flow_data = []
cc_pressures = []
mdot_list = []
of_list = []
for line in num_data:

    # c* = p*At/mdot
    #mdot = p*At/c*
    line.append(float(line[p_cc_idx])*6894.76*At/float(line[9])) #mdot in idx 15
    line.append(float(line[10])*float(line[15])*9.81) #opt thrust in index 16
    #print ("Press: ", line[1], "  O/f: ", line[0], "  mdot: ", line[15], "  thrust: ", line[16])

    #O/F, Mdot
    flow_data.append([float(line[of_idx]), float(line[mdot_idx])])
    cc_pressures.append(float(line[1]))
    mdot_list.append(float(line[mdot_idx]))
    of_list.append(float(line[of_idx]))


#a little ugly but it's easy
def get_closest_p_cc(mdot, of_ratio):
    closest = [num_data[0], 9999.9]
    for line in num_data:
        error = sqrt(pow(mdot - float(line[mdot_idx]), 2) + pow(of_ratio - float(line[of_idx]), 2))
        if error < closest[1]:
            closest[0] = line
            closest[1] = error

    #print("closest: ", closest[0][1])

    return float(closest[0][1])

def get_interpolated_p_cc(mdot, of_ratio):
    #find the closest point in each quadrant
    #arbitrairly y axis is O/F, x is Mdot
    q1 = [num_data[0], 9999.9]
    q2 = [num_data[0], 9999.9]
    q3 = [num_data[0], 9999.9]
    q4 = [num_data[0], 9999.9]
    for line in num_data:
        y_error = of_ratio - float(line[of_idx])
        x_error = mdot - float(line[mdot_idx])
        error = sqrt(pow(y_error, 2) + pow(x_error, 2))
        if error < q1[1] and x_error >= 0 and y_error >= 0:
            q1[0] = line
            q1[1] = error
        if error < q2[1] and x_error < 0 and y_error >= 0:
            q2[0] = line
            q2[1] = error
        if error < q3[1] and x_error < 0 and y_error < 0:
            q3[0] = line
            q3[1] = error
        if error < q4[1] and x_error >= 0 and y_error < 0:
            q4[0] = line
            q4[1] = error

    #print("q1: O/F: ", q1[0][of_idx], " M dot: ", q1[0][mdot_idx], " Pcc: ", q1[0][p_cc_idx])
    #print("q2: O/F: ", q2[0][of_idx], " M dot: ", q2[0][mdot_idx], " Pcc: ", q2[0][p_cc_idx])
    #print("q3: O/F: ", q3[0][of_idx], " M dot: ", q3[0][mdot_idx], " Pcc: ", q3[0][p_cc_idx])
    #print("q4: O/F: ", q4[0][of_idx], " M dot: ", q4[0][mdot_idx], " Pcc: ", q4[0][p_cc_idx])
    
    #interpolate along x
    #q1 and q2
    pccq12 = q1[0][p_cc_idx] + (mdot - q1[0][mdot_idx])*(q2[0][p_cc_idx] - q1[0][p_cc_idx]) / (q2[0][mdot_idx] - q1[0][mdot_idx])
    #print("pccq12: ", pccq12)

    #q3 and q4
    pccq34 = q3[0][p_cc_idx] + (mdot - q3[0][mdot_idx])*(q4[0][p_cc_idx] - q3[0][p_cc_idx]) / (q4[0][mdot_idx] - q3[0][mdot_idx])
    #print("pccq34: ", pccq34)

    #interpolate along y
    pcc_intr = pccq12 + (of_ratio - q1[0][of_idx])*(pccq34 - pccq12) / (q3[0][of_idx] - q1[0][of_idx])

    print("pcc interp: ", pcc_intr)
    
    return pcc_intr
    

#a square root function that is always defined and avoids /0 errors
def sqrt_def_all(num):
    if num <= 0:
        return 0.0000001
    else:
        return sqrt(num)

for mdot_test in range(4, 20, 1):
    print(mdot_test/10.0)
    get_interpolated_p_cc(mdot_test/10.0, 5.1)

mdot = -1
of_ratio = -1
for tank_press in range(1000, 1000, 20):
    p_cc = p_cc_nom
    for i in range(10): #iterate 10 times, seems to be plenty
        #assume constant 1kg/sec for ox
        print("fuel flow: ", K*sqrt_def_all(tank_press - p_cc))
        mdot = K*sqrt_def_all(tank_press - p_cc) + 1
        of_ratio = 1 / (K*sqrt_def_all(tank_press - p_cc))

        p_cc = get_interpolated_p_cc(mdot, of_ratio)
    print ("Tank Press: ", tank_press, "  CC Press: ", p_cc, "  O/f: ", of_ratio, "  mdot: ", mdot)


###some plotting stuff
#fig = plt.figure()
#ax = fig.add_subplot()#(projection='3d')
#ax.scatter(mdot_list, of_list, cc_pressures)
#ax.scatter(mdot_list, of_list)

#ax_test = fig.add_subplot(projection='3d')
#ax_test.scatter(mdot_test, of_test, p_cc_test)
#plt.show()


