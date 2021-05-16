import sys
import matplotlib.pyplot as plt
import numpy as np
from scipy import interpolate
from sklearn.pipeline import Pipeline
from sklearn.preprocessing import PolynomialFeatures
from sklearn.linear_model import LinearRegression

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
        num_data.append(line.split())

# Calculate new values
flow_data = []
cc_pressures = []
mdot_list = []
of_list = []
for line in num_data:

    # c* = p*At/mdot
    #mdot = p*At/c*
    line.append(float(line[p_cc_idx])*6894.76*At/float(line[9])) #mdot in idx 15
    line.append(float(line[10])*float(line[15])*9.8) #opt thrust in index 16
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

f_p_cc = interpolate.interp2d(np.array(mdot_list), np.array(of_list), np.array(cc_pressures))


fig = plt.figure()
ax = fig.add_subplot(projection='3d')
ax.scatter(mdot_list, of_list, cc_pressures)

mdot_test = np.arange(1.1, 1.3, 0.01)
of_test = np.arange(4, 6, 0.1)
p_cc_test = f_p_cc(mdot_test, of_test)

p_cc_test = p_cc_test.flatten()

print(p_cc_test)

ax_test = fig.add_subplot(projection='3d')
ax_test.scatter(mdot_test, of_test, p_cc_test)
plt.show()

def get_interpolated_p_cc(mdot, of_ratio):
    return f_p_cc(mdot, of_ratio)



def sqrt_def_all(num):
    if num <= 0:
        return 0.0000001
    else:
        return sqrt(num)

mdot = -1
of_ratio = -1
for tank_press in range(460, 460, 20):
    p_cc = p_cc_nom
    for i in range(10): #iterate 10 times, seems to be plenty
        #assume constant 1kg/sec for ox
        #print("fuel flow: ", K*sqrt_def_all(tank_press - p_cc))
        mdot = K*sqrt_def_all(tank_press - p_cc) + 1
        of_ratio = 1 / (K*sqrt_def_all(tank_press - p_cc))

        p_cc = get_interpolated_p_cc(mdot, of_ratio)
    print ("Tank Press: ", tank_press, "  CC Press: ", p_cc, "  O/f: ", of_ratio, "  mdot: ", mdot)


if False:
    for degree in range(1, 20, 1):
        print("degree: ", degree)
        polynomial_features = PolynomialFeatures(degree=degree, include_bias=False)
        linear_regression = LinearRegression()
        pipeline = Pipeline([("polynomial_features", polynomial_features),
                                ("linear_regression", linear_regression)])
        fit = pipeline.fit(flow_data, cc_pressures)

        total_root_error = 0
        total_error = 0
        for line in num_data:
            #print ("Press: ", line[1], "  O/f: ", line[0], "  mdot: ", line[15], "  thrust: ", line[16])
            #print("fit press: ", fit.predict([[float(line[0]), float(line[15])]]))

            predict_error = float(line[1]) - fit.predict([[float(line[0]), float(line[15])]])

            total_error += abs(predict_error)
            total_root_error += sqrt(abs(predict_error))

        print("total root: ", total_root_error)
        print("average error: ", total_error/len(num_data))
        print("Nominal CC estimate:", fit.predict([[5, 1.2]]))


