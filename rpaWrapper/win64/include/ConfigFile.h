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

#ifndef RPA_WRAPPER_API_CONFIG_H_
#define RPA_WRAPPER_API_CONFIG_H_

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
 * Creates empty configuration object and returns the pointer thereto.
 * @return pointer to configuration object.
 */
DLL	void* configFile();

/**
 * Creates configuration object and loads the data from specified file.
 * @param name file name
 * @return pointer to configuration object.
 */
DLL	void* configFileLoad(const char* name);

/**
 * Creates the copy of specified configuration object.
 * @param dataPtr pointer to configuration object
 * @return pointer to created copy of configuration object.
 */
DLL	void* configFileClone(void* dataPtr);

/**
 * Deletes the configuration object without deleting the file.
 * @param dataPtr pointer to configuration object
 */
DLL	void configFileDelete(void* dataPtr);

/**
 * Saves data from given configuration object to the file.
 * @param dataPtr pointer to configuration object
 */
DLL	void configFileSave(void* dataPtr);

/**
 * Saves data from given configuration object to specified file.
 * @param dataPtr pointer to configuration object
 * @param name file name
 */
DLL	void configFileSaveAs(void* dataPtr, const char* name);

/**
 * Returns true, if multiphase flow and phase transitions should be considered.
 * @param dataPtr pointer to configuration object
 */
DLL	bool configFileGeneralOptionsIsMultiphase(void* dataPtr);

/**
 * Assigns multiphase flow flag. Note that for the most of solid propellant problems this flag should be switched on.
 * @param dataPtr pointer to configuration object
 * @param value flag
 */
DLL	void configFileGeneralOptionsSetMultiphase(void* dataPtr, bool value);

/**
 *  Returns true, if species ionization effects should be considered.
 * @param dataPtr pointer to configuration object
 */
DLL	bool configFileGeneralOptionsIsIons(void* dataPtr);

/**
 * Assigns ions flag. Note that for the most of solid propellant problems this flag should be switched on.
 * @param dataPtr pointer to configuration object
 * @param value flag
 */
DLL	void configFileGeneralOptionsSetIons(void* dataPtr, bool value);

/**
 * Returns true, if flow separation effects should be considered.
 * @param dataPtr pointer to configuration object
 */
DLL	bool configFileGeneralOptionsIsFlowSeparation(void* dataPtr);

/**
 * Assigns flow separation effects flag.
 * @param dataPtr pointer to configuration object.
 * @param value flag
 */
DLL	void configFileGeneralOptionsSetFlowSeparation(void* dataPtr, bool value);

/**
 * Returns combustion chamber pressure in specified units.
 * @param dataPtr pointer to configuration object
 * @param units pressure units ("Pa"|"MPa"|"atm"|"bar"|"psi"|"psia"|"at"|"kg/cm2")
 */
DLL	double configFileCombustionChamberConditionsGetPressure(void* dataPtr, const char* units);

/**
 * Assigns combustion chamber pressure in specified units.
 * @param dataPtr pointer to configuration object
 * @param units pressure units ("Pa"|"MPa"|"atm"|"bar"|"psi"|"psia"|"at"|"kg/cm2")
 */
DLL	void configFileCombustionChamberConditionsSetPressure(void* dataPtr, double value, const char* units);

/**
 * Returns true if nozzle flow has to be calculated.
 * @param dataPtr pointer to configuration object
 */
DLL	bool configFileNozzleFlowOptionsIsCalculateNozzleFlow(void* dataPtr);

/**
 * Sets the flag of nozzle flow calculation.
 * @param dataPtr pointer to configuration object
 */
DLL	void configFileNozzleFlowOptionsSetCalculateNozzleFlow(void* dataPtr, bool value);

/**
 * Returns true if freezing conditions set.
 * @param dataPtr pointer to configuration object
 */
DLL	bool configFileNozzleFlowOptionsIsFreezingConditions(void* dataPtr);

/**
 * Assigns freezing conditions settings.
 * @param dataPtr pointer to configuration object
 * @param type of conditions: 0 - freezing condition defined as area ratio; 1 - freezing condition defined as a pressure in specified units; 2 - freezing condition defined as pressure ratio.
 * @param value condition value
 * @param units if type==1, pressure units ("Pa"|"MPa"|"atm"|"bar"|"psi"|"psia"|"at"|"kg/cm2")
 */
DLL	void configFileNozzleFlowOptionsSetFreezingConditions(void* dataPtr, unsigned int type, double value, const char* units);

/**
 * Deletes the assigned freezing conditions settings.
 * @param dataPtr pointer to configuration object
 */
DLL	void configFileNozzleFlowOptionsDeleteFreezingConditions(void* dataPtr);

/**
 * Returns true if nozzle inlet conditions set.
 * @param dataPtr pointer to configuration object
 */
DLL	bool configFileNozzleFlowOptionsIsNozzleInletConditions(void* dataPtr);

/**
 * Assigns nozzle inlet conditions.
 * @param dataPtr pointer to configuration object
 * @param type of conditions: 0 - nozzle inlet condition defined as contraction area ratio; 2 - nozzle inlet condition defined as combustion chamber mass flux in specified units.
 * @param value condition value
 * @param units if type==1, mass flux  units ("kg/(m2·s)"|"kg/(m2-s)"|"kg/(s·m2)"|"kg/(s-m2)"|"lbm/(ft2·s)"|"lbm/(ft2-s)"|"lbm/(s·ft2)"|"lbm/(s-ft2)")
 */
DLL	void configFileNozzleFlowOptionsSetNozzleInletConditions(void* dataPtr, unsigned int type, double value, const char* units);

/**
 * Deletes the assigned nozzle inlet conditions settings.
 * @param dataPtr pointer to configuration object
 */
DLL	void configFileNozzleFlowOptionsDeleteNozzleInletConditions(void* dataPtr);

/**
 * Returns true if nozzle exit conditions set.
 * @param dataPtr pointer to configuration object
 */
DLL	bool configFileNozzleFlowOptionsIsNozzleExitConditions(void* dataPtr);

/**
 * Assigns nozzle exit conditions.
 * @param dataPtr pointer to configuration object
 * @param type of conditions: 0 - nozzle exit condition defined as exit area ratio; 1 - nozzle exit condition defined as pressure ratio; 2 - nozzle exit condition defined as absolute pressure in specified units.
 * @param value condition value
 * @param units if type==2, pressure units ("Pa"|"MPa"|"atm"|"bar"|"psi"|"psia"|"at"|"kg/cm2")
 */
DLL	void configFileNozzleFlowOptionsSetNozzleExitConditions(void* dataPtr, unsigned int type, double value, const char* units);

/**
 * Deletes the assigned nozzle exit conditions settings.
 * @param dataPtr pointer to configuration object
 */
DLL	void configFileNozzleFlowOptionsDeleteNozzleExitConditions(void* dataPtr);

/**
 * Returns true if ambient conditions set.
 * @param dataPtr pointer to configuration object
 */
DLL	bool configFileNozzleFlowOptionsIsAmbientConditions(void* dataPtr);

/**
 * Assigns fixed ambient pressure in specified unit.
 * @param dataPtr pointer to configuration object
 * @param value ambient pressure
 * @param units pressure units ("Pa"|"MPa"|"atm"|"bar"|"psi"|"psia"|"at"|"kg/cm2")
 */
DLL	void configFileNozzleFlowOptionsSetAmbientConditions(void* dataPtr, double value, const char* units);

/**
 * Assigns lower and upper values of ambient pressure range in specified units.
 * @param dataPtr pointer to configuration object
 * @param lowerValue ambient pressure lower value
 * @param lowerUnits pressure units ("Pa"|"MPa"|"atm"|"bar"|"psi"|"psia"|"at"|"kg/cm2")
 * @param upperValue ambient pressure upper value
 * @param upperUnits pressure units ("Pa"|"MPa"|"atm"|"bar"|"psi"|"psia"|"at"|"kg/cm2")
 */
DLL	void configFileNozzleFlowOptionsSetAmbientConditionsRange(void* dataPtr, double lowerValue, const char* lowerUnits, double upperValue, const char* upperUnits);

/**
 * Returns the flag deliveredPerformance. If true, applies correction factors when calculating performance at configured ambient conditions.
 * @param dataPtr pointer to configuration object
 */
DLL	bool configFileNozzleFlowOptionsAmbientConditionsIsDeliveredPerformance(void* dataPtr);

/**
 * Assigns the flag deliveredPerformance. If true, applies correction factors when calculating performance at configured ambient conditions.
 * @param dataPtr pointer to configuration object
 * @param value boolean flag
 */
DLL	void configFileNozzleFlowOptionsAmbientConditionsSetDeliveredPerformance(void* dataPtr, bool value);

/**
 * Deletes the assigned ambient conditions settings .
 * @param dataPtr pointer to configuration object
 */
DLL	void configFileNozzleFlowOptionsDeleteAmbientConditions(void* dataPtr);

/**
 * Returns true if throttling conditions set.
 * @param dataPtr pointer to configuration object
 */
DLL	bool configFileNozzleFlowOptionsIsThrottlingConditions(void* dataPtr);

/**
 * Assigns fixed mass flow rate (decimal fraction, r/nominal).
 * @param dataPtr pointer to configuration object
 * @param value relative mass flow rate (decimal fraction, r/nominal)
 */
DLL	void configFileNozzleFlowOptionsSetThrottlingConditions(void* dataPtr, double value);

/**
 * Assigns lower and upper values of flow rate range (decimal fraction, r/nominal).
 * @param dataPtr pointer to configuration object
 * @param lowerValue lower value of range of relative mass flow rate (decimal fraction, r/nominal)
 * @param upperValue upper value of range of relative mass flow rate (decimal fraction, r/nominal)
 */
DLL	void configFileNozzleFlowOptionsSetThrottlingConditionsRange(void* dataPtr, double lowerValue, double upperValue);

/**
 * Returns the flag deliveredPerformance. If true, applies correction factors when calculating throttled performance.
 * @param dataPtr pointer to configuration object
 */
DLL	bool configFileNozzleFlowOptionsThrottlingConditionsIsDeliveredPerformance(void* dataPtr);

/**
 * Assigns the flag deliveredPerformance. If true, applies correction factors when calculating throttled performance.
 * @param dataPtr pointer to configuration object
 * @param value the flag deliveredPerformance.
 */
DLL	void configFileNozzleFlowOptionsThrottlingConditionsSetDeliveredPerformance(void* dataPtr, bool value);

/**
 * Deletes the assigned throttling conditions settings.
 * @param dataPtr pointer to configuration object
 */
DLL	void configFileNozzleFlowOptionsDeleteThrottlingConditions(void* dataPtr);

/**
 * Returns true if efficiency factors configuration set.
 * @param dataPtr pointer to configuration object
 */
DLL	bool configFileNozzleFlowOptionsIsEfficiencyFactors(void* dataPtr);

/**
 * Returns value of parameter applyEfficiencyFactors.
 * @param dataPtr pointer to configuration object
 */
DLL	bool configFileNozzleFlowOptionsIsApplyEfficiencyFactors(void* dataPtr);

/**
 * Assigns the flag applyEfficiencyFactors.
 * @param dataPtr pointer to configuration object
 * @param value boolean flag.
 */
DLL	void configFileNozzleFlowOptionsSetApplyEfficiencyFactors(void* dataPtr, bool value);

/**
 * Returns true if cycle efficiency is set.
 * @param dataPtr pointer to configuration object
 */
DLL	bool configFileNozzleFlowOptionsIsCycleEfficiency(void* dataPtr);

/**
 * Assigns cycle efficiency.
 * @param dataPtr pointer to configuration object
 * @param value efficiency.
 */
DLL	void configFileNozzleFlowOptionsSetCycleEfficiency(void* dataPtr, double value);

/**
 * Returns cycle efficiency.
 * @param dataPtr pointer to configuration object
 */
DLL	double configFileNozzleFlowOptionsGetCycleEfficiency(void* dataPtr);

/**
 * Deletes cycle efficiency.
 * @param dataPtr pointer to configuration object
 */
DLL	void configFileNozzleFlowOptionsDeleteCycleEfficiency(void* dataPtr);

/**
 * Returns true if reaction efficiency is set.
 * @param dataPtr pointer to configuration object
 */
DLL	bool configFileNozzleFlowOptionsIsReactionEfficiency(void* dataPtr);

/**
 * Assigns the value of reaction efficiency.
 * @param dataPtr pointer to configuration object
 * @param value reaction efficiency
 */
DLL	void configFileNozzleFlowOptionsSetReactionEfficiency(void* dataPtr, double value);

/**
 * Returns the value of reaction efficiency.
 * @param dataPtr pointer to configuration object
 */
DLL	double configFileNozzleFlowOptionsGetReactionEfficiency(void* dataPtr);

/**
 * Deletes the reaction efficiency.
 * @param dataPtr pointer to configuration object
 */
DLL	void configFileNozzleFlowOptionsDeleteReactionEfficiency(void* dataPtr);

/**
 * Returns true if nozzle efficiency is set.
 * @param dataPtr pointer to configuration object
 */
DLL	bool configFileNozzleFlowOptionsIsNozzleEfficiency(void* dataPtr);

/**
 * Assigns the value of nozzle efficiency.
 * @param dataPtr pointer to configuration object
 * @param value nozzle efficiency
 */
DLL	void configFileNozzleFlowOptionsSetNozzleEfficiency(void* dataPtr, double value);

/**
 * Returns th evalue of nozzle efficiency
 * @param dataPtr pointer to configuration object
 */
DLL	double configFileNozzleFlowOptionsGetNozzleEfficiency(void* dataPtr);

/**
 * Deletes the nozzle efficiency
 * @param dataPtr pointer to configuration object
 */
DLL	void configFileNozzleFlowOptionsDeleteNozzleEfficiency(void* dataPtr);

/**
 * Returns true if bell nozzle relative length is set.
 * @param dataPtr pointer to configuration object
 */
DLL	bool configFileNozzleFlowOptionsIsNozzleLength(void* dataPtr);

/**
 * Assigns bell nozzle relative length.
 * @param dataPtr pointer to configuration object
 * @param value bell nozzle relative length
 */
DLL	void configFileNozzleFlowOptionsSetNozzleLength(void* dataPtr, double value);

/**
 * Returns bell nozzle relative length.
 * @param dataPtr pointer to configuration object
 */
DLL	double configFileNozzleFlowOptionsGetNozzleLength(void* dataPtr);

/**
 * Deletes bell nozzle relative length.
 * @param dataPtr pointer to configuration object
 */
DLL	void configFileNozzleFlowOptionsDeleteNozzleLength(void* dataPtr);

/**
 * Returns true if cone nozzle half angle is set.
 * @param dataPtr pointer to configuration object
 */
DLL	bool configFileNozzleFlowOptionsIsConeHalfAngle(void* dataPtr);

/**
 * Assigns the value of cone nozzle half angle in specified units.
 * @param dataPtr pointer to configuration object
 * @param value cone nozzle half angle
 * @param units parameter units ("radians"|"degrees")
 */
DLL	void configFileNozzleFlowOptionsSetConeHalfAngle(void* dataPtr, double value, const char* unit);

/**
 * Returns the value of cone nozzle half angle in specified units.
 * @param dataPtr pointer to configuration object
 * @param units parameter units ("radians"|"degrees")
 */
DLL	double configFileNozzleFlowOptionsGetConeHalfAngle(void* dataPtr, const char* unit);

/**
 * Deletes the cone nozzle half angle.
 * @param dataPtr pointer to configuration object
 */
DLL	void configFileNozzleFlowOptionsDeleteConeHalfAngle(void* dataPtr);

/**
 * Deletes the assigned efficiency factors settings.
 * @param dataPtr pointer to configuration object
 */
DLL	void configFileNozzleFlowOptionsDeleteEfficiencyFactors(void* dataPtr);

/**
 * Returns assigned component ratio.
 * @param dataPtr pointer to configuration object
 */
DLL	double configFilePropellantGetRatio(void* dataPtr);

/**
 * Returns the type of assigned component ratio ("O/F"|"alpha"|"optimal")
 * @param dataPtr pointer to configuration object
 */
DLL	const char* configFilePropellantGetRatioType(void* dataPtr);

/**
 * Assigns component ratio of specified type.
 * @param dataPtr pointer to configuration object
 * @param value component ratio
 * @param type ratio type ("O/F"|"alpha"|"optimum")
 */
DLL	void configFilePropellantSetRatio(void* dataPtr, double value, const char* type);

/**
 * Returns the size of oxidizer list.
 * @param dataPtr pointer to configuration object
 */
DLL	unsigned int configFilePropellantGetOxidizerListSize(void* dataPtr);

/**
 * Returns the name of oxidizer component at specified index.
 * @param dataPtr pointer to configuration object
 * @param n index
 */
DLL	const char* configFilePropellantGetOxidizerName(void* dataPtr, unsigned int n);

/**
 * Returns the mass fraction of oxidizer component at specified index (relative to the sum of oxidizer components).
 * @param dataPtr pointer to configuration object
 * @param n index
 */
DLL	double configFilePropellantGetOxidizerMassFraction(void* dataPtr, unsigned int n);

/**
 * Returns the initial pressure of oxidizer component at specified index.
 * @param dataPtr pointer to configuration object
 * @param n index
 * @param units pressure units ("Pa"|"MPa"|"atm"|"bar"|"psi"|"psia"|"at"|"kg/cm2")
 */
DLL	double configFilePropellantGetOxidizerPressure(void* dataPtr, unsigned int n, const char* units);

/**
 * Returns the initial temperature of oxidizer component at specified index.
 * @param dataPtr pointer to configuration object
 * @param units temperature units ("K"|"C"|"F")
 */
DLL	double configFilePropellantGetOxidizerTemperature(void* dataPtr, unsigned int n, const char* units);

/**
 * Adds oxidizer component to oxidizer list.
 * @param dataPtr pointer to configuration object
 * @param name name of oxidizer component.
 * @param massFraction mass fraction of oxidizer component relative to the sum of oxidizer components.
 * @param pressure initial pressure
 * @param pressureUnits pressure units ("Pa"|"MPa"|"atm"|"bar"|"psi"|"psia"|"at"|"kg/cm2")
 * @param temperature initial temperature
 * @param units temperatureUnits units ("K"|"C"|"F")
 */
DLL	void configFilePropellantAddOxidizer(void* dataPtr, const char* name, double massFraction, double pressure, const char* pressureUnits, double temperature, const char* temperatureUnits);

/**
 * Returns the size of fuel list.
 * @param dataPtr pointer to configuration object
 */
DLL	unsigned int configFilePropellantGetFuelListSize(void* dataPtr);

/**
 * Returns the name of fuel component at specified index.
 * @param dataPtr pointer to configuration object
 * @param n index
 * @param dataPtr pointer to configuration object
 */
DLL	const char* configFilePropellantGetFuelName(void* dataPtr, unsigned int n);

/**
 * Returns the mass fraction of fuel component at specified index (relative to the sum of fuel components).
 * @param dataPtr pointer to configuration object
 * @param n index
 */
DLL	double configFilePropellantGetFuelMassFraction(void* dataPtr, unsigned int n);

/**
 * Returns the initial pressure of fuel component at specified index.
 * @param dataPtr pointer to configuration object
 * @param n index
 * @param units pressure units ("Pa"|"MPa"|"atm"|"bar"|"psi"|"psia"|"at"|"kg/cm2")
 */
DLL	double configFilePropellantGetFuelPressure(void* dataPtr, unsigned int n, const char* units);

/**
 * Returns the initial temperature of fuel component at specified index.
 * @param dataPtr pointer to configuration object
 * @param units temperature units ("K"|"C"|"F")
 */
DLL	double configFilePropellantGetFuelTemperature(void* dataPtr, unsigned int n, const char* units);

/**
 * Adds fuel component to fuel list.
 * @param dataPtr pointer to configuration object
 * @param name name of fuel component.
 * @param massFraction mass fraction of fuel component relative to the sum of fuel components.
 * @param pressure initial pressure
 * @param pressureUnits pressure units ("Pa"|"MPa"|"atm"|"bar"|"psi"|"psia"|"at"|"kg/cm2")
 * @param temperature initial temperature
 * @param units temperatureUnits units ("K"|"C"|"F")
 */
DLL	void configFilePropellantAddFuel(void* dataPtr, const char* name, double massFraction, double pressure, const char* pressureUnits, double temperature, const char* temperatureUnits);

/**
 * Returns the size of species list.
 * @param dataPtr pointer to configuration object
 */
DLL	unsigned int configFilePropellantGetSpeciesListSize(void* dataPtr);

/**
 * Returns the name of component at specified index.
 * @param dataPtr pointer to configuration object
 * @param n index
 * @param dataPtr pointer to configuration object
 */
DLL	const char* configFilePropellantGetSpeciesName(void* dataPtr, unsigned int n);

/**
 * Returns the mass fraction of component at specified index (relative to the sum of components).
 * @param dataPtr pointer to configuration object
 * @param n index
 */
DLL	double configFilePropellantGetSpeciesMassFraction(void* dataPtr, unsigned int n);

/**
 * Returns the initial pressure of component at specified index.
 * @param dataPtr pointer to configuration object
 * @param n index
 * @param units pressure units ("Pa"|"MPa"|"atm"|"bar"|"psi"|"psia"|"at"|"kg/cm2")
 */
DLL	double configFilePropellantGetSpeciesPressure(void* dataPtr, unsigned int n, const char* units);

/**
 * Returns the initial temperature of component at specified index.
 * @param dataPtr pointer to configuration object
 * @param units temperature units ("K"|"C"|"F")
 */
DLL	double configFilePropellantGetSpeciesTemperature(void* dataPtr, unsigned int n, const char* units);

/**
 * Adds fuel component to the components list.
 * @param dataPtr pointer to configuration object
 * @param name name of component.
 * @param massFraction mass fraction of component relative to the sum of all components.
 * @param pressure initial pressure
 * @param pressureUnits pressure units ("Pa"|"MPa"|"atm"|"bar"|"psi"|"psia"|"at"|"kg/cm2")
 * @param temperature initial temperature
 * @param units temperatureUnits units ("K"|"C"|"F")
 */
DLL	void configFilePropellantAddSpecies(void* dataPtr, const char* name, double massFraction, double pressure, const char* pressureUnits, double temperature, const char* temperatureUnits);

//*****************************************************************************

/**
 *
 * The following functions only available in RPA Standard Edition.
 *
 */

#ifdef STANDARD_EDITION

/**
 * Returns true if engine size is defined by thrust.
 * @param dataPtr pointer to configuration object
 */
DLL	bool configFileEngineSizeIsThrust(void* dataPtr);

/**
 * Returns engine thrust in specified units.
 * @param dataPtr pointer to configuration object
 * @param units thrust units ("N"|"kN"|"kg"|"lbf")
 */
DLL	double configFileEngineSizeGetThrust(void* dataPtr, const char* units);

/**
 * Assigns engine thrust in specified units.
 * @param dataPtr pointer to configuration object
 * @param value thrust
 * @param units thrust units ("N"|"kN"|"kg"|"lbf")
 */
DLL	void configFileEngineSizeSetThrust(void* dataPtr, double value, const char* units);

/**
 * Deletes engine thrust.
 * @param dataPtr pointer to configuration object
 */
DLL	void configFileEngineSizeDeleteThrust(void* dataPtr);

/**
 * Returns true if ambient pressure for configured engine thrust is defined.
 * @param dataPtr pointer to configuration object
 */
DLL	bool configFileEngineSizeIsAmbientPressure(void* dataPtr);

/**
 * Returns ambient pressure for configured engine thrust in specified units.
 * @param dataPtr pointer to configuration object
 * @param units pressure units ("Pa"|"MPa"|"atm"|"bar"|"psi"|"psia"|"at"|"kg/cm2")
 */
DLL	double configFileEngineSizeGetAmbientPressure(void* dataPtr, const char* units);

/**
 * Assigns ambient pressure for configured engine thrust in specified units.
 * @param dataPtr pointer to configuration object
 * @param value ambient pressure
 * @param units pressure units ("Pa"|"MPa"|"atm"|"bar"|"psi"|"psia"|"at"|"kg/cm2")
 */
DLL	void configFileEngineSizeSetAmbientPressure(void* dataPtr, double value, const char* units);

/**
 * Deletes ambient pressure for configured engine thrust.
 * @param dataPtr pointer to configuration object
 */
DLL	void configFileEngineSizeDeleteAmbientPressure(void* dataPtr);

/**
 * Returns true if engine size is defined by propellant mass flow rate.
 * @param dataPtr pointer to configuration object
 */
DLL	bool configFileEngineSizeIsMdot(void* dataPtr);

/**
 * Returns assigned propellant mass flow rate in specified units.
 * @param dataPtr pointer to configuration object
 * @param units mass flow rate units ("kg/s"|"lbm/s")
 */
DLL	double configFileEngineSizeGetMdot(void* dataPtr, const char* units);

/**
 * Assigns propellant mass flow rate in specified units.
 * @param dataPtr pointer to configuration object
 * @param value mass flow rate
 * @param units mass flow rate units ("kg/s"|"lbm/s")
 */
DLL	void configFileEngineSizeSetMdot(void* dataPtr, double value, const char* units);

/**
 * Deletes mass flow rate.
 * @param dataPtr pointer to configuration object
 */
DLL	void configFileEngineSizeDeleteMdot(void* dataPtr);

/**
 * Returns true if engine size is defined by nozzle throat diameter.
 * @param dataPtr pointer to configuration object
 */
DLL	bool configFileEngineSizeIsThroatDiameter(void* dataPtr);

/**
 * Returns assigned nozzle throat diameter in specified units.
 * @param dataPtr pointer to configuration object
 * @param units units of nozzle throat diameter ("m"|"mm"|"in"|"ft")
 */
DLL	double configFileEngineSizeGetThroatDiameter(void* dataPtr, const char* units);

/**
 * Assigns nozzle throat diameter in specified units.
 * @param dataPtr pointer to configuration object
 * @param value nozzle throat diameter
 * @param units units of nozzle throat diameter ("m"|"mm"|"in"|"ft")
 */
DLL	void configFileEngineSizeSetThroatDiameter(void* dataPtr, double value, const char* units);

/**
 * Deletes nozzle throat diameter.
 * @param dataPtr pointer to configuration object
 */
DLL	void configFileEngineSizeDeleteThroatDiameter(void* dataPtr);

/**
 * Returns the number of chambers in engine.
 * @param dataPtr pointer to configuration object
 */
DLL	unsigned int configFileEngineSizeGetChambersNo(void* dataPtr);

/**
 * Assigns the number of chambers in engine.
 * @param dataPtr pointer to configuration object
 */
DLL	void configFileEngineSizeSetChambersNo(void* dataPtr, unsigned int value);

/**
 * Returns chamber length in specified units.
 * @param dataPtr pointer to configuration object
 * @param units units of chamber length ("m"|"mm"|"in"|"ft")
 */
DLL	double configFileEngineSizeGetChamberLength(void* dataPtr, const char* units);

/**
 * Returns chamber length in specified units.
 * @param dataPtr pointer to configuration object
 * @param value chamber length
 * @param units units of chamber length ("m"|"mm"|"in"|"ft")
 * @param type type of chamber length (if type==1 then length is L* otherwise length is L')
 */
DLL	void configFileEngineSizeSetChamberLength(void* dataPtr, double value, const char* units, unsigned int type);

/**
 * Returns the type of assigned chamber length: 1 if length is L*; 2 if length is L'.
 * @param dataPtr pointer to configuration object
 */
DLL	unsigned int configFileEngineSizeGetChamberLengthType(void* dataPtr);

/**
 * Returns chamber contraction half-angle in specified units.
 * @param dataPtr pointer to configuration object
 * @param units parameter units ("radians"|"degrees")
 */
DLL	double configFileEngineSizeGetContractionAngle(void* dataPtr, const char* unit);

/**
 * Assigns chamber contraction angle in specified units.
 * @param dataPtr pointer to configuration object
 * @param value parameter chamber contraction half-angle
 * @param units parameter units ("radians"|"degrees")
 */
DLL	void configFileEngineSizeSetContractionAngle(void* dataPtr, double value, const char* unit);

/**
 * Returns R1/Rt ratio.
 * @param dataPtr pointer to configuration object
 */
DLL	double configFileEngineSizeGetR1ToRtRatio(void* dataPtr);

/**
 * Assigns R1/Rt ratio.
 * @param dataPtr pointer to configuration object
 */
DLL	void configFileEngineSizeSetR1ToRtRatio(void* dataPtr, double value);

/**
 * Returns Rn/Rt ratio.
 * @param dataPtr pointer to configuration object
 */
DLL	double configFileEngineSizeGetRnToRtRatio(void* dataPtr);

/**
 * Assigns Rn/Rt ratio.
 * @param dataPtr pointer to configuration object
 */
DLL	void configFileEngineSizeSetRnToRtRatio(void* dataPtr, double value);

/**
 * Returns R2/R2_max ratio.
 * @param dataPtr pointer to configuration object
 */
DLL	double configFileEngineSizeGetR2ToR2maxRatio(void* dataPtr);

/**
 * Assigns R2/R2_max ratio.
 * @param dataPtr pointer to configuration object
 */
DLL	void configFileEngineSizeSetR2ToR2maxRatio(void* dataPtr, double value);

/**
 * Returns true if nozzle is truncated ideal contour (TIC).
 * @param dataPtr pointer to configuration object
 */
DLL	bool configFileEngineSizeIsTIC(void* dataPtr);

/**
 * Assigns flag of truncated ideal contour (TIC)
 * @param dataPtr pointer to configuration object
 * @param value boolean flag
 */
DLL	void configFileEngineSizeSetTIC(void* dataPtr, bool value);

/**
 * Deletes flag of truncated ideal contour.
 * @param dataPtr pointer to configuration object
 */
DLL	void configFileEngineSizeDeleteTIC(void* dataPtr);

/**
 * Returns true of ratio Twg/T0 is defined.
 * @param dataPtr pointer to configuration object
 */
DLL	bool configFileEngineSizeIsTwToT0(void* dataPtr);

/**
 * Returns the ratio Twg/T0.
 * @param dataPtr pointer to configuration object
 */
DLL	double configFileEngineSizeGetTwToT0(void* dataPtr);

/**
 * Assigns the ratio Twg/T0.
 * @param dataPtr pointer to configuration object
 * @param value ratio Twg/T0
 */
DLL	void configFileEngineSizeSetTwToT0(void* dataPtr, double value);

/**
 * Deletes the ratio Twg/T0.
 * @param dataPtr pointer to configuration object
 */
DLL	void configFileEngineSizeDeleteTwToT0(void* dataPtr);

/**
 * Returns true if initial half-angle of parabolic nozzle is defined.
 * @param dataPtr pointer to configuration object
 */
DLL	bool configFileEngineSizeIsParabolicInitialAngle(void* dataPtr);

/**
 * Returns the initial half-angle of parabolic nozzle in specified units.
 * @param dataPtr pointer to configuration object
 * @param units parameter units ("radians"|"degrees")
 */
DLL	double configFileEngineSizeGetParabolicInitialAngle(void* dataPtr, const char* units);

/**
 * Assigns the initial half-angle of parabolic nozzle in specified units.
 * @param dataPtr pointer to configuration object
 * @param value half-angle of parabolic nozzle
 * @param units parameter units ("radians"|"degrees")
 */
DLL	void configFileEngineSizeSetParabolicInitialAngle(void* dataPtr, double value, const char* units);

/**
 * Deletes initial half-angle of parabolic nozzle.
 * @param dataPtr pointer to configuration object
 */
DLL	void configFileEngineSizeDeleteParabolicInitialAngle(void* dataPtr);

/**
 * Returns true if exit half-angle of parabolic nozzle is defined.
 * @param dataPtr pointer to configuration object
 */
DLL	bool configFileEngineSizeIsParabolicExitAngle(void* dataPtr);

/**
 * Returns the exit half-angle of parabolic nozzle in specified units.
 * @param dataPtr pointer to configuration object
 * @param units parameter units ("radians"|"degrees")
 */
DLL	double configFileEngineSizeGetParabolicExitAngle(void* dataPtr, const char* units);

/**
 * Assigns the exit half-angle of parabolic nozzle in specified units.
 * @param dataPtr pointer to configuration object
 * @param value exit half-angle of parabolic nozzle
 * @param units parameter units ("radians"|"degrees")
 */
DLL	void configFileEngineSizeSetParabolicExitAngle(void* dataPtr, double value, const char* units);

/**
 * Deletes exit half-angle of parabolic nozzle.
 * @param dataPtr pointer to configuration object
 */
DLL	void configFileEngineSizeDeleteParabolicExitAngle(void* dataPtr);

#endif

//*****************************************************************************

#ifdef __cplusplus
}
#endif

#endif /* RPA_WRAPPER_API_CONFIG_H_ */
