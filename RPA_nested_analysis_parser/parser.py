import sys
import numpy as np
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

flow_data = []
cc_pressures = []
for line in num_data:

    # c* = p*At/mdot
    #mdot = p*At/c*
    line.append(float(line[p_cc_idx])*6894.76*At/float(line[9])) #mdot in idx 15
    line.append(float(line[10])*float(line[15])*9.8) #opt thrust in index 16
    #print ("Press: ", line[1], "  O/f: ", line[0], "  mdot: ", line[15], "  thrust: ", line[16])

    #O/F, Mdot
    flow_data.append([float(line[0]), float(line[15])])
    cc_pressures.append(float(line[1]))

polynomial_features = PolynomialFeatures(degree=2, include_bias=False)
linear_regression = LinearRegression()
pipeline = Pipeline([("polynomial_features", polynomial_features),
                         ("linear_regression", linear_regression)])

fit = pipeline.fit(flow_data, cc_pressures)


print("fit: ", fit.predict([[4.5, 1.6], [5, 1.2]]))


#a little ugly but it's easy
def get_p_cc(mdot, of_ratio):
    closest = [num_data[0], 9999.9]
    second = [num_data[0], 9999.9]
    third = [num_data[0], 9999.9]
    for line in num_data:
        error = sqrt(pow(mdot - float(line[mdot_idx]), 2) + pow(of_ratio - float(line[of_idx]), 2))
        if error < closest[1]:
            if not (line[0] == closest[0][0] and closest[0][0] == second[0][0]): #ensure that the three points do not lie on a line
                third = second.copy()
            second = closest.copy()
            closest[0] = line
            closest[1] = error

        elif error < second[1]:
            if  not (line[0] == closest[0][0] and closest[0][0] == second[0][0]): #ensure that the three points do not lie on a line
                third = second.copy()
            second[0] = line
            second[1] = error

        elif error < third[1] and not (line[0] == closest[0][0] and closest[0][0] == second[0][0]): #ensure that the three points do not lie on a line
            third[0] = line
            third[1] = error

    #x = O/F, y = mdot, z = p_cc
    #ax + by + cz = d
    #d = 1
    #z = (d - ax - by)/c

    A_list = [[float(closest[0][0]), float(closest[0][15]), float(closest[0][1])], [float(second[0][0]), float(second[0][15]), float(second[0][1])], [float(third[0][0]), float(third[0][15]), float(third[0][1])]]
    A = np.array(A_list)

    B = np.array([[1], [1], [1]])

    X = np.linalg.inv(A).dot(B)

    #print(X)

    #print("closest: ", closest[0][0], closest[0][15])
    #print("second: ", second[0][0], second[0][15])
    #print("third: ", third[0][0], third[0][15])

    print("closest: ", closest[0][1])

    return float((1 - X[0]*of_ratio - X[1]*mdot)/X[2])

def sqrt_def_all(num):
    if num <= 0:
        return 0.0000001
    else:
        return sqrt(num)

mdot = -1
of_ratio = -1
for tank_press in range(500, 500, 20):
    p_cc = p_cc_nom
    for i in range(5): #iterate 10 times, seems to be plenty
        #assume constant 1kg/sec for ox
        #print("fuel flow: ", K*sqrt_def_all(tank_press - p_cc))
        mdot = K*sqrt_def_all(tank_press - p_cc) + 1
        of_ratio = 1 / (K*sqrt_def_all(tank_press - p_cc))

        p_cc = get_p_cc(mdot, of_ratio)
    print ("Tank Press: ", tank_press, "  CC Press: ", p_cc, "  O/f: ", of_ratio, "  mdot: ", mdot)
