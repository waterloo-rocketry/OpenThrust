import os

# Collection point for all fixed constants used

BASE_PATH = os.path.dirname(os.path.abspath(__file__))
CONFIG_PATH = os.path.join(BASE_PATH, "settings.cfg")
NIST_PATH = os.path.join(BASE_PATH, 'ReferenceData', 'N2O_100_1000PSI.txt')

PSI_TO_PASCAL = 6894.76
ATMOSPHERE_PSI = 14.7
CENTIGRADE_TO_KELVIN = 273.15
CM2_TO_M2 = 0.0001
L_TO_M3 = 1.0 / 1000.0

PROPERTIES_HEADER = "Rocket Properties"
DIMENSIONS_HEADER = "Rocket Dimensions"
