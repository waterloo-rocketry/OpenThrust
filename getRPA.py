import platform
import ctypes
import os
import sys
import contextlib

from configReader import readRPAConf
from constants import CONFIG_PATH, BASE_PATH
from utils import GrabOutput


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
    os.add_dll_directory(os.path.join(BASE_PATH, "rpaWrapper", libraryVer))
    rpa = ctypes.CDLL("libwrapper.dll")
# TODO: Add support for Linux and Mac (need to figure out where libraries are stored in downloaded wrappers)
elif platform.system() == "Linux":
    rpa = ctypes.CDLL("")
else:  # On Mac
    rpa = ctypes.CDLL("")

# Declare all required functions from the library (finalize takes no arguments and so is not included)
rpa.initializeWithPath.argtypes = [ctypes.c_char_p, ctypes.c_char_p, ctypes.c_bool]

rpa.configFile.restype = ctypes.c_void_p

rpa.configFileLoad.argtypes = [ctypes.c_void_p]
rpa.configFileLoad.restype = ctypes.c_void_p

rpa.configFileGeneralOptionsSetMultiphase.argtypes = [ctypes.c_void_p, ctypes.c_bool]
rpa.configFileGeneralOptionsSetIons.argtypes = [ctypes.c_void_p, ctypes.c_bool]
rpa.configFileGeneralOptionsSetFlowSeparation.argtypes = [ctypes.c_void_p, ctypes.c_bool]
rpa.configFileNozzleFlowOptionsSetCalculateNozzleFlow.argtypes = [ctypes.c_void_p, ctypes.c_bool]
rpa.configFileNozzleFlowOptionsAmbientConditionsSetDeliveredPerformance.argtypes = [ctypes.c_void_p, ctypes.c_bool]

rpa.configFileCombustionChamberConditionsSetPressure.argtypes = [ctypes.c_void_p, ctypes.c_double, ctypes.c_char_p]

rpa.configFileNozzleFlowOptionsSetNozzleInletConditions.argtypes = [ctypes.c_void_p, ctypes.c_uint, ctypes.c_double,
                                                                    ctypes.c_char_p]
rpa.configFileNozzleFlowOptionsSetNozzleExitConditions.argtypes = [ctypes.c_void_p, ctypes.c_uint, ctypes.c_double,
                                                                   ctypes.c_char_p]
rpa.configFileNozzleFlowOptionsSetAmbientConditions.argtypes = [ctypes.c_void_p, ctypes.c_double, ctypes.c_char_p]
rpa.configFileNozzleFlowOptionsSetConeHalfAngle.argtypes = [ctypes.c_void_p, ctypes.c_double, ctypes.c_char_p]

rpa.configFilePropellantSetRatio.argtypes = [ctypes.c_void_p, ctypes.c_double, ctypes.c_char_p]
rpa.configFilePropellantAddOxidizer.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_double, ctypes.c_double,
                                                ctypes.c_char_p, ctypes.c_double, ctypes.c_char_p]
rpa.configFilePropellantAddFuel.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_double, ctypes.c_double,
                                            ctypes.c_char_p, ctypes.c_double, ctypes.c_char_p]

rpa.performanceCreate.argtypes = [ctypes.c_void_p, ctypes.c_bool, ctypes.c_bool]
rpa.performanceCreate.restype = ctypes.c_void_p

rpa.performanceSolve.argtypes = [ctypes.c_void_p, ctypes.c_bool]
rpa.performanceSolve.restype = ctypes.c_void_p

rpa.performancePrint.argtypes = [ctypes.c_void_p]
rpa.performancePrint.restype = ctypes.c_void_p

rpa.performanceGetOF.argtypes = [ctypes.c_void_p]
rpa.performanceGetOF.restype = ctypes.c_double

rpa.performanceDelete.argtypes = [ctypes.c_void_p]
rpa.configFileDelete.argtypes = [ctypes.c_void_p]

rpa.configFileDelete.argtypes = [ctypes.c_void_p]

rpa.performanceGetDeliveredIspH.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_double, ctypes.c_char_p,
                                            ctypes.c_double]
rpa.performanceGetDeliveredIspH.restype = ctypes.c_double

rpa.performanceGetDeliveredIsp.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_double, ctypes.c_char_p,
                                           ctypes.c_double]
rpa.performanceGetDeliveredIsp.restype = ctypes.c_double


# -----------------------------------------------

def parseRPA(outputData):
    # Create a dictionary containing all values from the RPA output
    values = {}
    exclude = ["ERROR", "WARNING", "Case name"]
    excludeSubsection = ["Combustion composition"]
    outputData = outputData.splitlines()
    currentSection = None
    headerTitle = None
    newSection = False
    header = False
    units = False
    separationCount = 0
    for line in range(len(outputData)):
        if len(outputData[line].strip()) > 0 and not any(word in outputData[line] for word in exclude):
            if '*' in outputData[line].strip():
                if not newSection:
                    newSection = True
                    header = False
                    separationCount = 0
                else:
                    newSection = False
                continue
            if newSection:
                currentSection = outputData[line].strip()
                values[currentSection] = {}
                continue
            if not header:
                header = True
                headerTitle = outputData[line].strip()[:-1]
                continue
            if "--" in outputData[line].strip():
                if header and separationCount < 2:
                    separationCount += 1
                    if separationCount == 1 and not "Combustion parameters" in headerTitle:
                        units = True
                    else:
                        units = False
                else:
                    separationCount = 0
                    header = False
                continue
            elif not any(section in headerTitle for section in excludeSubsection) and not units:
                if ":" in outputData[line]:
                    newEntry = outputData[line].split(":")
                    values[currentSection][newEntry[0].strip()] = [l.strip() for l in newEntry[1].split()]
                else:
                    newEntry = [l.strip() for l in outputData[line].split()]
                    # If the first value in newEntry is a number, don't include this line (just unit conversion of
                    # previous entry)
                    try:
                        float(newEntry[0])
                    except ValueError:
                        values[currentSection][newEntry[0]] = newEntry[1:]
    return values


class RPA:
    """
        Use the RPA members and methods to get required values for the model
        The rpa object pointing to the library MUST be initialized prior to use of this class
    """

    def __init__(self, confPath=CONFIG_PATH):
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
        self.exitSupersonic = False
        self.OF = 0.0
        self.oxidizerName = ""
        self.oxidizerMassFraction = 0.0
        self.oxidizerPressure = 0.0
        self.fuelNames = []
        self.fuelMassFraction = []
        self.fuelPressure = []
        self.numChambers = 0
        self.CCLength = 0.0
        self.characteristicLength = False
        self.CCContractionAngle = 0.0
        self.R1RtRatio = 0.0
        self.RnRtRatio = 0.0
        self.R2R2MaxRatio = 0.0
        self.oxidizerTemperature = 0.0
        self.fuelTemperature = 0.0

        readRPAConf(self, confPath)

        rpa.configFileCombustionChamberConditionsSetPressure(self.conf, self.ccPressure, encodeString("psi"))
        rpa.configFileNozzleFlowOptionsSetNozzleInletConditions(self.conf, 0, self.inletContractionAreaRatio, None)
        rpa.configFileNozzleFlowOptionsSetNozzleExitConditions(self.conf, 0, self.exitAreaRatio, None)
        rpa.configFileNozzleFlowOptionsSetAmbientConditions(self.conf, self.ambientPressure, encodeString("atm"))
        rpa.configFileNozzleFlowOptionsSetConeHalfAngle(self.conf, self.nozzleHalfAngle, encodeString("degrees"))
        rpa.configFilePropellantSetRatio(self.conf, self.OF, encodeString("O/F"))
        rpa.configFilePropellantAddOxidizer(self.conf, encodeString(self.oxidizerName), self.oxidizerMassFraction,
                                            self.oxidizerPressure, encodeString("MPa"), self.oxidizerTemperature,
                                            encodeString('K'))
        for fuel in range(len(self.fuelNames)):
            rpa.configFilePropellantAddFuel(self.conf, encodeString(self.fuelNames[fuel]), self.fuelMassFraction[fuel],
                                            self.fuelPressure[fuel], encodeString("MPa"), self.fuelTemperature[fuel],
                                            encodeString('K'))

        # self.conf = rpa.configFileLoad(encodeString(os.path.join(BASE_PATH, "Vidar3RPA.cfg")))
        # Create performance object from configuration object
        self.perf = rpa.performanceCreate(self.conf, 0, 0)
        self.values = {}

    def solveRPA(self, perfObject=None, optimizePropellant=False):
        if perfObject is None:
            rpa.performanceSolve(self.perf, optimizePropellant)
        else:
            rpa.performanceSolve(perfObject, optimizePropellant)
        buffer = GrabOutput()
        with buffer:
            rpa.performancePrint(self.perf)
        return parseRPA(buffer.capturedOutput)

    def updatePressure(self, newPressure):
        self.perf = rpa.performanceCreate(self.conf, 0, 0)
        rpa.configFileCombustionChamberConditionsSetPressure(self.conf, self.ccPressure, encodeString("psi"))
