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

#ifndef RPA_WRAPPER_API_NOZZLESTATION_H_
#define RPA_WRAPPER_API_NOZZLESTATION_H_

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
 * Creates object "Nozzle Station" and returns the pointer thereto.
 * @param performancePtr pointer to object "Performance"
 * @param condition condition to locate the nozzle station (see conditionType)
 * @param conditionUnits units of pressure condition ("Pa"|"MPa"|"atm"|"bar"|"psi"|"psia"|"at"|"kg/cm2")
 * @param conditionType 1-nozzle inlet, 2-nozzle throat, 3-nozzle exit, 4-pressure, 5-pressure ratio, 6-area ratio subsonic, 7-area ratio supersonic
 * @param checkForFreezing if true, allow combustion "freezing"
 * @param checkForOverexpansion if true, allow flow separation
 * @param pa ambient pressure
 * @param paUnits units of ambient pressure ("Pa"|"MPa"|"atm"|"bar"|"psi"|"psia"|"at"|"kg/cm2")
 * @param withTransportProperties if true, calculates transport properties of combustion mixture as well.
 * @return pointer to object "Nozzle Station"
 */
DLL void* nozzleStationCreate(void* performancePtr, double condition, const char* conditionUnits, int conditionType, bool checkForFreezing, bool checkForOverexpansion, double pa, const char* paUnits, bool withTransportProperties);

/**
 * Deletes object "Nozzle Station"
 * @param stationPtr pointer to object "Nozzle Station"
 */
DLL void nozzleStationDelete(void* stationPtr);

/**
 * Returns area ratio.
 * @param stationPtr pointer to object "Nozzle Station"
 * @return double area ratio.
 */
DLL double nozzleStationGetAr(void* stationPtr);

/**
 * Returns pressure ratio.
 * @param stationPtr pointer to object "Nozzle Station"
 * @return double pressure ratio.
 */
DLL double nozzleStationGetPi(void* stationPtr);

/**
 * Returns pressure.
 * @param stationPtr pointer to object "Nozzle Station"
 * @param units pressure units ("Pa"|"MPa"|"atm"|"bar"|"psi"|"psia"|"at"|"kg/cm2")
 * @return double pressure
 */
DLL double nozzleStationGetP(void* stationPtr, const char* units);

/**
 * Returns gas velocity.
 * @param stationPtr pointer to object "Nozzle Station"
 * @param units velocity units ("m/s"|"ft/s")
 * @return double
 */
DLL double nozzleStationGetW(void* stationPtr, const char* units);

/**
 * Return Mach number.
 * @param stationPtr pointer to object "Nozzle Station"
 * @return double
 */
DLL double nozzleStationGetMach(void* stationPtr);

/**
 * Returns specific area.
 * @param stationPtr pointer to object "Nozzle Station"
 * @return double
 */
DLL double nozzleStationGetF(void* stationPtr);

/**
 * Returns mass flux.
 * @param stationPtr pointer to object "Nozzle Station"
 * @param units ("kg/(m2-s)"|"lbm/(ft2-s)")
 * @return double
 */
DLL double nozzleStationGetMr(void* stationPtr, const char* units);

/**
 * Returns temperature.
 * @param stationPtr pointer to object "Nozzle Station"
 * @units ("K"|"C"|"F")
 * @return temperature.
 */
DLL double nozzleStationGetT(void* stationPtr, const char* units);

/**
 * Returns enthalpy.
 * @param stationPtr pointer to object "Nozzle Station"
 * @param units ("J/mol"|"Btu/lb-mol"|"kJ/kg"|"Btu/lbm")
 * @return double.
 */
DLL double nozzleStationGetH(void* stationPtr, const char* units);

/**
 * Returns entropy.
 * @param stationPtr pointer to object "Nozzle Station"
 * @param units ("J/(mol K)"|"Btu/(lb mol R)"|"kJ/(kg K)"|"Btu/(lbm K)")
 * @return double.
 */
DLL double nozzleStationGetS(void* stationPtr, const char* units);

/**
 * Returns heat capacity at constant pressure.
 * @param stationPtr pointer to object "Nozzle Station"
 * @param units ("J/(mol K)"|"Btu/(lb-mol R)"|"kJ/(kg K)"|"Btu/(lbm R)")
 * @return heat capacity.
 */
DLL double nozzleStationGetCp(void* stationPtr, const char* units);

/**
 * Returns heat capacity at constant volume.
 * @param stationPtr pointer to object "Nozzle Station"
 * @param units ("J/(mol K)"|"Btu/(lb-mol R)"|"kJ/(kg K)"|"Btu/(lbm R)")
 * @return heat capacity.
 */
DLL double nozzleStationGetCv(void* stationPtr, const char* units);

/**
 * Return gas constant of reacting mixture.
 * @param stationPtr pointer to object "Nozzle Station"
 * @param units ("J/(mol K)"|"Btu/(lb-mol R)"|"kJ/(kg K)"|"Btu/(lbm R)")
 * @return double
 */
DLL double nozzleStationGetR(void* stationPtr, const char* units);

/**
 * Returns the molar mass of reacting mixture.
 * @param stationPtr pointer to object "Nozzle Station"
 * @param units ("kg/mol"|"lbm/lb-mol")
 * @return double
 */
DLL double nozzleStationGetMm(void* stationPtr, const char* units);

/**
 * Return \f$ k = - \frac{\gamma}{{\left(void* stationPtr, \frac{\delta ln V}{\delta ln p}\right)}_T} \f$.
 * @param stationPtr pointer to object "Nozzle Station"
 * @return double
 */
DLL double nozzleStationGetK(void* stationPtr);

/**
 * Returns velocity of sound.
 * @param stationPtr pointer to object "Nozzle Station"
 * @param units ("m/s"|"ft/s")
 * @return double
 */
DLL double nozzleStationGetA(void* stationPtr, const char* units);

/**
 * Returns density.
 * @param stationPtr pointer to object "Nozzle Station"
 * @param units ("kg/m^3"|"lbm/ft^3")
 * @return double
 */
DLL double nozzleStationGetRho(void* stationPtr, const char* units);

/**
 * Returns viscosity.
 * Not available if nozzle station calculated with option withTransportProperties=false.
 * @param stationPtr pointer to object "Nozzle Station"
 * @param units ("kg/(m-s)"|"lb/(ft s)")
 * @return double
 */
DLL double nozzleStationGetV(void* stationPtr, const char* units);

/**
 * Returns frozen conductivity.
 * Not available if nozzle station calculated with option withTransportProperties=false.
 * @param stationPtr pointer to object "Nozzle Station"
 * @param units ("W/(m K)"|"Btu/(hr ft R)")
 * @return double
 */
DLL double nozzleStationGetCFr(void* stationPtr, const char* units);

/**
 * Returns frozen specific heat at constant pressure.
 * Not available if nozzle station calculated with option withTransportProperties=false.
 * @param stationPtr pointer to object "Nozzle Station"
 * @param units ("J/(mol K)"|"Btu/(lb-mol R)"|"kJ/(kg K)"|"Btu/(lbm R)")
 * @return double
 */
DLL double nozzleStationGetCpFr(void* stationPtr, const char* units);

/**
 * Returns frozen Prandtl number (void* stationPtr, Pr).
 * Not available if nozzle station calculated with option withTransportProperties=false.
 * @param stationPtr pointer to object "Nozzle Station"
 * @return double
 */
DLL double nozzleStationGetPrFr(void* stationPtr, const char* units);

/**
 * Returns effective conductivity.
 * Not available if nozzle station calculated with option withTransportProperties=false.
 * @param stationPtr pointer to object "Nozzle Station"
 * @param units ("W/(m K)"|"Btu/(hr ft R)")
 * @return double
 */
DLL double nozzleStationGetCEql(void* stationPtr, const char* units);

/**
 * Returns effective specific heat at constant pressure.
 * Not available if nozzle station calculated with option withTransportProperties=false.
 * @param stationPtr pointer to object "Nozzle Station"
 * @param units ("J/(mol K)"|"Btu/(lb-mol R)"|"kJ/(kg K)"|"Btu/(lbm R)")
 * @return double
 */
DLL double nozzleStationGetCpEql(void* stationPtr, const char* units);

/**
 * Returns effective Prandtl number (void* stationPtr, Pr).
 * Not available if nozzle station calculated with option withTransportProperties=false.
 * @param stationPtr pointer to object "Nozzle Station"
 * @return double
 */
DLL double nozzleStationGetPrEql(void* stationPtr, const char* units);

#endif

//*****************************************************************************

#ifdef __cplusplus
}
#endif

#endif /* NOZZLESTATION_H_ */
