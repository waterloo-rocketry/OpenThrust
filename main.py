import os

import getRPA

# To get console output from RPA, change the 0 to a 1
rpaPath = os.path.join('rpaWrapper', getRPA.libraryVer, 'resources').encode('utf-8')
getRPA.rpa.initializeWithPath(rpaPath, None, 0)

# TODO: CLI, any other setup required, link everything together

# At program close/end, clean up the rpa object
getRPA.rpa.finalize()
