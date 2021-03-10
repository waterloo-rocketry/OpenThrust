import os

import getRPA

from constants import BASE_PATH

rpaPath = os.path.join(BASE_PATH, 'rpaWrapper', getRPA.libraryVer, 'resources').encode('utf-8')
getRPA.rpa.initializeWithPath(rpaPath, None, 1)

rpaObject = getRPA.RPA()
x = rpaObject.solveRPA()

print("x = ", x)

#with open("info.log") as file:
#    print(file.readlines())

getRPA.rpa.finalize()
