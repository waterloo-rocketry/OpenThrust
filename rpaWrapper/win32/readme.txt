The RPA Wrapper is a RPA complementary tool containing development library and examples.

This software is a commercial product. You can use it either under the terms of the valid
RPA SDK License as published at http://www.propulsion-analysis.com/sdk_eula.htm
or as a complementary tool under the terms of valid RPA Standard Edition License
as published at http://www.propulsion-analysis.com/lic_standard.htm
or RPA Lite Edition License as published at http://www.propulsion-analysis.com/lic_lite.htm

Prerequisite
------------

- OS: Linux 32/64, Mac OS X or Windows Xp/Vista/7 x86/x86-64 (please download the corresponding
version of wrapper from http://www.propulsion-analysis.com).

If you want to use the RPA Wrapper to develop programs written in C/C++:

- C/C++ compiler: 
	GNU C++ (Linux, Mac OS X or Windows), 
	Open64 C++ (Linux), 
	Visual C++ 2010 (Windows) 
	Intel C++ (Linux or Windows).
- GNU make utility to compile examples.

Note: 
On Windows, you can get GNU make for Windows from http://gnuwin32.sourceforge.net/packages/make.htm 

If you want to use the RPA Wrapper to develop programs written in C/C++:

- Python interpreter for testing the wrapper with program written in Python.

Note:
If you are using 32-bit version of Python on 64-bit version of Windows, you have to download 
32-bit version of RPA Wrapper, even if you are already using 64-bit version of RPA. 

Installation
------------

Extract ZIP file to any folder on your hard disc.

RPA Wrapper for Windows depends on MS VC++ 2010 runtime libraries. If you are using RPA Lite v.1.2.7+ or 
RPA Standard v.2.0.5+, you have already installed these libraries.  

If your computer does not have it installed, download and install appropriate redistributable 
runtime components from Microsoft download center 
	for x86 (download size 4.8 MB):	http://www.microsoft.com/en-us/download/details.aspx?id=5555 
	for x64 (download size 5.5 MB): http://www.microsoft.com/en-us/download/details.aspx?id=14632

Examples
--------							
		
This RPA Wrapper contains following examples:

	wrapper_client.cpp	This example shows how to use wrapper for development programs in C/C++

	wrapper_client_1.py	These examples show how to use wrapper for development programs in Python
	wrapper_client_2.py
	wrapper_client_3.py
	wrapper_client_4.py
	wrapper_client_5.py
		

How to use build and execute examples
-------------------------------------

Open command line console (cmd) and change to RPA Wrapper directory.

Building C example on Linux:

	make -f Makefile_gcc build

Running C example on Linux:

	make -f Makefile_gcc execute
or
	LD_LIBRARY_PATH=../:$LD_LIBRARY_PATH ./wrapper_client.exe

Building C example on Windows:

	make -f Makefile_win build

Running C example on Windows:

	make -f Makefile_win execute
or
	set PATH=%PATH%;..\ 
	wrapper_client.exe

Running Python example on Linux:

	LD_LIBRARY_PATH=../:$LD_LIBRARY_PATH python wrapper_client_1.py

Running Python example on Windows:

	set PATH=%PATH%;..\ 
	python wrapper_client_1.py
