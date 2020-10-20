/*
 * RPA - Tool for Rocket Propulsion Analysis
 * RPA wrapper library
 *
 * Copyright 2009,2013 Alexander Ponomarenko.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This software is a commercial product; you can use it either
 * under the terms of the valid RPA SDK License as published
 * at http://www.propulsion-analysis.com/sdk_eula.htm
 * or as a complementary tool under the terms of valid RPA Standard Edition License
 * as published at http://www.propulsion-analysis.com/lic_standard.htm
 * or RPA Lite Edition License as published at http://www.propulsion-analysis.com/lic_lite.htm
 *
 * This program is distributed WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE. See the applicable RPA SDK License, RPA Standard Edition License or
 * RPA Lite Edition License for more details.
 *
 * You should have received a valid copy of the RPA SDK License, RPA Standard Edition License or
 * RPA Lite Edition License along with this program; if not, write to author <contact@propulsion-analysis.com>
 *
 * Please contact author <contact@propulsion-analysis.com> or visit http://www.propulsion-analysis.com
 * if you need additional information or have any questions.
 */

#ifndef RPA_WRAPPER_API_H_
#define RPA_WRAPPER_API_H_

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(_WIN64) || defined(__WIN64__) || defined(WIN64)
	#define DLL __declspec(dllexport)
#else
	#define DLL
#endif

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************

/**
 * Initializes the RPA library, creating loggers and loading database files using following paths:<br>
 * resources/thermo.inp <br>
 * resources/usr_thermo.inp <br>
 * resources/properties.inp <br>
 * resources/usr_properties.inp <br>
 * resources/trans.inp <br>
 *
 * @param consoleOutput if true, duplicate the logging in console
 */
DLL void initialize(bool consoleOutput);

/**
 * Initializes the RPA library, creating loggers and loading database files using specified paths:<br>
 * $(logpath)/rpa_info.log <br>
 * $(respath)/thermo.inp <br>
 * $(respath)/usr_thermo.inp <br>
 * $(respath)/properties.inp <br>
 * $(respath)/usr_properties.inp <br>
 * $(respath)/trans.inp <br>
 *
 * @param respath path to resource directory with database files
 * @param logpath path to log directory
 * @param consoleOutput if true, duplicate the logging in console
 */
DLL void initializeWithPath(const char* respath, const char* logpath, bool consoleOutput);

/*
 * Finalizes the RPA library, closing all open file loggers.
 */
DLL void finalize();

//*****************************************************************************

#ifdef __cplusplus
}
#endif

#endif /* RPA_WRAPPER_API_H_ */
