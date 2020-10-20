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

#ifndef RPA_WRAPPER_API_EQUILIBRIUM_H_
#define RPA_WRAPPER_API_EQUILIBRIUM_H_

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
 * Creates object "Propellant" and returns the pointer thereto.
 * @param OF_ratio O/F ratio.
 * @return pointer to object "Propellant"
 */
DLL void* propellantCreateOF(double OF_ratio);

/**
 * Creates object "Propellant" and returns the pointer thereto.
 * @param oxidizerExcessCoefficient oxidizer excess coefficient (value 1.0 corresponds to stoichiometric ratio).
 * @return pointer to object "Propellant"
 */
DLL void* propellantCreateOxExcess(double oxidizerExcessCoefficient);

/**
 * Deletes object "Propellant"
 * @param propPtr pointer to the object "Propellant"
 */
DLL void propellantDelete(void* propPtr);

/**
 * Adds specified component to oxidizer.
 * @param propPtr pointer to the object "Propellant"
 * @param componentName name of component.
 * @param massFraction mass fraction of component within oxidizer.
 * @return true if component is added without errors.
 */
DLL bool propellantAddOxidizerComponent(void* propPtr, const char* componentName, double massFraction);

/**
 * Adds specified component to oxidizer.
 * @param propPtr pointer to the object "Propellant"
 * @param componentName name of component.
 * @param p initial pressure.
 * @param pressureUnits pressure units ("Pa"|"MPa"|"atm"|"bar"|"psi"|"psia"|"at"|"kg/cm2")
 * @param T initial temperature.
 * @param temperatureUnits temperature units ("K"|"C"|"F")
 * @param mf mass fraction of component within oxidizer.
 * @return true if component is added without errors.
 */
DLL bool propellantAddOxidizerComponentPT(void* propPtr, const char* componentName, double massFraction, double p, const char* pressureUnits, double T, const char* temperatureUnits);

/**
 * Adds specified component to fuel.
 * @param propPtr pointer to the object "Propellant"
 * @param componentName name of component.
 * @param massFraction mass fraction of component within fuel.
 * @return true if component is added without errors.
 */
DLL bool propellantAddFuelComponent(void* propPtr, const char* componentName, double massFraction);

/**
 * Adds specified component to fuel.
 * @param propPtr pointer to the object "Propellant"
 * @param componentName name of component.
 * @param p initial pressure.
 * @param pressureUnits pressure units ("Pa"|"MPa"|"atm"|"bar"|"psi"|"psia"|"at"|"kg/cm2")
 * @param T initial temperature.
 * @param temperatureUnits temperature units ("K"|"C"|"F")
 * @param mf mass fraction of component within fuel.
 * @return true if component is added without errors.
 */
DLL bool propellantAddFuelComponentPT(void* propPtr, const char* componentName, double massFraction, double p, const char* pressureUnits, double T, const char* temperatureUnits);

/*
 * Returns propellant enthalpy.
 * @param propPtr pointer to the object "Propellant"
 * @param enthalpyUnits units ("J/mol"|"Btu/lb-mol"|"kJ/kg"|"Btu/lbm")
 * @return double
 */
DLL double propellantGetH(void* propPtr, const char* enthalpyUnits);

//*****************************************************************************

/**
 * Creates object "Mixture" and returns the pointer thereto.
 * @return pointer to object "Mixture"
 */
DLL void* mixtureCreate();

/**
 * Deletes object "Propellant"
 * @param mixturePtr pointer to the object "Mixture"
 */
DLL void mixtureDelete(void* mixturePtr);

/**
 * Adds specified component to mixture.
 * @param mixturePtr pointer to the object "Mixture"
 * @param componentName name of component.
 * @param massFraction mass fraction of component within mixture.
 * @return true if component is added without errors.
 */
DLL bool mixtureAddComponent(void* mixturePtr, const char* componentName, double massFraction);

/**
 * Adds specified component to mixture.
 * @param mixturePtr pointer to the object "Mixture"
 * @param componentName name of component.
 * @param p initial pressure.
 * @param pressureUnits pressure units ("Pa"|"MPa"|"atm"|"bar"|"psi"|"psia"|"at"|"kg/cm2")
 * @param T initial temperature.
 * @param temperatureUnits temperature units ("K"|"C"|"F")
 * @param mf mass fraction of component within mixture.
 * @return true if component is added without errors.
 */
DLL bool mixtureAddComponentPT(void* mixturePtr, const char* componentName, double massFraction, double p, const char* pressureUnits, double T, const char* temperatureUnits);

/*
 * Returns propellant enthalpy.
 * @param propPtr pointer to the object "Propellant"
 * @param enthalpyUnits units ("J/mol"|"Btu/lb-mol"|"kJ/kg"|"Btu/lbm")
 * @return double
 */
DLL double mixtureGetH(void* propPtr, const char* enthalpyUnits);


//*****************************************************************************

/**
 * Creates object "Equilibrium" and returns the pointer thereto.
 * @param propPtr pointer to the object "Propellant"
 * @param multiphase if true, allow multiphase reacting mixtures.
 * @param ions if true, allow ionized reacting mixtures.
 * @return pointer to object "Equilibrium"
 */
DLL void* equilibriumCreateFromPropellant(void* propPtr, bool multiphase, bool ions);

/**
 * Creates object "Equilibrium" and returns the pointer thereto.
 * @param mixturePtr pointer to the object "Mixture"
 * @param multiphase if true, allow multiphase reacting mixtures.
 * @param ions if true, allow ionized reacting mixtures.
 * @return pointer to object "Equilibrium"
 */
DLL void* equilibriumCreateFromMixture(void* mixturePtr, bool multiphase, bool ions);

DLL void* equilibriumCreateFromNozzleStation(void* stationPtr);

/**
 * Deletes object "Equilibrium".
 * @param equilibriumPtr pointer to object "Equilibrium"
 */
DLL void equilibriumDelete(void* propPtr);

/**
 * Assigns the initial temperature of reaction.
 *
 * @param equilibriumPtr pointer to object "Equilibrium"
 * @param T temperature.
 * @param temperatureUnits temperature units ("K"|"C"|"F")
 * @param setIsothermic if true, switch the process type to isothermic.
 */
DLL void equilibriumSetT(void* equilibriumPtr, double T, const char* temperatureUnits, bool setIsothermic);

/**
 * Returns the temperature of reaction.
 *
 * @param equilibriumPtr pointer to object "Equilibrium"
 * @param temperatureUnits temperature units ("K"|"C"|"F")
 * @return double
 */
DLL double equilibriumGetT(void* equilibriumPtr, const char* temperatureUnits);

/**
 * Assigns the pressure of reaction.
 *
 * @param equilibriumPtr pointer to object "Equilibrium"
 * @param p pressure
 * @param pressureUnits pressure units ("Pa"|"MPa"|"atm"|"bar"|"psi"|"psia"|"at"|"kg/cm2")
 */
DLL void equilibriumSetP(void* equilibriumPtr, double p, const char* pressureUnits);

/**
 * Returns the pressure of reaction.
 *
 * @param equilibriumPtr pointer to object "Equilibrium"
 * @param pressureUnits pressure units ("Pa"|"MPa"|"atm"|"bar"|"psi"|"psia"|"at"|"kg/cm2")
 * @return double
 */
DLL double equilibriumGetP(void* equilibriumPtr, const char* pressureUnits);

/**
 * Assigns the enthalpy of the mixture and switches the type of process to isenthalpic.
 *
 * @param equilibriumPtr pointer to object "Equilibrium"
 * @param H enthalpy
 * @param enthalpyUnits units ("J/mol"|"Btu/lb-mol"|"kJ/kg"|"Btu/lbm")
 */
DLL void equilibriumSetH(void* equilibriumPtr, double H, const char* enthalpyUnits);

/**
 * Returns the enthalpy of reacting mixture.
 *
 * @param equilibriumPtr pointer to object "Equilibrium"
 * @param enthalpyUnits units ("J/mol"|"Btu/lb-mol"|"kJ/kg"|"Btu/lbm")
 * @return double
 */
DLL double equilibriumGetH(void* equilibriumPtr, const char* enthalpyUnits);

/**
 * Assigns the entropy of the mixture and switches the type of process to isentropic.
 *
 * @param equilibriumPtr pointer to object "Equilibrium"
 * @qparam S entropy
 * @param entropyUnits units ("J/(mol K)"|"Btu/(lb mol R)"|"kJ/(kg K)"|"Btu/(lbm K)")
 */
DLL void equilibriumSetS(void* equilibriumPtr, double S, const char* entropyUnits);

/**
 * Returns the entropy of reacting mixture.
 *
 * @param equilibriumPtr pointer to object "Equilibrium"
 * @param entropyUnits units ("J/(mol K)"|"Btu/(lb mol R)"|"kJ/(kg K)"|"Btu/(lbm K)")
 * @return double
 */
DLL double equilibriumGetS(void* equilibriumPtr, const char* entropyUnits);

/**
 * Solves the configured equilibrium problem.
 *
 * @param equilibriumPtr pointer to object "Equilibrium"
 * @param startWithCondensed if true. allow condensed species at first iteration.
 * @param withTransportProperties if true, calculates transport properties as well.
 */
DLL void equilibriumSolve(void* equilibriumPtr, bool startWithCondensed, bool withTransportProperties);

/**
 * Returns true if equilibrium problem is solved successfully.
 *
 * @param equilibriumPtr pointer to object "Equilibrium"
 * @return bool true if equilibrium is solved.
 */
DLL bool equilibriumIsSolved(void* equilibriumPtr);

/**
 * Returns heat capacity \f$ C_p \f$ of reacting mixture.
 *
 * @param equilibriumPtr pointer to object "Equilibrium"
 * @param units heat capacity units ("J/(mol K)"|"Btu/(lb-mol R)"|"kJ/(kg K)"|"Btu/(lbm R)")
 * @return double
 */
DLL double derivativesGetCp(void* equilibriumPtr, const char* units);

/**
 * Returns heat capacity \f$ C_v \f$ of reacting mixture.
 *
 * @param equilibriumPtr pointer to object "Equilibrium"
 * @param units ("J/(mol K)"|"Btu/(lb-mol R)"|"kJ/(kg K)"|"Btu/(lbm R)")
 * @return double
 */
DLL double derivativesGetCv(void* equilibriumPtr, const char* units);

/**
 * Returns gas constant \f$ R \f$ of reacting mixture.
 *
 * @param equilibriumPtr pointer to object "Equilibrium"
 * @param units gas constant units ("J/(mol K)"|"Btu/(lb-mol R)"|"kJ/(kg K)"|"Btu/(lbm R)")
 * @return double
 */
DLL double derivativesGetR(void* equilibriumPtr, const char* units);

/**
 * Returns \f$ k = - \frac{\gamma}{{\left(\frac{\delta ln V}{\delta ln p}\right)}_T} \f$ of reacting mixture.
 *
 * @param equilibriumPtr pointer to object "Equilibrium"
 * @return double
 */
DLL double derivativesGetK(void* equilibriumPtr);

/**
 * Returns \f$ \gamma = \frac{C_p}{C_v} \f$ of reacting mixture.
 *
 * @param equilibriumPtr pointer to object "Equilibrium"
 * @return double
 */
DLL double derivativesGetGamma(void* equilibriumPtr);

/**
 * Returns velocity of sound in reacting mixture.
 *
 * @param equilibriumPtr pointer to object "Equilibrium"
 * @param units velocity units ("m/s"|"ft/s")
 * @return double
 */
DLL double derivativesGetA(void* equilibriumPtr, const char* units);

/**
 * Returns density of reacting mixture.
 *
 * @param equilibriumPtr pointer to object "Equilibrium"
 * @param units density units ("kg/m^3"|"lbm/ft^3")
 * @return double
 */
DLL double derivativesGetRho(void* equilibriumPtr, const char* units);

/**
 * Returns density of gaseous products.
 *
 * @param equilibriumPtr pointer to object "Equilibrium"
 * @param units density units ("kg/m^3"|"lbm/ft^3")
 * @return double
 */
DLL double derivativesGetRhoGas(void* equilibriumPtr, const char* units);

/**
 * Returns mass fraction of condensed products.
 *
 * @param equilibriumPtr pointer to object "Equilibrium"
 * @return double
 */
DLL double derivativesGetZ(void* equilibriumPtr);

/**
 * Returns specific heat capacity \f$ C_p \f$ for condensed species.
 *
 * @param equilibriumPtr pointer to object "Equilibrium"
 * @param units density units ("kJ/(kg K)"|"Btu/(lbm R)")
 * @return double
 */
DLL double derivativesGetCpz_spec(void* equilibriumPtr, const char* units);

/**
 * Returns the molar mass of reacting mixture.
 *
 * @param equilibriumPtr pointer to object "Equilibrium"
 * @param units ("kg/mol"|"lbm/lb-mol")
 * @return double
 */
DLL double derivativesGetMm(void* equilibriumPtr, const char* units);

/**
 * Returns the molar mass of reacting mixture without condensed phase.
 *
 * @param equilibriumPtr pointer to object "Equilibrium"
 * @param units ("kg/mol"|"lbm/lb-mol")
 * @return double
 */
DLL double derivativesGetMm2(void* equilibriumPtr, const char* units);

/**
 * Returns viscosity of reacting mixture.
 * Not available if equilibrium calculated with option withTransportProperties=false.
 *
 * @param equilibriumPtr pointer to object "Equilibrium"
 * @param units ("kg/(m-s)"|"lb/(ft s)")
 * @return double
 */
DLL double derivativesGetV(void* equilibriumPtr, const char* units);

/**
 * Returns reaction conductivity of reacting mixture.
 * Not available if equilibrium calculated with option withTransportProperties=false.
 *
 * @param equilibriumPtr pointer to object "Equilibrium"
 * @param units ("W/(m K)"|"Btu/(hr ft R)")
 * @return double
 */
DLL double derivativesGetCR(void* equilibriumPtr, const char* units);

/**
 * Returns frozen conductivity  of reacting mixture.
 * Not available if equilibrium calculated with option withTransportProperties=false.
 *
 * @param equilibriumPtr pointer to object "Equilibrium"
 * @param units ("W/(m K)"|"Btu/(hr ft R)")
 * @return double
 */
DLL double derivativesGetCFr(void* equilibriumPtr, const char* units);

/**
 * Returns effective conductivity  of reacting mixture.
 * Not available if equilibrium calculated with option withTransportProperties=false.
 *
 * @param equilibriumPtr pointer to object "Equilibrium"
 * @param units ("W/(m K)"|"Btu/(hr ft R)")
 * @return double
 */
DLL double derivativesGetCEql(void* equilibriumPtr, const char* units);

/**
 * Returns reaction specific heat of reacting mixture at constant pressure.
 * Not available if equilibrium calculated with option withTransportProperties=false.
 *
 * @param equilibriumPtr pointer to object "Equilibrium"
 * @param units ("J/(mol K)"|"Btu/(lb-mol R)"|"kJ/(kg K)"|"Btu/(lbm R)")
 * @return double
 */
DLL double derivativesGetCpR(void* equilibriumPtr, const char* units);

/**
 * Returns frozen specific heat of reacting mixture at constant pressure.
 * Not available if equilibrium calculated with option withTransportProperties=false.
 *
 * @param equilibriumPtr pointer to object "Equilibrium"
 * @param units ("J/(mol K)"|"Btu/(lb-mol R)"|"kJ/(kg K)"|"Btu/(lbm R)")
 * @return double
 */
DLL double derivativesGetCpFr(void* equilibriumPtr, const char* units);

/**
 * Returns effective specific heat  of reacting mixture at constant pressure.
 * Not available if equilibrium calculated with option withTransportProperties=false.
 *
 * @param equilibriumPtr pointer to object "Equilibrium"
 * @param units ("J/(mol K)"|"Btu/(lb-mol R)"|"kJ/(kg K)"|"Btu/(lbm R)")
 * @return double
 */
DLL double derivativesGetCpEql(void* equilibriumPtr, const char* units);

/**
 * Returns reaction Prandtl number (Pr)  of reacting mixture.
 * Not available if equilibrium calculated with option withTransportProperties=false.
 *
 * @param equilibriumPtr pointer to object "Equilibrium"
 * @return double
 */
DLL double derivativesGetPrR(void* equilibriumPtr);

/**
 * Returns frozen Prandtl number (Pr)  of reacting mixture.
 * Not available if equilibrium calculated with option withTransportProperties=false.
 *
 * @param equilibriumPtr pointer to object "Equilibrium"
 * @return double
 */
DLL double derivativesGetPrFr(void* equilibriumPtr);

/**
 * Returns effective Prandtl number (Pr)  of reacting mixture.
 * Not available if equilibrium calculated with option withTransportProperties=false.
 *
 * @param equilibriumPtr pointer to object "Equilibrium"
 * @return double
 */
DLL double derivativesGetPrEql(void* equilibriumPtr);

#endif

//*****************************************************************************

#ifdef __cplusplus
}
#endif

#endif /* RPA_WRAPPER_API_EQUILIBRIUM_H_ */
