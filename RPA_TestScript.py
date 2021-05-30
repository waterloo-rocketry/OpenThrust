"""
Pytest doesn't seem to allow for the redirection of output required for this feature when running through it,
therefore this test is kept separately from the others.
"""

import os

import getRPA

from constants import BASE_PATH

rpaPath = os.path.join(BASE_PATH, 'rpaWrapper', getRPA.libraryVer, 'resources').encode('utf-8')
getRPA.rpa.initializeWithPath(rpaPath, None, 1)

rpaObject = getRPA.RPA()
rpaDict = rpaObject.solveRPA()

expectedKeys = ["Initial data", "Combustion chamber", "Combustion chamber end", "Throat", "Nozzle section"]
assert(len(rpaDict) == 5)
assert any(key in rpaDict.keys() for key in expectedKeys)
for key in rpaDict.keys():
    assert(len(rpaDict[key]) > 0)

# Unfortunately, RPA seems to be designed to withhold output of the specific impulse (vac and opt) and thrust
# coefficient (vac and opt) until first print after finalization regardless of what is being printed
getRPA.rpa.finalize()
