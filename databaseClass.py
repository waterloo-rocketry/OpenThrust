from scipy.interpolate import interp1d
import csv
from constants import CtoKELVIN


def interpX(X, Y):
    return interp1d(X, Y, kind="cubic", bounds_error=False)


def calcQuality(rho, rho_V, rho_L):
    """
    Returns the factor for determining properties of the liquid/vapour mixture
    Property = PropertyVapour * factor + PropertyLiquid * (1-factor)
    """
    a = rho_V / rho
    b = rho_L / rho
    c = rho_L - rho_V
    return a * (b / c)


class DataBase(object):

    def __init__(self, databasePath):
        self.path = databasePath  # Path to database from working directory
        self.nistSplines_T = {}
        self.nistSplines_P = {}
        self.loaded = False

        self.s_L_NIST = []
        self.h_L_NIST = []
        self.rho_L_NIST = []
        self.P_NIST = []
        self.T_NIST = []
        self.rho_V_NIST = []
        self.h_V_NIST = []
        self.s_V_NIST = []

    def buildNistSplines(self):
        # Read in data from file
        rowCount = -1
        for row in csv.reader(open(self.path, 'r'), delimiter='\t'):
            if rowCount > -1:
                self.T_NIST[rowCount] = float(row[0]) + CtoKELVIN
                self.P_NIST[rowCount] = float(row[1])
                self.rho_L_NIST[rowCount] = float(row[2])
                self.h_L_NIST[rowCount] = float(row[5])
                self.s_L_NIST[rowCount] = float(row[6])
                self.rho_V_NIST[rowCount] = float(row[14])
                self.h_V_NIST[rowCount] = float(row[17])
                self.s_V_NIST[rowCount] = float(row[18])
            rowCount += 1

        # Interpolate with respect to temperature to build splines
        self.nistSplines_T["P"] = interpX(self.T_NIST, self.P_NIST)
        self.nistSplines_T["rho_L"] = interpX(self.T_NIST, self.rho_L_NIST)
        self.nistSplines_T["h_L_NIST"] = interpX(self.T_NIST, self.h_L_NIST)
        self.nistSplines_T["s_L_NIST"] = interpX(self.T_NIST, self.s_L_NIST)
        self.nistSplines_T["rho_V_NIST"] = interpX(self.T_NIST, self.rho_V_NIST)
        self.nistSplines_T["h_V_NIST"] = interpX(self.T_NIST, self.h_V_NIST)
        self.nistSplines_T["s_V_NIST"] = interpX(self.T_NIST, self.s_V_NIST)

        # Interpolate with respect to pressure to build splines
        self.nistSplines_T["T"] = interpX(self.P_NIST, self.T_NIST)
        self.nistSplines_T["rho_L"] = interpX(self.P_NIST, self.rho_L_NIST)
        self.nistSplines_T["h_L_NIST"] = interpX(self.P_NIST, self.h_L_NIST)
        self.nistSplines_T["s_L_NIST"] = interpX(self.P_NIST, self.s_L_NIST)
        self.nistSplines_T["rho_V_NIST"] = interpX(self.P_NIST, self.rho_V_NIST)
        self.nistSplines_T["h_V_NIST"] = interpX(self.P_NIST, self.h_V_NIST)
        self.nistSplines_T["s_V_NIST"] = interpX(self.P_NIST, self.s_V_NIST)

    def grabProps(self, rho, T=None, P=None):
        """
        Returns data for either a specified temperature or pressure.
        If both are specified, temperature will be used to generate the data
        """
        if T and T <= 0:
            raise ValueError("Temperature is at or below 0 K")
        if rho <= 0:
            raise ValueError("Density is at or below 0")
        if P and P <= 0:
            raise ValueError("Pressure is at or below 0")
        props = {}
        if T:
            props["T"] = T
            props["P"] = float(self.nistSplines_T["P"](T))
            propSet = lambda prop: float(self.nistSplines_T[prop](T))
        elif P:
            props["T"] = float(self.nistSplines_P["T"](P))
            props["P"] = P
            propSet = lambda prop: float(self.nistSplines_P[prop](P))
        else:
            raise ValueError("No reference point given")
        propSet("rho_L")
        propSet("h_L_NIST")
        propSet("s_L_NIST")
        propSet("rho_V_NIST")
        propSet("h_V_NIST")
        propSet("s_V_NIST")

        props["X"] = calcQuality(rho, props["rho_V"], props["rho_L"])
        props["h"] = props["h_V"]*props["X"] + props["h_L"]*(1-props["X"])
        props["s"] = props["s_V"]*props["X"] + props["s_L"]*(1-props["X"])
        props["state"] = 1

        return props
