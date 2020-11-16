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
