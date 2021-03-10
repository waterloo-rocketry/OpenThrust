import pytest
import os

import getRPA

from constants import BASE_PATH


class TestRPA:
    def test_RPACalls(self):
        rpaPath = os.path.join(BASE_PATH, 'rpaWrapper', getRPA.libraryVer, 'resources').encode('utf-8')
        getRPA.rpa.initializeWithPath(rpaPath, None, 1)

        rpaObject = getRPA.RPA()
        x = rpaObject.solveRPA()

        #with open("info.log") as file:
        #    print(file.readlines())

        getRPA.rpa.finalize()
