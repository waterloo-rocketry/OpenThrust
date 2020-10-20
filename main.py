import getRPA

# To get console output from RPA, change the 0 to a 1
getRPA.rpa.initializeWithPath("rpaWrapper\\" + getRPA.libraryVer + "\\resources", None, 0)

# TODO: CLI, any other setup required, link everything together

# At program close/end, clean up the rpa object
getRPA.rpa.finalize()
