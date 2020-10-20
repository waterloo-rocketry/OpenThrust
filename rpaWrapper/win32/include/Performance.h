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

#ifndef RPA_WRAPPER_API_PERFORMANCE_H_
#define RPA_WRAPPER_API_PERFORMANCE_H_

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
 * Creates object "Theoretical performance of rocket engine" and returns the pointer thereto.
 * @param dataPtr pointer to configuration object.
 * @param solve if true, calculate the performance.
 * @param optimizePropellant if true, calculates the theoretical performance, optimizing the propellant O/F ratio.
 */
DLL	void* performanceCreate(void* dataPtr, bool solve, bool optimizePropellant);

/**
 * Creates object "Theoretical performance of rocket engine"
 * @param performancePtr pointer to the object "Theoretical performance of rocket engine"
 */
DLL	void performanceDelete(void* performancePtr);

/**
 * Calculate the performance.
 * @param performancePtr pointer to the object "Theoretical performance of rocket engine"
 * @param optimizePropellant if true, calculates the theoretical performance, optimizing the propellant O/F ratio.
 */
DLL	void performanceSolve(void* performancePtr, bool optimizePropellant);

/**
 * Returns mass O/F ratio (either defined or calculated during optimization).
 * @param performancePtr pointer to the object "Theoretical performance of rocket engine"
 */
DLL	double performanceGetOF(void* performancePtr);

/**
 * Returns delivered specific impulse in specified units at given ambient pressure.
 * @param performancePtr pointer to the object "Theoretical performance of rocket engine"
 * @param IspUnits specific impulse units ("m/s"|"ft/s"|"s")
 * @param pa ambient pressure
 * @param pressureUnits ambient pressure units ("Pa"|"MPa"|"atm"|"bar"|"psi"|"psia"|"at"|"kg/cm2")
 * @param phi correction factor; if phi==0, uses correction factors defined in configuration file, or estimated factor, if not defined in configuration file.
 */
DLL	double performanceGetDeliveredIsp(void* performancePtr, const char* IspUnits, double pa, const char* pressureUnits, double phi);


/**
 * Returns delivered throttled specific impulse in specified units at given ambient pressure and given throttle value.
 * @param performancePtr pointer to the object "Theoretical performance of rocket engine"
 * @param IspUnits specific impulse units ("m/s"|"ft/s"|"s")
 * @param pa ambient pressure
 * @param pressureUnits ambient pressure units ("Pa"|"MPa"|"atm"|"bar"|"psi"|"psia"|"at"|"kg/cm2")
 * @param throttleValue throttle value (throttleValue=1.0 at nominal thrust)
 * @param phi correction factor; if phi==0, uses correction factors defined in configuration file, or estimated factor, if not defined in configuration file.
 */
DLL double performanceGetDeliveredIspThrottled(void* performancePtr, const char* IspUnits, double pa, const char* pressureUnits, double throttleValue, double phi);

/**
 * Returns delivered specific impulse in specified units at given altitude.
 * @param performancePtr pointer to the object "Theoretical performance of rocket engine"
 * @param IspUnits specific impulse units ("m/s"|"ft/s"|"s")
 * @param H altitude
 * @param altitudeUnits altitude units ("m"|"mm"|"in"|"ft")
 * @param phi correction factor; if phi==0, uses correction factors defined in configuration file, or estimated factor, if not defined in configuration file.
 */
DLL	double performanceGetDeliveredIspH(void* performancePtr, const char* IspUnits, double H, const char* altitudeUnits, double phi);

/**
 * Returns delivered throttled specific impulse in specified units at given altitude and given throttle value.
 * @param performancePtr pointer to the object "Theoretical performance of rocket engine"
 * @param IspUnits specific impulse units ("m/s"|"ft/s"|"s")
 * @param H altitude
 * @param altitudeUnits altitude units ("m"|"mm"|"in"|"ft")
 * @param throttleValue throttle value (throttleValue=1.0 at nominal thrust)
 * @param phi correction factor; if phi==0, uses correction factors defined in configuration file, or estimated factor, if not defined in configuration file.
 */
DLL double performanceGetDeliveredIspHThrottled(void* performancePtr, const char* IspUnits, double H, const char* altitudeUnits, double throttleValue, double phi);

/**
 * Returns ideal specific impulse in specified units at given ambient pressure.
 * @param performancePtr pointer to the object "Theoretical performance of rocket engine"
 * @param IspUnits specific impulse units ("m/s"|"ft/s"|"s")
 * @param pa ambient pressure
 * @param pressureUnits ambient pressure units ("Pa"|"MPa"|"atm"|"bar"|"psi"|"psia"|"at"|"kg/cm2")
 */
DLL	double performanceGetIdealIsp(void* performancePtr, const char* IspUnits, double pa, const char* units);

/**
 * Returns ideal throttled specific impulse in specified units at given ambient pressure and given throttle value.
 * @param performancePtr pointer to the object "Theoretical performance of rocket engine"
 * @param IspUnits specific impulse units ("m/s"|"ft/s"|"s")
 * @param pa ambient pressure
 * @param pressureUnits ambient pressure units ("Pa"|"MPa"|"atm"|"bar"|"psi"|"psia"|"at"|"kg/cm2")
 * @param throttleValue throttle value (throttleValue=1.0 at nominal thrust)
 */
DLL double performanceGetIdealIspThrottled(void* performancePtr, const char* IspUnits, double pa, const char* pressureUnits, double throttleValue);

/**
 * Returns ideal specific impulse in specified units at given altitude.
 * @param performancePtr pointer to the object "Theoretical performance of rocket engine"
 * @param IspUnits specific impulse units ("m/s"|"ft/s"|"s")
 * @param H altitude
 * @param altitudeUnits altitude units ("m"|"mm"|"in"|"ft")
 */
DLL	double performanceGetIdealIspH(void* performancePtr, const char* IspUnits, double H, const char* altitudeUnits);

/**
 * Returns ideal throttled specific impulse in specified units at given altitude and given throttle value.
 * @param performancePtr pointer to the object "Theoretical performance of rocket engine"
 * @param IspUnits specific impulse units ("m/s"|"ft/s"|"s")
 * @param H altitude
 * @param altitudeUnits altitude units ("m"|"mm"|"in"|"ft")
 * @param throttleValue throttle value (throttleValue=1.0 at nominal thrust)
 */
DLL double performanceGetIdealIspHThrottled(void* performancePtr, const char* IspUnits, double H, const char* altitudeUnits, double throttleValue);

/**
 * Prints out the performance parameters to the log.
 * @param performancePtr pointer to the object "Theoretical performance of rocket engine"
 */
DLL	void performancePrint(void* performancePtr);

//*****************************************************************************

#ifdef __cplusplus
}
#endif

#endif /* RPA_WRAPPER_API_PERFORMANCE_H_ */
