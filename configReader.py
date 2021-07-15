import configparser

from constants import CM2_TO_M2, L_TO_M3, PROPERTIES_HEADER, DIMENSIONS_HEADER


def readSettings(newModel, confPath):
    config = configparser.ConfigParser()
    config.read(confPath)

    # Set rocket dimension settings
    newModel.V = float(config[DIMENSIONS_HEADER]["oxidizer tank volume (l)"]) * L_TO_M3
    newModel.nozThroatArea = float(config[DIMENSIONS_HEADER]["nozzle throat area (cm^2)"]) * CM2_TO_M2
    newModel.nozExitArea = float(config[DIMENSIONS_HEADER]["nozzle exit area (cm^2)"]) * CM2_TO_M2
    newModel.Ac = float(config[DIMENSIONS_HEADER]["injector area (cm^2)"]) * CM2_TO_M2

    # Set rocket property settings
    newModel.Cd = float(config[PROPERTIES_HEADER]["injector discharge coefficient"])
    newModel.OF = float(config[PROPERTIES_HEADER]["average oxidizer/fuel ratio"])
    newModel.rampUpTime = float(config[PROPERTIES_HEADER]["ramp up time (s)"])
    newModel.rampDownTime = float(config[PROPERTIES_HEADER]["ramp down time (s)"])

    # Set simulation settings
    newModel.dt = float(config["Simulation Settings"]["time step (s)"])


def readRPAConf(RPAObject, confPath):
    config = configparser.ConfigParser()
    config.read(confPath)

    # Set CC conditions
    RPAObject.ccPressure = float(config[PROPERTIES_HEADER]["chamber pressure (psi)"])

    # Set nozzle flow options
    RPAObject.inletContractionAreaRatio = float(config[DIMENSIONS_HEADER]["inlet contraction area ratio"])
    RPAObject.exitAreaRatio = float(config[DIMENSIONS_HEADER]["exit area ratio"])
    RPAObject.nozzleHalfAngle = float(config[DIMENSIONS_HEADER]["nozzle half angle (degrees)"])
    RPAObject.ambientPressure = float(config[PROPERTIES_HEADER]["ambient pressure (atm)"])
    RPAObject.exitSupersonic = bool(config[PROPERTIES_HEADER]["exit supersonic"])

    # Set propellant information
    RPAObject.OF = float(config[PROPERTIES_HEADER]["average oxidizer/fuel ratio"])
    RPAObject.oxidizerName = config[PROPERTIES_HEADER]["oxidizer label"]
    RPAObject.oxidizerMassFraction = float(config[PROPERTIES_HEADER]["oxidizer mass fraction"])
    RPAObject.oxidizerPressure = float(config[PROPERTIES_HEADER]["oxidizer initial pressure (MPa)"])
    RPAObject.oxidizerTemperature = float(config[PROPERTIES_HEADER]["oxidizer initial temperature (K)"])

    RPAObject.fuelNames = []
    for fuel in config[PROPERTIES_HEADER]["fuel label(s)"].split(','):
        RPAObject.fuelNames.append(fuel.strip())
    RPAObject.fuelMassFraction = []
    for fuel in config[PROPERTIES_HEADER]["fuel mass fraction(s)"].split(','):
        RPAObject.fuelMassFraction.append(float(fuel.strip()))
    RPAObject.fuelPressure = []
    for fuel in config[PROPERTIES_HEADER]["fuel pressure(s) (MPa)"].split(','):
        RPAObject.fuelPressure.append(float(fuel.strip()))
    RPAObject.fuelTemperature = []
    for fuel in config[PROPERTIES_HEADER]["fuel temperature(s) (K)"].split(','):
        RPAObject.fuelTemperature.append(float(fuel.strip()))

    # Set CC information
    RPAObject.numChambers = int(config[DIMENSIONS_HEADER]["number of chambers"])
    RPAObject.CCLength = float(config[DIMENSIONS_HEADER]["chamber length (m)"])
    RPAObject.characteristicLength = bool(config[DIMENSIONS_HEADER]["characteristic length"])
    RPAObject.CCContractionAngle = float(config[DIMENSIONS_HEADER]["contraction angle (degrees)"])
    RPAObject.R1RtRatio = float(config[DIMENSIONS_HEADER]["R1 to Rt ratio"])
    RPAObject.RnRtRatio = float(config[DIMENSIONS_HEADER]["Rn to Rt ratio"])
    RPAObject.R2R2MaxRatio = float(config[DIMENSIONS_HEADER]["R2 to R2_max ratio"])
