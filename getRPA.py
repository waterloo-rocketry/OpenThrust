import platform
import ctypes
import os


def encodeString(s):
    return s.encode('utf-8')


# Load wrapper library
# Need to change directory to load modules because of how Windows handles loading DLLs
libraryVer = ""
if platform.system() == "Windows":
    if "64" in platform.python_compiler():  # Running 64 bit python
        libraryVer = "win64"
    else:  # Running 32 bit python
        libraryVer = "win32"
    os.add_dll_directory(str(os.getcwd()) + "\\rpaWrapper\\" + libraryVer)
    rpa = ctypes.CDLL("libwrapper.dll")
# TODO: Add support for Linux and Mac (need to figure out where libraries are stored in downloaded wrappers)
elif platform.system() == "Linux":
    rpa = ctypes.CDLL("")
else:  # On Mac
    rpa = ctypes.CDLL("")

# Declare all required functions from the library (finalize takes no arguments and so is not included)
rpa.initializeWithPath.argtypes = [ctypes.c_char_p, ctypes.c_char_p, ctypes.c_bool]

rpa.configFile.restype = ctypes.c_void_p
rpa.configFileCombustionChamberConditionsSetPressure.argtypes = [ctypes.c_void_p, ctypes.c_double, ctypes.c_char_p]

# These may not be necessary
rpa.configFileLoad.argtypes = [ctypes.c_void_p]
rpa.configFileLoad.restype = ctypes.c_void_p

rpa.performanceCreate.argtypes = [ctypes.c_void_p, ctypes.c_bool, ctypes.c_bool]
rpa.performanceCreate.restype = ctypes.c_void_p

rpa.performanceSolve.argtypes = [ctypes.c_void_p, ctypes.c_bool]
rpa.performanceSolve.restype = ctypes.c_void_p

rpa.performanceGetOF.argtypes = [ctypes.c_void_p]
rpa.performanceGetOF.restype = ctypes.c_double

rpa.performanceDelete.argtypes = [ctypes.c_void_p]

rpa.configFileDelete.argtypes = [ctypes.c_void_p]

rpa.performanceGetDeliveredIspH.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_double, ctypes.c_char_p,
                                            ctypes.c_double]
rpa.performanceGetDeliveredIspH.restype = ctypes.c_double

rpa.performanceGetDeliveredIsp.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_double, ctypes.c_char_p,
                                           ctypes.c_double]
rpa.performanceGetDeliveredIsp.restype = ctypes.c_double


# -----------------------------------------------

class RPA:
    """
        Use the RPA members and methods to get required values for the model
        The rpa object pointing to the library MUST be initialized prior to use of this class
    """

    def __init__(self):
        # Set up configuration object
        self.conf = rpa.configFile()
        rpa.configFileGeneralOptionsSetMultiphase(self.conf, True)
        rpa.configFileGeneralOptionsSetIons(self.conf, True)
        rpa.configFileGeneralOptionsSetFlowSeparation(self.conf, True)
        rpa.configFileNozzleFlowOptionsSetCalculateNozzleFlow(self.conf, True)
        rpa.configFileNozzleFlowOptionsAmbientConditionsSetDeliveredPerformance(self.conf, True)

        self.ccPressure = 0.0
        self.inletContractionAreaRatio = 0.0
        self.exitAreaRatio = 0.0
        self.nozzleHalfAngle = 0.0
        self.ambientPressure = 0.0
        self.OF = 0.0
        self.oxidizerName = ""
        self.oxidizerMassFraction = 0.0
        self.oxidizerPressure = 0.0
        self.fuelNames = []
        self.fuelMassFraction = []
        self.fuelPressure = []
        readRPAConf(self, CONFIG_PATH)

        rpa.configFileCombustionChamberConditionsSetPressure(self.conf, self.ccPressure, "psi")
        rpa.configFileNozzleFlowOptionsSetNozzleInletConditions(self.conf, 0, self.inletContractionAreaRatio, None)
        rpa.configFileNozzleFlowOptionsSetNozzleExitConditions(self.conf, 0, self.exitAreaRatio, None)
        rpa.configFileNozzleFlowOptionsSetAmbientConditions(self.conf, self.ambientPressure, "atm")
        rpa.configFileNozzleFlowOptionsSetConeHalfAngle(self.conf, self.nozzleHalfAngle, "degrees")
        rpa.configFilePropellantSetRatio(self.conf, self.OF, "O/F")
        rpa.configFilePropellantAddOxidizer(self.conf, self.oxidizerName, self.oxidizerMassFraction,
                                            self.oxidizerPressure, "MPa", None, None)
        for fuel in range(len(self.fuelNames)):
            rpa.configFilePropellantAddFuel(self.conf, self.fuelNames[fuel], self.fuelMassFraction[fuel],
                                            self.fuelPressure[fuel], "MPa", None, None)

        # Create performance object from configuration object
        self.perf = rpa.performanceCreate(self.conf, 0, 0)
