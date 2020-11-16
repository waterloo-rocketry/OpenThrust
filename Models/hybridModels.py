import configReader
from constants import ATMOSPHERE_PSI, CONFIG_PATH
from Models.injectorModel import DyerModel


class GeneralModel(object):
    """General model implementation"""

    def __init__(self, mass, temperature, minMass=0, maxIterations=0, dataBases=None, label=""):
        """
            Mass in Kg, temperature in K
        """
        self.DBs = dataBases
        self.initMass = mass
        self.m = mass
        self.initTemp = temperature
        self.minMass = minMass
        self.maxIter = maxIterations

        self.V = 0
        self.nozThroatArea = 0
        self.nozExitArea = 0
        self.Ac = 0
        self.Cd = 0
        self.OF = 0
        self.rampUpTime = 0
        self.rampDownTime = 0
        self.dt = 0
        configReader.readSettings(self, CONFIG_PATH)
        self.injector = DyerModel(self, self.Ac, self.Cd)

        self.running = False
        self.thrust = 0
        self.iterations = 0
        self.t = 0
        self.mdot = 0
        self.P2 = ATMOSPHERE_PSI
        self.Pc = ATMOSPHERE_PSI

        # Initialize data arrays
        self.tArray, self.mArray, self.T1Array = [], [], []
        self.mdotArray, self.thrustArray = [], []
        self.rho1Array, self.PcArray = [], []

        # In case self.V == 0, place in try/except block
        try:
            self.rho1 = self.m / self.V
        except ValueError:
            print("Value error encountered when initializing state, unable to create instance")
            exit(1)

    def timeStep(self):
        self.model()

        self.iterations += 1
        if self.m < self.minMass:
            print("Minimum mass reached, outputting results...")
            # Output results, CSV file?
            return False
        if self.iterations > self.maxIter > 0:
            print("Maximum iterations reached, outputting results...")
            # Output results, CSV file?
            return False

        self.t += self.dt

        return True

    def model(self):
        pass

    def runModel(self):
        self.running = True  # Start running

        while self.running:
            print("Running iteration ", self.iterations)
            self.running = self.timeStep()


class AspireModel(GeneralModel):
    """
       Aspire model (add more comments as developed)
    """
