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

#ifndef RPA_WRAPPER_API_CHAMBER_H_
#define RPA_WRAPPER_API_CHAMBER_H_

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
 *
 * The following functions only available in RPA wrapper library Standard Edition.
 *
 */

#ifdef STANDARD_EDITION

/**
 * Creates object "Combustion chamber" and returns the pointers thereto after calculating the geometry.
 * @param applyCorrectionFactors if true, apply correction factors.
 */
DLL void* chamberCreate(void* performancePtr, bool applyCorrectionFactors);

/**
 * Deletes object "Combustion chamber"
 * @param chamberPtr pointer to object "Combustion chamber"
 */
DLL void chamberDelete(void* chamberPtr);

/**
 * Returns throat diameter of combustion chamber in specified units.
 * @param chamberPtr pointer to object "Combustion chamber"
 * @param units throat diameter units ("m"|"mm"|"in"|"ft")
 */
DLL double chamberGetThroatDiameter(void* chamberPtr, const char* units);

/**
 * Returns thrust of combustion chamber in specified units.
 * @param chamberPtr pointer to object "Combustion chamber"
 * @param units thrust units ("N"|"kN"|"kg"|"lbf")
 */
DLL double chamberGetThrust(void* chamberPtr, const char* units);

/**
 * Returns total mass flow rate through the combustion chamber in specified units.
 * @param chamberPtr pointer to object "Combustion chamber"
 * @param units mass flow rate units ("kg/s"|"lbm/s")
 */
DLL double chamberGetMdot(void* chamberPtr, const char* units);

/**
 * Returns oxidizer mass flow rate through the combustion chamber in specified units.
 * @param chamberPtr pointer to object "Combustion chamber"
 * @param units oxidizer mass flow rate units ("kg/s"|"lbm/s")
 */
DLL double chamberGetMdotOxidizer(void* chamberPtr, const char* units);

/**
 * Returns fuel mass flow rate through the combustion chamber in specified units.
 * @param chamberPtr pointer to object "Combustion chamber"
 * @param units fuel mass flow rate units ("kg/s"|"lbm/s")
 */
DLL double chamberGetMdotFuel(void* chamberPtr, const char* units);

//*****************************************************************************

/**
 * Creates object "Nozzle" and returns the pointers thereto after calculating the geometry.
 * @param applyCorrectionFactors if true, apply correction factors.
 */
DLL void* nozzleCreate(void* chamberPtr, bool applyCorrectionFactors);

/**
 * Deletes object "Nozzle".
 * @param nozzlePtr pointer to object "Nozzle"
 */
DLL void nozzleDelete(void* nozzlePtr);

/**
 * Returns nozzle exit diameter in specified units.
 * @param nozzlePtr pointer to object "Nozzle"
 * @param units nozzle exit diameter units ("m"|"mm"|"in"|"ft")
 */
DLL double nozzleGetExitDiameter(void* nozzlePtr, const char* units);

/**
 * Returns nozzle length in specified units.
 * @param nozzlePtr pointer to object "Nozzle"
 * @param units nozzle length units ("m"|"mm"|"in"|"ft")
 */
DLL double nozzleGetLength(void* nozzlePtr, const char* units);

#endif

//*****************************************************************************

#ifdef __cplusplus
}
#endif

#endif /* RPA_WRAPPER_API_CHAMBER_H_ */
