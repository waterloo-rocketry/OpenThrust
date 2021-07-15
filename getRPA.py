import platform
import ctypes
import os

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
    # Exclude some lines that are outputted by the RPA library but don't contain useful information
    exclude = ["ERROR", "WARNING", "Case name"]
    excludeSubsection = ["Combustion composition"]
    # Split the string fed in at the newline characters, creating an array of strings
    outputData = outputData.splitlines()
    # Declare some variables that will be used further down
    currentSection = None
    headerTitle = None
    newSection = False
    header = False
    units = False
    separationCount = 0
    # Iterate through each line of the data
    for line in outputData:
        # Ignore any lines that are empty or include any of the excluded markers
        if len(line.strip()) > 0 and not any(word in line for word in exclude):
            # RPA uses a line of '*'s before and after the title of each main section
            if '*' in line.strip():
                # If the a new section was not already opened, a line of '*'s indicates the beginning of a new section
                if not newSection:
                    newSection = True
                    header = False
                    separationCount = 0
                # Otherwise the line indicates the end of a new section
                else:
                    newSection = False
                continue
            # If a new section was opened but not closed yet, this line is the name of the section. Introduce it as a
            # key for an empty dictionary within the main dictionary
            if newSection:
                currentSection = line.strip()
                values[currentSection] = {}
                continue
            # If the new section has been closed but header has not yet been set, this line is a header for a subsection
            if not header:
                header = True
                headerTitle = line.strip()[:-1]
                continue
            # RPA uses a line of '--'s to delineate subsections and column titles
            if "--" in line.strip():
                if header and separationCount < 2:
                    separationCount += 1
                    # If this is the first line of '--'s, a header was already defined, and the header is not
                    # 'Combustion parameters' (the only subsection to break this rule), the lines until the next line
                    # of '--'s is units and/or the title of columns. Otherwise it is not, make sure units is set to
                    # false
                    if separationCount == 1 and not "Combustion parameters" in headerTitle:
                        units = True
                    else:
                        units = False
                # Otherwise this is indicating the end of a subsection, reset the separation count and set header to
                # false
                else:
                    separationCount = 0
                    header = False
                continue
            # If none of the header title is in the list of excluded markers and the units flag has not been set,
            # this is a relevant value that needs to be added to the subsection dictionary
            elif not any(section in headerTitle for section in excludeSubsection) and not units:
                # Some lines separate the parameter and value by a ':', if so split across this and write the parameter
                # and value into the current subsection dictionary
                if ":" in line:
                    newEntry = line.split(":")
                    values[currentSection][newEntry[0].strip()] = [l.strip() for l in newEntry[1].split()]
                # Otherwise the parameter and value are only split by whitespace, split the line and write the parameter
                # and value into the current subsection dictionary
                else:
                    newEntry = [l.strip() for l in line.split()]
                    # If the first value in newEntry is a number, don't include this line (just unit conversion of
                    # previous entry)
                    try:
                        float(newEntry[0])
                    except ValueError:
                        values[currentSection][newEntry[0]] = newEntry[1:]
    # Return the completed dictionary of values
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

        # Initialize a bunch of variables to be read in
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

        # Read in the values for the above variables from the configuration file
        readRPAConf(self, confPath)

        # Set configuration object according to values read from settings file
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
        rpa.configFileCombustionChamberConditionsSetPressure(self.conf, newPressure, encodeString("psi"))
        return self.solveRPA()
