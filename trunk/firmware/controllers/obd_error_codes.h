/**
 * @file obd_error_codes.h
 * @brief Standart OBD-II error codes
 *
 * More info at http://www.obd-codes.com/faq/obd2-codes-explained.php
 *
 * @date Dec 20, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef OBD_ERROR_CODES_H_
#define OBD_ERROR_CODES_H_

typedef enum {
//P0001 Fuel Volume Regulator Control Circuit/Open
//P0002 Fuel Volume Regulator Control Circuit Range/Performance
//P0003 Fuel Volume Regulator Control Circuit Low
//P0004 Fuel Volume Regulator Control Circuit High
//P0005 Fuel Shutoff Valve "A" Control Circuit/Open
//P0006 Fuel Shutoff Valve "A" Control Circuit Low
//P0007 Fuel Shutoff Valve "A" Control Circuit High
//P0008 Engine Positions System Performance Bank 1
//P0009 Engine Position System Performance Bank 2
//P0010 "A" Camshaft Position Actuator Circuit (Bank 1)
	//P0001 Fuel Volume Regulator Control Circuit/Open
	//P0002 Fuel Volume Regulator Control Circuit Range/Performance
	//P0003 Fuel Volume Regulator Control Circuit Low
	//P0004 Fuel Volume Regulator Control Circuit High
	//P0005 Fuel Shutoff Valve "A" Control Circuit/Open
	//P0006 Fuel Shutoff Valve "A" Control Circuit Low
	//P0007 Fuel Shutoff Valve "A" Control Circuit High
	//P0008 Engine Positions System Performance Bank 1
	//P0009 Engine Position System Performance Bank 2
	//P0010 "A" Camshaft Position Actuator Circuit (Bank 1)
	//P0011 "A" Camshaft Position - Timing Over-Advanced or System Performance (Bank 1)
	//P0012 "A" Camshaft Position - Timing Over-Retarded (Bank 1)
	//P0013 "B" Camshaft Position - Actuator Circuit (Bank 1)
	//P0014 "B" Camshaft Position - Timing Over-Advanced or System Performance (Bank 1)
	//P0015 "B" Camshaft Position -Timing Over-Retarded (Bank 1)
	//P0016 Crankshaft Position - Camshaft Position Correlation (Bank 1 Sensor A)
	//P0017 Crankshaft Position - Camshaft Position Correlation (Bank 1 Sensor B)
	//P0018 Crankshaft Position - Camshaft Position Correlation (Bank 2 Sensor A)
	//P0019 Crankshaft Position - Camshaft Position Correlation (Bank 2 Sensor B)
	//P0020 "A" Camshaft Position Actuator Circuit (Bank 2)
	//P0021 "A" Camshaft Position - Timing Over-Advanced or System Performance (Bank 2)
	//P0022 "A" Camshaft Position - Timing Over-Retarded (Bank 2)
	//P0023 "B" Camshaft Position - Actuator Circuit (Bank 2)
	//P0024 "B" Camshaft Position - Timing Over-Advanced or System Performance (Bank 2)
	//P0025 "B" Camshaft Position - Timing Over-Retarded (Bank 2)
	//P0026 Intake Valve Control Solenoid Circuit Range/Performance Bank 1
	//P0027 Exhaust Valve Control solenoid Circuit Range/Performance Bank 1
	//P0028 Intake valve Control Solenoid Circuit Range/Performance Bank 2
	//P0029 Exhaust Valve Control Solenoid Circuit Range/Performance Bank 2
	//P0030 HO2S Heater Control Circuit (Bank 1 Sensor 1)
	//P0031 HO2S Heater Control Circuit Low (Bank 1 Sensor 1)
	//P0032 HO2S Heater Control Circuit High (Bank 1 Sensor 1)
	//P0033 Turbo Charger Bypass Valve Control Circuit
	//P0034 Turbo Charger Bypass Valve Control Circuit Low
	//P0035 Turbo Charger Bypass Valve Control Circuit High
	//P0036 HO2S Heater Control Circuit (Bank 1 Sensor 2)
	//P0037 HO2S Heater Control Circuit Low (Bank 1 Sensor 2)
	//P0038 HO2S Heater Control Circuit High (Bank 1 Sensor 2)
	//P0039 Turbo/Super Charger Bypass Valve Control Circuit Range/Performance
	//P0040 Upstream Oxygen Sensors Swapped From Bank To Bank
	//P0041 Downstream Oxygen Sensors Swapped From Bank To Bank
	//P0042 HO2S Heater Control Circuit (Bank 1 Sensor 3)
	//P0043 HO2S Heater Control Circuit Low (Bank 1 Sensor 3)
	//P0044 HO2S Heater Control Circuit High (Bank 1 Sensor 3)
	//P0050 HO2S Heater Control Circuit (Bank 2 Sensor 1)
	//P0051 HO2S Heater Control Circuit Low (Bank 2 Sensor 1)
	//P0052 HO2S Heater Control Circuit High (Bank 2 Sensor 1)
	//P0053 HO2S Heater Resistance (Bank 1, Sensor 1)
	//P0054 HO2S Heater Resistance (Bank 1, Sensor 2)
	//P0055 HO2S Heater Resistance (Bank 1, Sensor 3)
	//P0056 HO2S Heater Control Circuit (Bank 2 Sensor 2)
	//P0057 HO2S Heater Control Circuit Low (Bank 2 Sensor 2)
	//P0058 HO2S Heater Control Circuit High (Bank 2 Sensor 2)
	//P0059 HO2S Heater Resistance (Bank 2, Sensor 1)
	//P0060 HO2S Heater Resistance (Bank 2, Sensor 2)
	//P0061 HO2S Heater Resistance (Bank 2, Sensor 3)
	//P0062 HO2S Heater Control Circuit (Bank 2 Sensor 3)
	//P0063 HO2S Heater Control Circuit Low (Bank 2 Sensor 3)
	//P0064 HO2S Heater Control Circuit High (Bank 2 Sensor 3)
	//P0065 Air Assisted Injector Control Range/Performance
	//P0066 Air Assisted Injector Control Circuit or Circuit Low
	//P0067 Air Assisted Injector Control Circuit High
	//P0068 MAP/MAF - Throttle Position Correlation
	//P0069 Manifold Absolute Pressure - Barometric Pressure Correlation
	//P0070 Ambient Air Temperature Sensor Circuit
	//P0071 Ambient Air Temperature Sensor Range/Performance
	//P0072 Ambient Air Temperature Sensor Circuit Low Input
	//P0073 Ambient Air Temperature Sensor Circuit High Input
	//P0074 Ambient Air Temperature Sensor Circuit Intermittent
	//P0075 Intake Valve Control Solenoid Circuit (Bank 1)
	//P0076 Intake Valve Control Solenoid Circuit Low (Bank 1)
	//P0077 Intake Valve Control Solenoid Circuit High (Bank 1)
	//P0078 Exhaust Valve Control Solenoid Circuit (Bank 1)
	//P0079 Exhaust Valve Control Solenoid Circuit Low (Bank 1)
	//P0080 Exhaust Valve Control Solenoid Circuit High (Bank 1)
	//P0081 Intake valve Control Solenoid Circuit (Bank 2)
	//P0082 Intake Valve Control Solenoid Circuit Low (Bank 2)
	//P0083 Intake Valve Control Solenoid Circuit High (Bank 2)
	//P0084 Exhaust Valve Control Solenoid Circuit (Bank 2)
	//P0085 Exhaust Valve Control Solenoid Circuit Low (Bank 2)
	//P0086 Exhaust Valve Control Solenoid Circuit High (Bank 2)
	//P0087 Fuel Rail/System Pressure - Too Low
	//P0088 Fuel Rail/System Pressure - Too High
	//P0089 Fuel Pressure Regulator 1 Performance
	//P0090 Fuel Pressure Regulator 1 Control Circuit
	//P0091 Fuel Pressure Regulator 1 Control Circuit Low
	//P0092 Fuel Pressure Regulator 1 Control Circuit High
	//P0093 Fuel System Leak Detected - Large Leak
	//P0094 Fuel System Leak Detected - Small Leak
	//P0095 Intake Air Temperature Sensor 2 Circuit
	//P0096 Intake Air Temperature Sensor 2 Circuit Range/Performance
	//P0097 Intake Air Temperature Sensor 2 Circuit Low
	//P0098 Intake Air Temperature Sensor 2 Circuit High
	//P0099 Intake Air Temperature Sensor 2 Circuit Intermittent/Erratic
	//P0100 Mass or Volume Air Flow Circuit Malfunction
	//P0101 Mass or Volume Air Flow Circuit Range/Performance Problem
	//P0102 Mass or Volume Air Flow Circuit Low Input
	//P0103 Mass or Volume Air Flow Circuit High Input
	//P0104 Mass or Volume Air Flow Circuit Intermittent
	//P0105 Manifold Absolute Pressure/Barometric Pressure Circuit Malfunction
	//P0106 Manifold Absolute Pressure/Barometric Pressure Circuit Range/Performance Problem
	//P0107 Manifold Absolute Pressure/Barometric Pressure Circuit Low Input
	//P0108 Manifold Absolute Pressure/Barometric Pressure Circuit High Input
	//P0109 Manifold Absolute Pressure/Barometric Pressure Circuit Intermittent
	//P0110 Intake Air Temperature Circuit Malfunction
	//P0111 Intake Air Temperature Circuit Range/Performance Problem
	//P0112 Intake Air Temperature Circuit Low Input
	//P0113 Intake Air Temperature Circuit High Input
	//P0114 Intake Air Temperature Circuit Intermittent
	OBD_Engine_Coolant_Temperature_Circuit_Malfunction = 115,

} obd_code_e;

#endif /* OBD_ERROR_CODES_H_ */
