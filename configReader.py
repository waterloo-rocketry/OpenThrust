import configparser

from constants import CM2_TO_M2, L_TO_M3


def readSettings(newModel, confPath):
    config = configparser.ConfigParser()
    config.read(confPath)

    # Set rocket dimension settings
    newModel.V = float(config["Rocket Dimensions"]["oxidizer tank volume (l)"]) * L_TO_M3
    newModel.nozThroatArea = float(config["Rocket Dimensions"]["nozzle throat area (cm^2)"]) * CM2_TO_M2
    newModel.nozExitArea = float(config["Rocket Dimensions"]["nozzle exit area (cm^2)"]) * CM2_TO_M2
    newModel.Ac = float(config["Rocket Dimensions"]["injector area (cm^2)"]) * CM2_TO_M2

    # Set rocket property settings
    newModel.Cd = float(config["Rocket Properties"]["injector discharge coefficient"])
    newModel.OF = float(config["Rocket Properties"]["average oxidizer/fuel ratio"])
    newModel.rampUpTime = float(config["Rocket Properties"]["ramp up time (s)"])
    newModel.rampDownTime = float(config["Rocket Properties"]["ramp down time (s)"])

    # Set simulation settings
    newModel.dt = float(config["Simulation Settings"]["time step (s)"])


def readRPAConf(RPAObject, confPath):
    config = configparser.ConfigParser()
    config.read(confPath)

    # Set CC conditions
    RPAObject.ccPressure = float(config["Rocket Properties"]["chamber pressure (psi)"])

    # Set nozzle flow options
    RPAObject.inletContractionAreaRatio = float(config["Rocket Dimensions"]["inlet contraction area ratio"])
    RPAObject.exitAreaRatio = float(config["Rocket Dimensions"]["exit area ratio"])
    RPAObject.nozzleHalfAngle = float(config["Rocket Dimensions"]["nozzle half angle (degrees)"])
    RPAObject.ambientPressure = float(config["Rocket Properties"]["ambient pressure (atm)"])
    RPAObject.exitSupersonic = bool(config["Rocket Properties"]["exit supersonic"])

    # Set propellant information
    RPAObject.OF = float(config["Rocket Properties"]["average oxidizer/fuel ratio"])
    RPAObject.oxidizerName = config["Rocket Properties"]["oxidizer label"]
    RPAObject.oxidizerMassFraction = float(config["Rocket Properties"]["oxidizer mass fraction"])
    RPAObject.oxidizerPressure = float(config["Rocket Properties"]["oxidizer initial pressure (MPa)"])
    RPAObject.oxidizerTemperature = float(config["Rocket Properties"]["oxidizer initial temperature (K)"])

    RPAObject.fuelNames = []
    for fuel in config["Rocket Properties"]["fuel label(s)"].split(','):
        RPAObject.fuelNames += [fuel.strip()]
    RPAObject.fuelMassFraction = []
    for fuel in config["Rocket Properties"]["fuel mass fraction(s)"].split(','):
        RPAObject.fuelMassFraction += [float(fuel.strip())]
    RPAObject.fuelPressure = []
    for fuel in config["Rocket Properties"]["fuel pressure(s) (MPa)"].split(','):
        RPAObject.fuelPressure += [float(fuel.strip())]
    RPAObject.fuelTemperature = []
    for fuel in config["Rocket Properties"]["fuel temperature(s) (K)"].split(','):
        RPAObject.fuelTemperature += [float(fuel.strip())]

    # Set CC information
    RPAObject.numChambers = int(config["Rocket Dimensions"]["number of chambers"])
    RPAObject.CCLength = float(config["Rocket Dimensions"]["chamber length (m)"])
    RPAObject.characteristicLength = bool(config["Rocket Dimensions"]["characteristic length"])
    RPAObject.CCContractionAngle = float(config["Rocket Dimensions"]["contraction angle (degrees)"])
    RPAObject.R1RtRatio = float(config["Rocket Dimensions"]["R1 to Rt ratio"])
    RPAObject.RnRtRatio = float(config["Rocket Dimensions"]["Rn to Rt ratio"])
    RPAObject.R2R2MaxRatio = float(config["Rocket Dimensions"]["R2 to R2_max ratio"])
