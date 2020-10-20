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

def createRPAconf(model, fileName="rpaConf"):
    # TODO: Read from settings file to create RPA config file (store in rpaWrapper folder)
    # I tried to avoid creating another config file... I failed
    # TODO: See if getters and setters in the configFile header file can be used in place of a config file by
    #  customizing an empty conf object
    name = fileName
    if len(name) == 0:
        name = "rpaConf"

    confPath = "rpaWrapper\\" + name
    confFile = None
    try:
        confFile = open(confPath, "w+")
    except OSError as e:
        print("Unable to open or create RPA configuration file:", e)
        exit(1)

    # Get from model the settings that were taken from the configuration file and use to create
    confFile.write('version = 1.2;\nname = "' + name +
                   '";\ninfo = "This file was generated automatically by OpenThrust";\n')

    confFile.write('generalOptions : \n{\n')
    confFile.write('\t')  # Put in all options, beginning each line with a tab
    confFile.write('};\n')

    confFile.write('combustionChamberConditions : \n{\n')
    confFile.write('\t')  # Put in all options, beginning each line with a tab
    confFile.write('};\n')

    confFile.write('propellant : \n{\n')
    confFile.write('\t')  # Put in all options, beginning each line with a tab
    confFile.write('};\n')

    confFile.close()
    return confPath


class RPA(object):
    """
        Use the RPA members and methods to get required values for the model
        The rpa object pointing to the library MUST be initialized prior to use of this class
    """

    # Initialize, don't want to deal with additional config files, information required should be fed into
    # constructor from existing config file (add RPA section if required)
    def __init__(self, confPath):
        # self.conf = rpa.configFileLoad(encodeString(confPath))
        self.conf = rpa.configFile()
        self.perf = rpa.performanceCreate(self.conf, 0, 0)
