import sys

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

of_ratio = []
pressure = []

for line in num_data:

    # c* = p*At/mdot
    #mdot = p*At/c*
    line.append(float(line[p_cc_idx])*6894.76*At/float(line[9])) #mdot in idx 15
    line.append(float(line[10])*float(line[15])*9.8) #opt thrust in index 16
    #print ("Press: ", line[1], "  O/f: ", line[0], "  mdot: ", line[15], "  thrust: ", line[16])


#a little ugly but it's easy
def get_p_cc(mdot, of_ratio):
    error = 999.99
    p_cc = -1
    for line in num_data:
        if sqrt(pow(mdot - float(line[mdot_idx]), 2) + pow(of_ratio - float(line[of_idx]), 2)) < error:
            p_cc = float(line[p_cc_idx])
            error = sqrt(pow(mdot - float(line[mdot_idx]), 2) + pow(of_ratio - float(line[of_idx]), 2))
            #print("Error: ", error, " mdot: ", line[mdot_idx], " of: ", line[of_idx])
            #print("TARGETS: ", " mdot: ", mdot, " of: ", of_ratio)

    return p_cc

def sqrt_def_all(num):
    if num <= 0:
        return 0.0000001
    else:
        return sqrt(num)

mdot = -1
of_ratio = -1
for tank_press in range(200, 900, 10):
    p_cc = p_cc_nom
    for i in range(10): #iterate 10 times, seems to be plenty
        #assume constant 1kg/sec for ox
        #print("fuel flow: ", K*sqrt_def_all(tank_press - p_cc))
        mdot = K*sqrt_def_all(tank_press - p_cc) + 1
        of_ratio = 1 / (K*sqrt_def_all(tank_press - p_cc))

        p_cc = get_p_cc(mdot, of_ratio)
    print ("Tank Press: ", tank_press, "  CC Press: ", p_cc, "  O/f: ", of_ratio, "  mdot: ", mdot)
