/**
 * @file obd_error_codes.h
 * @brief Standart OBD-II error codes
 *
 * More info at http://www.obd-codes.com/faq/obd2-codes-explained.php
 *
 * @date Dec 20, 2013
 * @author Andrey Belomutskiy, (c) 2012-2015
 */

#ifndef OBD_ERROR_CODES_H_
#define OBD_ERROR_CODES_H_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "rusefi_enums.h"

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
	OBD_Mass_or_Volume_Air_Flow_Circuit_Malfunction = 100,
	//P0101 Mass or Volume Air Flow Circuit Range/Performance Problem
	//P0102 Mass or Volume Air Flow Circuit Low Input
	//P0103 Mass or Volume Air Flow Circuit High Input
	//P0104 Mass or Volume Air Flow Circuit Intermittent
	//P0105 Manifold Absolute Pressure/Barometric Pressure Circuit Malfunction
	//P0106 Manifold Absolute Pressure/Barometric Pressure Circuit Range/Performance Problem
	//P0107 Manifold Absolute Pressure/Barometric Pressure Circuit Low Input
	//P0108 Manifold Absolute Pressure/Barometric Pressure Circuit High Input
	//P0109 Manifold Absolute Pressure/Barometric Pressure Circuit Intermittent
	OBD_Intake_Air_Temperature_Circuit_Malfunction = 110,
	//P0111 Intake Air Temperature Circuit Range/Performance Problem
	//P0112 Intake Air Temperature Circuit Low Input
	//P0113 Intake Air Temperature Circuit High Input
	//P0114 Intake Air Temperature Circuit Intermittent
	OBD_Engine_Coolant_Temperature_Circuit_Malfunction = 115,
	//P0116 Engine Coolant Temperature Circuit Range/Performance Problem
	//P0117 Engine Coolant Temperature Circuit Low Input
	//P0118 Engine Coolant Temperature Circuit High Input
	//P0119 Engine Coolant Temperature Circuit Intermittent
	//P0120 Throttle Position Sensor/Switch A Circuit Malfunction
	//P0121 Throttle Position Sensor/Switch A Circuit Range/Performance Problem
	//P0122 Throttle Position Sensor/Switch A Circuit Low Input
	//P0123 Throttle Position Sensor/Switch A Circuit High Input
	//P0124 Throttle Position Sensor/Switch A Circuit Intermittent
	//P0125 Insufficient Coolant Temperature for Closed Loop Fuel Control
	//P0126 Insufficient Coolant Temperature for Stable Operation
	//P0128 Coolant Thermostat (Coolant Temperature Below Thermostat Regulating Temperature)
	//P0130 02 Sensor Circuit Malfunction (Bank I Sensor 1)
	//P0131 02 Sensor Circuit Low Voltage (Bank I Sensor I)
	//P0132 02 Sensor Circuit High Voltage (Bank I Sensor 1)
	//P0133 02 Sensor Circuit Slow Response (Bank 1 Sensor 1)
	//P0134 02 Sensor Circuit No Activity Detected (Bank I Sensor 1)
	//P0135 02 Sensor Heater Circuit Malfunction (Bank 1 Sensor 1)
	//P0136 02 Sensor Circuit Malfunction (Bank I Sensor 2)
	//P0137 02 Sensor Circuit Low Voltage (Bank I Sensor 2)
	//P0138 02 Sensor Circuit High Voltage (Bank I Sensor 2)
	//P0139 02 Sensor Circuit Slow Response (Bank 1 Sensor 2)
	//P0140 02 Sensor Circuit No Activity Detected (Bank 1 Sensor 2)
	//P0141 02 Sensor Heater Circuit Malfunction (Bank 1 Sensor 2)
	//P0142 02 Sensor Circuit Malfunction (Bank I Sensor 3)
	//P0143 02 Sensor Circuit Low Voltage (Bank I Sensor 3)
	//P0144 02 Sensor Circuit High Voltage (Bank I Sensor 3)
	//P0145 02 Sensor Circuit Slow Response (Bank 1 Sensor 3)
	//P0146 02 Sensor Circuit No Activity Detected (Bank I Sensor 3)
	//P0147 02 Sensor Heater Circuit Malfunction (Bank I Sensor 3)
	//P0150 02 Sensor Circuit Malfunction (Bank 2 Sensor I)
	//P0151 02 Sensor Circuit Low Voltage (Bank 2 Sensor I)
	//P0152 02 Sensor Circuit High Voltage (Bank 2 Sensor 1)
	//P0153 02 Sensor Circuit Slow Response (Bank 2 Sensor 1)
	//P0154 02 Sensor Circuit No Activity Detected (Bank 2 Sensor 1)
	//P0155 02 Sensor Heater Circuit Malfunction (Bank 2 Sensor 1)
	//P0156 02 Sensor Circuit Malfunction (Bank 2 Sensor 2)
	//P0157 02 Sensor Circuit Low Voltage (Bank 2 Sensor 2)
	//P0158 02 Sensor Circuit High Voltage (Bank 2 Sensor 2)
	//P0159 02 Sensor Circuit Slow Response (Bank 2 Sensor 2)
	//P0160 02 Sensor Circuit No Activity Detected (Bank 2 Sensor 2)
	//P0161 02 Sensor Heater Circuit Malfunction (Bank 2 Sensor 2)
	//P0162 02 Sensor Circuit Malfunction (Bank 2 Sensor 3)
	//P0163 02 Sensor Circuit Low Voltage (Bank 2 Sensor 3)
	//P0164 02 Sensor Circuit High Voltage (Bank 2 Sensor 3)
	//P0165 02 Sensor Circuit Slow Response (Bank 2 Sensor 3)
	//P0166 02 Sensor Circuit No Activity Detected (Bank 2 Sensor 3)
	//P0167 02 Sensor Heater Circuit Malfunction (Bank 2 Sensor 3)
	//P0170 Fuel Trim Malfunction (Bank 1)
	//P0171 System too Lean (Bank 1)
	//P0172 System too Rich (Bank 1)
	//P0173 Fuel Trim Malfunction (Bank 2)
	//P0174 System too Lean (Bank 2)
	//P0175 System too Rich (Bank 2)
	//P0176 Fuel Composition Sensor Circuit Malfunction
	//P0177 Fuel Composition Sensor Circuit Range/Performance
	//P0178 Fuel Composition Sensor Circuit Low Input
	//P0179 Fuel Composition Sensor Circuit High Input
	//P0180 Fuel Temperature Sensor A Circuit Malfunction
	//P0181 Fuel Temperature Sensor A Circuit Range/Performance
	//P0182 Fuel Temperature Sensor A Circuit Low Input
	//P0183 Fuel Temperature Sensor A Circuit High Input
	//P0184 Fuel Temperature Sensor A Circuit Intermittent
	//P0185 Fuel Temperature Sensor B Circuit Malfunction
	//P0186 Fuel Temperature Sensor B Circuit Range/Performance
	//P0187 Fuel Temperature Sensor B Circuit Low Input
	//P0188 Fuel Temperature Sensor B Circuit High Input
	//P0189 Fuel Temperature Sensor B Circuit Intermittent
	//P0190 Fuel Rail Pressure Sensor Circuit Malfunction
	//P0191 Fuel Rail Pressure Sensor Circuit Range/Performance
	//P0192 Fuel Rail Pressure Sensor Circuit Low Input
	//P0193 Fuel Rail Pressure Sensor Circuit High Input
	//P0194 Fuel Rail Pressure Sensor Circuit Intermittent
	//P0195 Engine Oil Temperature Sensor Malfunction
	//P0196 Engine Oil Temperature Sensor Range/Performance
	//P0197 Engine Oil Temperature Sensor Low
	//P0198 Engine Oil Temperature Sensor High
	//P0199 Engine Oil Temperature Sensor Intermittent
	//DTC Codes - P0200-P0299 - Fuel and Air Metering (Injector Circuit)
	//P0200 Injector Circuit Malfunction
	//P0201 Injector Circuit Malfunction - Cylinder 1
	//P0202 Injector Circuit Malfunction - Cylinder 2
	//P0203 Injector Circuit Malfunction - Cylinder 3
	//P0204 Injector Circuit Malfunction - Cylinder 4
	//P0205 Injector Circuit Malfunction - Cylinder 5
	//P0206 Injector Circuit Malfunction - Cylinder 6
	//P0207 Injector Circuit Malfunction - Cylinder 7
	//P0208 Injector Circuit Malfunction - Cylinder 8
	//P0209 Injector Circuit Malfunction - Cylinder 9
	//P0210 Injector Circuit Malfunction - Cylinder 10
	//P0211 Injector Circuit Malfunction - Cylinder 11
	//P0212 Injector Circuit Malfunction - Cylinder 12
	//P0213 Cold Start Injector 1 Malfunction
	//P0214 Cold Start Injector 2 Malfunction
	//P0215 Engine Shutoff Solenoid Malfunction
	//P0216 Injection Timing Control Circuit Malfunction
	//P0217 Engine Overtemp Condition
	//P0218 Transmission Over Temperature Condition
	//P0219 Engine Overspeed Condition
	//P0220 Throttle/Petal Position Sensor/Switch B Circuit Malfunction
	//P0221 Throttle/Petal Position Sensor/Switch B Circuit Range/Performance Problem
	//P0222 Throttle/Petal Position Sensor/Switch B Circuit Low Input
	//P0223 Throttle/Petal Position Sensor/Switch B Circuit High Input
	//P0224 Throttle/Petal Position Sensor/Switch B Circuit Intermittent
	//P0225 Throttle/Petal Position Sensor/Switch C Circuit Malfunction
	//P0226 Throttle/Petal Position Sensor/Switch C Circuit Range/Performance Problem
	//P0227 Throttle/Petal Position Sensor/Switch C Circuit Low Input
	//P0228 Throttle/Petal Position Sensor/Switch C Circuit High Input
	//P0229 Throttle/Petal Position Sensor/Switch C Circuit Intermittent
	//P0230 Fuel Pump Primary Circuit Malfunction
	//P0231 Fuel Pump Secondary Circuit Low
	//P0232 Fuel Pump Secondary Circuit High
	//P0233 Fuel Pump Secondary Circuit Intermittent
	//P0234 Engine Turbocharger/Supercharger Overboost Condition
	//P0235 Turbocharger Boost Sensor A Circuit Malfunction
	//P0236 Turbocharger Boost Sensor A Circuit Range/Performance
	//P0237 Turbocharger Boost Sensor A Circuit Low
	//P0238 Turbocharger Boost Sensor A Circuit High
	//P0239 Turbocharger Boost Sensor B Malfunction
	//P0240 Turbocharger Boost Sensor B Circuit Range/Performance
	//P0241 Turbocharger Boost Sensor B Circuit Low
	//P0242 Turbocharger Boost Sensor B Circuit High
	//P0243 Turbocharger Wastegate Solenoid A Malfunction
	//P0244 Turbocharger Wastegate Solenoid A Range/Performance
	//P0245 Turbocharger Wastegate Solenoid A Low
	//P0246 Turbocharger Wastegate Solenoid A High
	//P0247 Turbocharger Wastegate Solenoid B Malfunction
	//P0248 Turbocharger Wastegate Solenoid B Range/Performance
	//P0249 Turbocharger Wastegate Solenoid B Low
	//P0250 Turbocharger Wastegate Solenoid B High
	//P0251 Injection Pump Fuel Metering Control "A" Malfunction (Cam/Rotor/Injector)
	//P0252 Injection Pump Fuel Metering Control "A" Range/Performance (Cam/Rotor/Injector)
	//P0253 Injection Pump Fuel Metering Control "A" Low (Cam/Rotor/Injector)
	//P0254 Injection Pump Fuel Metering Control "A" High (Cam/Rotor/Injector)
	//P0255 Injection Pump Fuel Metering Control "A" Intermittent (Cam/Rotor/Injector)
	//P0256 Injection Pump Fuel Metering Control "B" Malfunction (Cam/Rotor/Injector)
	//P0257 Injection Pump Fuel Metering Control "B" Range/Performance Injector)
	//P0258 Injection Pump Fuel Metering Control "B" Low (Cam/R
	//P0259 Injection Pump Fuel Metering Control "B" High (Cam/R
	//P0260 Injection Pump Fuel Metering Control "B" Intermittent Injector)
	//P0261 Cylinder I Injector Circuit Low
	//P0262 Cylinder I Injector Circuit High
	//P0263 Cylinder I Contribution/Balance Fault
	//P0264 Cylinder 2 Injector Circuit Low
	//P0265 Cylinder 2 Injector Circuit High
	//P0266 Cylinder 2 Contribution/Balance Fault
	//P0267 Cylinder 3 Injector Circuit Low
	//P0268 Cylinder 3 Injector Circuit High
	//P0269 Cylinder 3 Contribution/Balance Fault
	//P0270 Cylinder 4 Injector Circuit Low
	//P0271 Cylinder 4 Injector Circuit High
	//P0272 Cylinder 4 Contribution/Balance Fault
	//P0273 Cylinder 5 Injector Circuit Low
	//P0274 Cylinder 5 Injector Circuit High
	//P0275 Cylinder S Contribution/Balance Fault
	//P0276 Cylinder 6 Injector Circuit Low
	//P0277 Cylinder 6 Injector Circuit High
	//P0278 Cylinder 6 Contribution/Balance Fault
	//P0279 Cylinder 7 Injector Circuit Low
	//P0280 Cylinder 7 Injector Circuit High
	//P0281 Cylinder 7 Contribution/Balance Fault
	//P0282 Cylinder 8 Injector Circuit Low
	//P0283 Cylinder 8 Injector Circuit High
	//P0284 Cylinder 8 Contribution/Balance Fault
	//P0285 Cylinder 9 Injector Circuit Low
	//P0286 Cylinder 9 Injector Circuit High
	//P0287 Cylinder 9 Contribution/Balance Fault
	//P0288 Cylinder 10 Injector Circuit Low
	//P0289 Cylinder 10 Injector Circuit High
	//P0290 Cylinder 10 Contribution/Balance Fault
	//P0291 Cylinder 11 Injector Circuit Low
	//P0292 Cylinder 11 Injector Circuit High
	//P0293 Cylinder 11 Contribution/Balance Fault
	//P0294 Cylinder 12 Injector Circuit Low
	//P0295 Cylinder 12 Injector Circuit High
	//P0296 Cylinder 12 Contribution/Range Fault
	//P0297 Vehicle Overspeed Condition
	//P0298 Engine Oil Over Temperature Condition
	//P0299 Turbocharger/Supercharger "A" Underboost Condition
	//P0300 Random/Multiple Cylinder Misfire Detected
	//P0301 Cylinder 1 Misfire Detected
	//P0302 Cylinder 2 Misfire Detected
	//P0303 Cylinder 3 Misfire Detected
	//P0304 Cylinder 4 Misfire Detected
	//P0305 Cylinder 5 Misfire Detected
	//P0306 Cylinder 6 Misfire Detected
	//P0307 Cylinder 7 Misfire Detected
	//P0308 Cylinder 8 Misfire Detected
	//P0309 Cylinder 9 Misfire Detected
	//P0310 Cylinder 10 Misfire Detected
	//P0311 Cylinder 11 Misfire Detected
	//P0312 Cylinder 12 Misfire Detected
	//P0313 Misfire Detected with Low Fuel
	//P0314 Single Cylinder Misfire (Cylinder not Specified)
	//P0315 Crankshaft Position System Variation Not Learned
	//P0316 Misfire Detected On Startup (First 1000 Revolutions)
	//P0317 Rough Road Hardware Not Present
	//P0318 Rough Road Sensor A Signal Circuit
	//P0319 Rough Road Sensor B Signal Circuit
	//P0320 Ignition/Distributor Engine Speed Input Circuit Malfunction
	//P0321 Ignition/Distributor Engine Speed Input Circuit Range/Performance
	//P0322 Ignition/Distributor Engine Speed Input Circuit No Signal
	//P0323 Ignition/Distributor Engine Speed Input Circuit Intermittent
	//P0324 Knock Control System Error
	//P0325 Knock Sensor 1 Circuit Malfunction (Bank I or Single Sensor)
	//P0326 Knock Sensor 1 Circuit Range/Performance (Bank 1 or Single Sensor)
	//P0327 Knock Sensor 1 Circuit Low Input (Bank I or Single Sensor)
	//P0328 Knock Sensor 1 Circuit High Input (Bank I or Single Sensor)
	//P0329 Knock Sensor 1 Circuit Intermittent (Bank 1 or Single Sensor)
	//P0330 Knock Sensor 2 Circuit Malfunction (Bank 2)
	//P0331 Knock Sensor 2 Circuit Range/Performance (Bank 2)
	//P0332 Knock Sensor 2 Circuit Low Input (Bank 2)
	//P0333 Knock Sensor 2 Circuit High Input (Bank 2)
	//P0334 Knock Sensor 2 Circuit Intermittent (Bank 2)
	//P0335 Crankshaft Position Sensor A Circuit Malfunction
	//P0336 Crankshaft Position Sensor A Circuit Range/Performance
	//P0337 Crankshaft Position Sensor A Circuit Low Input
	//P0338 Crankshaft Position Sensor A Circuit High Input
	//P0339 Crankshaft Position Sensor A Circuit Intermittent
	//P0340 Camshaft Position Sensor Circuit Malfunction
	 OBD_Camshaft_Position_Sensor_Circuit_Range_Performance = 341,
	//P0342 Camshaft Position Sensor Circuit Low Input
	//P0343 Camshaft Position Sensor Circuit High Input
	//P0344 Camshaft Position Sensor Circuit Intermittent
	//P0345 Camshaft Position Sensor A Circuit Malfunction (Bank 2)
	//P0346 Camshaft Position Sensor A Circuit Range/Performance (Bank 2)
	//P0347 Camshaft Position Sensor A Circuit Low Input (Bank 2)
	//P0348 Camshaft Position Sensor A Circuit High Input (Bank 2)
	//P0349 Camshaft Position Sensor A Circuit Intermittent (Bank 2)
	//P0350 Ignition Coil Primary/Secondary Circuit Malfunction
	//P0351 Ignition Coil A Primary/Secondary Circuit Malfunction
	//P0352 Ignition Coil B Primary/Secondary Circuit Malfunction
	//P0353 Ignition Coil C Primary/Secondary Circuit Malfunction
	//P0354 Ignition Coil D Primary/Secondary Circuit Malfunction
	//P0355 Ignition Coil E Primary/Secondary Circuit Malfunction
	//P0356 Ignition Coil F Primary/Secondary Circuit Malfunction
	//P0357 Ignition Coil G Primary/Secondary Circuit Malfunction
	//P0358 Ignition Coil H Primary/Secondary Circuit Malfunction
	//P0359 Ignition Coil I Primary/Secondary Circuit Malfunction
	//P0360 Ignition Coil J Primary/Secondary Circuit Malfunction
	//P0361 Ignition Coil K Primary/Secondary Circuit Malfunction
	//P0362 Ignition Coil L Primary/Secondary Circuit Malfunction
	//P0363 Misfire Detected - Fueling Disabled
	//P0364 Reserved
	//P0365 Camshaft Position Sensor "B" Circuit (Bank 1)
	//P0366 Camshaft Position Sensor "B" Circuit Range/Performance (Bank 1)
	//P0367 Camshaft Position Sensor "B" Circuit Low (Bank 1)
	//P0368 Camshaft Position Sensor "B" Circuit High (Bank 1)
	//P0369 Camshaft Position Sensor "B" Circuit Intermittent (Bank 1)
	//P0370 Timing Reference High Resolution Signal A Malfunction
	//P0371 Timing Reference High Resolution Signal A Too Many Pulses
	//P0372 Timing Reference High Resolution Signal A Too Few Pulses
	//P0373 Timing Reference High Resolution Signal A Intermittent/Erratic Pulses
	//P0374 Timing Reference High Resolution Signal A No Pulses
	//P0375 Timing Reference High Resolution Signal B Malfunction
	//P0376 Timing Reference High Resolution Signal B Too Many Pulses
	//P0377 Timing Reference High Resolution Signal B Too Few Pulses
	//P0378 Timing Reference High Resolution Signal B Intermittent/Erratic Pulses
	//P0379 Timing Reference High Resolution Signal B No Pulses
	//P0380 Glow Plug/Heater Circuit "A" Malfunction
	//P0381 Glow Plug/Heater Indicator Circuit Malfunction
	//P0382 Exhaust Gas Recirculation Flow Malfunction
	//P0383 Glow Plug Control Module Control Circuit Low
	//P0384 Glow Plug Control Module Control Circuit High
	//P0385 Crankshaft Position Sensor B Circuit Malfunction
	//P0386 Crankshaft Position Sensor B Circuit Range/Performance
	//P0387 Crankshaft Position Sensor B Circuit Low Input
	//P0388 Crankshaft Position Sensor B Circuit High Input
	//P0389 Crankshaft Position Sensor B Circuit Intermittent
	//P0390 Camshaft Position Sensor "B" Circuit (Bank 2)
	//P0391 Camshaft Position Sensor "B" Circuit Range/Performance (Bank 2)
	//P0392 Camshaft Position Sensor "B" Circuit Low (Bank 2)
	//P0393 Camshaft Position Sensor "B" Circuit High (Bank 2)
	//P0394 Camshaft Position Sensor "B" Circuit Intermittent (Bank 2)
	//DTC Codes - P0400-P0499 - Auxiliary Emissions Controls
	//P0400 Exhaust Gas Recirculation Flow Malfunction
	//P0401 Exhaust Gas Recirculation Flow Insufficient Detected
	//P0402 Exhaust Gas Recirculation Flow Excessive Detected
	//P0403 Exhaust Gas Recirculation Circuit Malfunction
	//P0404 Exhaust Gas Recirculation Circuit Range/Performance
	//P0405 Exhaust Gas Recirculation Sensor A Circuit Low
	//P0406 Exhaust Gas Recirculation Sensor A Circuit High
	//P0407 Exhaust Gas Recirculation Sensor B Circuit Low
	//P0408 Exhaust Gas Recirculation Sensor B Circuit High
	//P0409 Exhaust Gas Recirculation Sensor "A" Circuit
	//P0410 Secondary Air Injection System Malfunction
	//P0411 Secondary Air Injection System Incorrect Flow Detected
	//P0412 Secondary Air Injection System Switching Valve A Circuit Malfunction
	//P0413 Secondary Air Injection System Switching Valve A Circuit Open
	//P0414 Secondary Air Injection System Switching Valve A Circuit Shorted
	//P0415 Secondary Air Injection System Switching Valve B Circuit Malfunction
	//P0416 Secondary Air Injection System Switching Valve B Circuit Open
	//P0417 Secondary Air Injection System Switching Valve B Circuit Shorted
	//P0418 Secondary Air Injection System Relay "A" Circuit Malfunction
	//P0419 Secondary Air Injection System Relay "B" Circuit Malfunction
	//P0420 Catalyst System Efficiency Below Threshold (Bank 1)
	//P0421 Warm Up Catalyst Efficiency Below Threshold (Bank 1)
	//P0422 Main Catalyst Efficiency Below Threshold (Bank 1)
	//P0423 Heated Catalyst Efficiency Below Threshold (Bank 1)
	//P0424 Heated Catalyst Temperature Below Threshold (Bank 1)
	//P0424 Heated Catalyst Temperature Below Threshold (Bank 1)
	//P0425 Catalyst Temperature Sensor (Bank 1)
	//P0426 Catalyst Temperature Sensor Range/Performance (Bank 1)
	//P0427 Catalyst Temperature Sensor Low (Bank 1)
	//P0428 Catalyst Temperature Sensor High (Bank 1)
	//P0429 Catalyst Heater Control Circuit
	//P0430 Catalyst System Efficiency Below Threshold (Bank 2)
	//P0431 Warm Up Catalyst Efficiency Below Threshold (Bank 2)
	//P0432 Main Catalyst Efficiency Below Threshold (Bank 2)
	//P0433 Heated Catalyst Efficiency Below Threshold (Bank 2)
	//P0434 Heated Catalyst Temperature Below Threshold (Bank 2)
	//P0435 Catalyst Temperature Sensor (Bank 2)
	//P0436 Catalyst Temperature Sensor Range/Performance (Bank 2)
	//P0437 Catalyst Temperature Sensor Low (Bank 2)
	//P0438 Catalyst Temperature Sensor High (Bank 2)
	//P0439 Catalyst Heater Control Circuit
	//P0440 Evaporative Emission Control System Malfunction
	//P0441 Evaporative Emission Control System Incorrect Purge Flow
	//P0442 Evaporative Emission Control System Leak Detected (small leak)
	//P0443 Evaporative Emission Control System Purge Control Valve Circuit
	//P0444 Evaporative Emission Control System Purge Control Valve Circuit Open
	//P0445 Evaporative Emission Control System Purge Control Valve Circuit Shorted
	//P0446 Evaporative Emission Control System Vent Control Circuit Malfunction
	//P0447 Evaporative Emission Control System Vent Control Circuit Open
	//P0448 Evaporative Emission Control System Vent Control Circuit Shorted
	//P0449 Evaporative Emission Control System Vent Valve/Solenoid Circuit Malfunction
	//P0450 Evaporative Emission Control System Pressure Sensor Malfunction
	//P0451 Evaporative Emission Control System Pressure Sensor Range/Performance
	//P0452 Evaporative Emission Control System Pressure Sensor Low Input
	//P0453 Evaporative Emission Control System Pressure Sensor High Input
	//P0454 Evaporative Emission Control System Pressure Sensor Intermittent
	//P0455 Evaporative Emission Control System Leak Detected (gross leak)
	//P0456 Evaporative Emissions System Small Leak Detected
	//P0457 Evaporative Emission Control System Leak Detected
	//P0458 Evaporative Emission System Purge Control Valve Circuit Low
	//P0459 Evaporative Emission System Purge Control Valve Circuit High
	//P0460 Fuel Level Sensor Circuit Malfunction
	//P0461 Fuel Level Sensor Circuit Range/Performance
	//P0462 Fuel Level Sensor Circuit Low Input
	//P0463 Fuel Level Sensor Circuit High Input
	//P0464 Fuel Level Sensor Circuit Intermittent
	//P0465 Purge Flow Sensor Circuit Malfunction
	//P0466 Purge Flow Sensor Circuit Range/Performance
	//P0467 Purge Flow Sensor Circuit Low Input
	//P0468 Purge Flow Sensor Circuit High Input
	//P0469 Purge Flow Sensor Circuit Intermittent
	//P0470 Exhaust Pressure Sensor Malfunction
	//P0471 Exhaust Pressure Sensor Range/Performance
	//P0472 Exhaust Pressure Sensor Low
	//P0473 Exhaust Pressure Sensor High
	//P0474 Exhaust Pressure Sensor Intermittent
	//P0475 Exhaust Pressure Control Valve Malfunction
	//P0476 Exhaust Pressure Control Valve Range/Performance
	//P0477 Exhaust Pressure Control Valve Low
	//P0478 Exhaust Pressure Control Valve High
	//P0479 Exhaust Pressure Control Valve Intermittent
	//P0480 Cooling Fan I Control Circuit Malfunction
	//P0481 Cooling Fan 2 Control Circuit Malfunction
	//P0482 Cooling Fan 3 Control Circuit Malfunction
	//P0483 Cooling Fan Rationality Check Malfunction
	//P0484 Cooling Fan Circuit Over Current
	//P0485 Cooling Fan Power/Ground Circuit Malfunction
	//P0486 Exhaust Gas Recirculation Sensor "B" Circuit
	//P0487 Exhaust Gas Recirculation Throttle Control Circuit "A" Open
	//P0488 Exhaust Gas Recirculation Throttle Control Circuit "A" Range/Performance
	//P0489 Exhaust Gas Recirculation "A" Control Circuit Low
	//P0490 Exhaust Gas Recirculation "A" Control Circuit High
	//P0491 Secondary Air Injection System Insufficient Flow Bank 1
	//P0492 Secondary Air Injection System Insufficient Flow Bank 2
	//P0493 Fan Overspeed
	//P0494 Fan Speed Low
	//P0495 Fan Speed High
	//P0496 EVAP Flow During A Non-Purge Condition
	//P0497 Evaporative Emission System Low Purge Flow
	//P0498 Evaporative Emission System Vent Valve Control Circuit Low
	//P0499 Evaporative Emission System Vent Valve Control Circuit High
	//DTC Codes - P0500-P0599 - Vehicle Speed Controls and Idle Control System
	//P0500 Vehicle Speed Sensor Malfunction
	//P0501 Vehicle Speed Sensor Range/Performance
	//P0502 Vehicle Speed Sensor Low Input
	//P0503 Vehicle Speed Sensor Intermittent/Erratic/High
	//P0504 Brake Switch "A"/"B" Correlation
	//P0505 Idle Control System Malfunction
	//P0506 Idle Control System RPM Lower Than Expected
	//P0507 Idle Control System RPM Higher Than Expected
	//P0508 Idle Air Control System Circuit Low
	//P0509 Idle Air Control System Circuit High
	//P0510 Closed Throttle Position Switch Malfunction
	//P0511 Idle Air Control Circuit
	//P0512 Starter Request Circuit
	//P0513 Incorrect Immobilizer Key
	//P0514 Battery Temperature Sensor Circuit Range/Performance
	//P0515 Battery Temperature Sensor Circuit
	//P0516 Battery Temperature Sensor Circuit Low
	//P0517 Battery Temperature Sensor Circuit High
	//P0518 Idle Air Control Circuit Intermittent
	//P0519 Idle Air Control System Performance
	//P0520 Engine Oil Pressure Sensor/Switch Circuit Malfunction
	//P0521 Engine Oil Pressure Sensor/Switch Circuit Range/Performance
	//P0522 Engine Oil Pressure Sensor/Switch Circuit Low Voltage
	//P0523 Engine Oil Pressure Sensor/Switch Circuit High Voltage
	//P0524 Engine Oil Pressure Too Low
	//P0525 Cruise Control Servo Control Circuit Range/Performance
	//P0526 Fan Speed Sensor Circuit
	//P0527 Fan Speed Sensor Circuit Range/Performance
	//P0528 Fan Speed Sensor Circuit No Signal
	//P0529 Fan Speed Sensor Circuit Intermittent
	//P0530 A/C Refrigerant Pressure Sensor Circuit Malfunction
	//P0531 A/C Refrigerant Pressure Sensor Circuit Range/Performance
	//P0532 A/C Refrigerant Pressure Sensor Circuit Low Input
	//P0533 A/C Refrigerant Pressure Sensor Circuit High Input
	//P0534 Air Conditioner Refrigerant Charge Loss
	//P0535 A/C Evaporator Temperature Sensor Circuit
	//P0536 A/C Evaporator Temperature Sensor Circuit Range/Performance
	//P0537 A/C Evaporator Temperature Sensor Circuit Low
	//P0538 A/C Evaporator Temperature Sensor Circuit High
	//P0539 A/C Evaporator Temperature Sensor Circuit Intermittent
	//P0540 Intake Air Heater "A" Circuit
	//P0541 Intake Air Heater "A" Circuit Low
	//P0542 Intake Air Heater "A" Circuit High
	//P0543 Intake Air Heater "A" Circuit Open
	//P0544 Exhaust Gas Temperature Sensor Circuit
	//P0545 Exhaust Gas Temperature Sensor Circuit Low
	//P0546 Exhaust Gas Temperature Sensor Circuit High
	//P0547 Exhaust Gas Temperature Sensor Circuit
	//P0548 Exhaust Gas Temperature Sensor Circuit Low
	//P0549 Exhaust Gas Temperature Sensor Circuit High
	//P0550 Power Steering Pressure Sensor Circuit Malfunction
	//P0551 Power Steering Pressure Sensor Circuit Range/Performance
	//P0552 Power Steering Pressure Sensor Circuit Low Input
	//P0553 Power Steering Pressure Sensor Circuit High Input
	//P0554 Power Steering Pressure Sensor Circuit Intermittent
	//P0555 Brake Booster Pressure Sensor Circuit
	//P0556 Brake Booster Pressure Sensor Circuit Range/Performance
	//P0557 Brake Booster Pressure Sensor Circuit Low
	//P0558 Brake Booster Pressure Sensor Circuit High
	//P0559 Brake Booster Pressure Sensor Circuit Intermittent
	OBD_System_Voltage_Malfunction = 560,
	//P0561 System Voltage Unstable
	//P0562 System Voltage Low
	//P0563 System Voltage High
	//P0564 Cruise Control Multi-Function Input "A" Circuit
	//P0565 Cruise Control On Signal Malfunction
	//P0566 Cruise Control Off Signal Malfunction
	//P0567 Cruise Control Resume Signal Malfunction
	//P0568 Cruise Control Set Signal Malfunction
	//P0569 Cruise Control Coast Signal Malfunction
	//P0570 Cruise Control Accel Signal Malfunction
	//P0571 Cruise Control/Brake Switch A Circuit Malfunction
	//P0572 Cruise Control/Brake Switch A Circuit Low
	//P0573 Cruise Control/Brake Switch A Circuit High
	//P0574 Cruise Control System - Vehicle Speed Too High
	//P0575 Cruise Control Input Circuit
	//P0576 Cruise Control Input Circuit Low
	//P0577 Cruise Control Input Circuit High
	//P0578 Cruise Control Multi-Function Input "A" Circuit Stuck
	//P0579 Cruise Control Multi-Function Input "A" Circuit Range/Performance
	//P0580 Cruise Control Multi-Function Input "A" Circuit Low
	//P0581 Cruise Control Multi-Function Input "A" Circuit High
	//P0582 Cruise Control Vacuum Control Circuit/Open
	//P0583 Cruise Control Vacuum Control Circuit Low
	//P0584 Cruise Control Vacuum Control Circuit High
	//P0585 Cruise Control Multi-Function Input "A"/"B" Correlation
	//P0586 Cruise Control Vent Control Circuit/Open
	//P0587 Cruise Control Vent Control Circuit Low
	//P0588 Cruise Control Vent Control Circuit High
	//P0589 Cruise Control Multi-Function Input "B" Circuit
	//P0590 Cruise Control Multi-Function Input "B" Circuit Stuck
	//P0591 Cruise Control Multi-Function Input "B" Circuit Range/Performance
	//P0592 Cruise Control Multi-Function Input "B" Circuit Low
	//P0593 Cruise Control Multi-Function Input "B" Circuit High
	//P0594 Cruise Control Servo Control Circuit/Open
	//P0595 Cruise Control Servo Control Circuit Low
	//P0596 Cruise Control Servo Control Circuit High
	//P0597 Thermostat Heater Control Circuit/Open
	//P0598 Thermostat Heater Control Circuit Low
	//P0599 Thermostat Heater Control Circuit High
	//P0600 Serial Communication Link Malfunction
	//P0601 Internal Control Module Memory Check Sum Error
	//P0602 Control Module Programming Error
	//P0603 Internal Control Module Keep Alive Memory (KAM) Error
	//P0604 Internal Control Module Random Access Memory (RAM) Error
	//P0605 Internal Control Module Read Only Memory (ROM) Error
	OBD_PCM_Processor_Fault = 606,
	//P0607 Control Module Performance
	//P0608 Control Module VSS Output "A" Malfunction
	//P0609 Control Module VSS Output "B" Malfunction
	//P0610 Control Module Vehicle Options Error
	//P0611 Fuel Injector Control Module Performance
	//P0612 Fuel Injector Control Module Relay Control
	//P0613 TCM Processor
	//P0614 ECM / TCM Incompatible
	//P0615 Starter Relay Circuit
	//P0616 Starter Relay Circuit Low
	//P0617 Starter Relay Circuit High
	//P0618 Alternative Fuel Control Module KAM Error
	//P0619 Alternative Fuel Control Module RAM/ROM Error
	//P0620 Generator Control Circuit Malfunction
	//P0621 Generator Lamp "L" Control Circuit Malfunction
	//P0622 Generator Field "F" Control Circuit Malfunction
	//P0623 Generator Lamp Control Circuit
	//P0624 Fuel Cap Lamp Control Circuit
	//P0625 Generator Field/F Terminal Circuit Low
	//P0626 Generator Field/F Terminal Circuit High
	//P0627 Fuel Pump &ldquo;A&rdquo; Control Circuit /Open
	//P0628 Fuel Pump &ldquo;A&rdquo; Control Circuit Low
	//P0629 Fuel Pump &ldquo;A&rdquo; Control Circuit High
	//P0630 VIN Not Programmed or Incompatible - ECM/PCM
	//P0631 VIN Not Programmed or Incompatible - TCM
	//P0632 Odometer Not Programmed - ECM/PCM
	//P0633 Immobilizer Key Not Programmed - ECM/PCM
	//P0634 PCM/ECM/TCM Internal Temperature Too High
	//P0635 Power Steering Control Circuit
	//P0636 Power Steering Control Circuit Low
	//P0637 Power Steering Control Circuit High
	//P0638 Throttle Actuator Control Range/Performance (Bank 1)
	//P0639 Throttle Actuator Control Range/Performance (Bank 2)
	//P0640 Intake Air Heater Control Circuit
	//P0641 Sensor Reference Voltage &ldquo;A&rdquo; Circuit/Open
	//P0642 Sensor Reference Voltage &ldquo;A&rdquo; Circuit Low
	//P0643 Sensor Reference Voltage &ldquo;A&rdquo; Circuit High
	//P0644 Driver Display Serial Communication Circuit
	//P0645 A/C Clutch Relay Control Circuit
	//P0646 A/C Clutch Relay Control Circuit Low
	//P0647 A/C Clutch Relay Control Circuit High
	//P0648 Immobilizer Lamp Control Circuit
	//P0649 Speed Control Lamp Control Circuit
	//P0650 Malfunction Indicator Lamp (MIL) Control Circuit Malfunction
	//P0651 Sensor Reference Voltage &ldquo;B&rdquo; Circuit/Open
	//P0652 Sensor Reference Voltage &ldquo;B&rdquo; Circuit Low
	//P0653 Sensor Reference Voltage &ldquo;B&rdquo; Circuit High
	//P0654 Engine RPM Output Circuit Malfunction
	//P0655 Engine Hot Lamp Output Control Circuit Malfunction
	//P0656 Fuel Level Output Circuit Malfunction
	//P0657 Actuator Supply Voltage "A" Circuit/Open
	//P0658 Actuator Supply Voltage "A" Circuit Low
	//P0659 Actuator Supply Voltage "A" Circuit High
	//P0660 Intake Manifold Tuning Valve Control Circuit/Open Bank 1
	//P0661 Intake Manifold Tuning Valve Control Circuit Low Bank 1
	//P0662 Intake Manifold Tuning Valve Control Circuit High Bank 1
	//P0663 Intake Manifold Tuning Valve Control Circuit/Open Bank 2
	//P0664 Intake Manifold Tuning Valve Control Circuit Low Bank 2
	//P0665 Intake Manifold Tuning Valve Control Circuit High Bank 2
	//P0666 PCM/ECM/TCM Internal Temperature Sensor Circuit
	//P0667 PCM/ECM/TCM Internal Temperature Sensor Range/Performance
	//P0668 PCM/ECM/TCM Internal Temperature Sensor Circuit Low
	//P0669 PCM/ECM/TCM Internal Temperature Sensor Circuit High
	//P0670 Glow Plug Module Control Circuit
	//P0671 Cylinder 1 Glow Plug Circuit
	//P0672 Cylinder 2 Glow Plug Circuit
	//P0673 Cylinder 3 Glow Plug Circuit
	//P0674 Cylinder 4 Glow Plug Circuit
	//P0675 Cylinder 5 Glow Plug Circuit
	//P0676 Cylinder 6 Glow Plug Circuit
	//P0677 Cylinder 7 Glow Plug Circuit
	//P0678 Cylinder 8 Glow Plug Circuit
	//P0679 Cylinder 9 Glow Plug Circuit
	//P0680 Cylinder 10 Glow Plug Circuit
	//P0681 Cylinder 11 Glow Plug Circuit
	//P0682 Cylinder 12 Glow Plug Circuit
	//P0683 Glow Plug Control Module to PCM Communication Circuit
	//P0684 Glow Plug Control Module to PCM Communication Circuit Range/Performance
	//P0685 ECM/PCM Power Relay Control Circuit /Open
	//P0686 ECM/PCM Power Relay Control Circuit Low
	//P0687 ECM/PCM Power Relay Control Circuit High
	//P0688 ECM/PCM Power Relay Sense Circuit /Open
	//P0689 ECM/PCM Power Relay Sense Circuit Low
	//P0690 ECM/PCM Power Relay Sense Circuit High
	//P0691 Fan 1 Control Circuit Low P0692 Fan 1 Control Circuit High
	//P0693 Fan 2 Control Circuit Low
	//P0694 Fan 2 Control Circuit High
	//P0695 Fan 3 Control Circuit Low
	//P0696 Fan 3 Control Circuit High
	//P0697 Sensor Reference Voltage &ldquo;C&rdquo; Circuit/Open
	//P0698 Sensor Reference Voltage &ldquo;C&rdquo; Circuit Low
	//P0699 Sensor Reference Voltage &ldquo;C&rdquo; Circuit High
	//P0700 Transmission Control System Malfunction
	//P0701 Transmission Control System Range/Performance
	//P0702 Transmission Control System Electrical
	//P0703 Torque Converter/Brake Switch B Circuit Malfunction
	//P0704 Clutch Switch Input Circuit Malfunction
	//P0705 Transmission Range Sensor Circuit malfunction (PRNDL Input)
	//P0706 Transmission Range Sensor Circuit Range/Performance
	//P0707 Transmission Range Sensor Circuit Low Input
	//P0708 Transmission Range Sensor Circuit High Input
	//P0709 Transmission Range Sensor Circuit Intermittent
	//P0710 Transmission Fluid Temperature Sensor Circuit Malfunction
	//P0711 Transmission Fluid Temperature Sensor Circuit Range/Performance
	//P0712 Transmission Fluid Temperature Sensor Circuit Low Input
	//P0713 Transmission Fluid Temperature Sensor Circuit High Input
	//P0714 Transmission Fluid Temperature Sensor Circuit Intermittent
	//P0715 Input/Turbine Speed Sensor Circuit Malfunction
	//P0716 Input/Turbine Speed Sensor Circuit Range/Performance
	//P0717 Input/Turbine Speed Sensor Circuit No Signal
	//P0718 Input/Turbine Speed Sensor Circuit Intermittent
	//P0719 Torque Converter/Brake Switch B Circuit Low
	//P0720 Output Speed Sensor Circuit Malfunction
	//P0721 Output Speed Sensor Range/Performance
	//P0722 Output Speed Sensor No Signal
	//P0723 Output Speed Sensor Intermittent
	//P0724 Torque Converter/Brake Switch B Circuit High
	//P0725 Engine Speed input Circuit Malfunction
	//P0726 Engine Speed Input Circuit Range/Performance
	//P0727 Engine Speed Input Circuit No Signal
	//P0728 Engine Speed Input Circuit Intermittent
	//P0729 Gear 6 Incorrect Ratio
	//P0730 Incorrect Gear Ratio
	//P0731 Gear I Incorrect ratio
	//P0732 Gear 2 Incorrect ratio
	//P0733 Gear 3 Incorrect ratio
	//P0734 Gear 4 Incorrect ratio
	//P0735 Gear 5 Incorrect ratio
	//P0736 Reverse incorrect gear ratio
	//P0737 TCM Engine Speed Output Circuit
	//P0738 TCM Engine Speed Output Circuit Low
	//P0739 TCM Engine Speed Output Circuit High
	//P0740 Torque Converter Clutch Circuit Malfunction
	//P0741 Torque Converter Clutch Circuit Performance or Stuck Off
	//P0742 Torque Converter Clutch Circuit Stock On
	//P0743 Torque Converter Clutch Circuit Electrical
	//P0744 Torque Converter Clutch Circuit Intermittent
	//P0745 Pressure Control Solenoid Malfunction
	//P0746 Pressure Control Solenoid Performance or Stuck Off
	//P0747 Pressure Control Solenoid Stuck On
	//P0748 Pressure Control Solenoid Electrical
	//P0749 Pressure Control Solenoid Intermittent
	//P0750 Shift Solenoid A Malfunction
	//P0751 Shift Solenoid A Performance or Stuck Off
	//P0752 Shift Solenoid A Stuck On
	//P0753 Shift Solenoid A Electrical
	//P0754 Shift Solenoid A Intermittent
	//P0755 Shift Solenoid B Malfunction
	//P0756 Shift Solenoid B Performance or Stock Off
	//P0757 Shift Solenoid B Stuck On
	//P0758 Shift Solenoid B Electrical
	//P0759 Shift Solenoid B Intermittent
	//P0760 Shift Solenoid C Malfunction
	//P0761 Shift Solenoid C Performance or Stuck Off
	//P0762 Shift Solenoid C Stuck On
	//P0763 Shift Solenoid C Electrical
	//P0764 Shift Solenoid C Intermittent
	//P0765 Shift Solenoid D Malfunction
	//P0766 Shift Solenoid D Performance or Stuck Off
	//P0767 Shift Solenoid D Stuck On
	//P0768 Shift Solenoid D Electrical
	//P0769 Shift Solenoid D Intermittent
	//P0770 Shift Solenoid E Malfunction
	//P0771 Shift Solenoid E Performance or Stuck Off
	//P0772 Shift Solenoid E Stuck On
	//P0773 Shift Solenoid E Electrical
	//P0774 Shift Solenoid E Intermittent
	//P0775 Pressure Control Solenoid "B"
	//P0776 Pressure Control Solenoid "B" Performance or Stuck off
	//P0777 Pressure Control Solenoid "B" Stuck On
	//P0778 Pressure Control Solenoid "B" Electrical
	//P0779 Pressure Control Solenoid "B" Intermittent
	//P0780 Shift Malfunction
	//P0781 1-2 Shift Malfunction
	//P0782 2-3 Shift Malfunction
	//P0783 3-4 Shift Malfunction
	//P0784 4-5 Shift Malfunction
	//P0785 Shift/Timing Solenoid Malfunction
	//P0786 Shift/Timing Solenoid Range/Performance
	//P0787 Shift/Timing Solenoid Low
	//P0788 Shift/Timing Solenoid High
	//P0789 Shift/Timing Solenoid Intermittent
	//P0790 Normal/Performance Switch Circuit Malfunction
	//P0791 Intermediate Shaft Speed Sensor &ldquo;A&rdquo; Circuit
	//P0792 Intermediate Shaft Speed Sensor &ldquo;A&rdquo; Circuit Range/Performance
	//P0793 Intermediate Shaft Speed Sensor &ldquo;A&rdquo; Circuit No Signal
	//P0794 Intermediate Shaft Speed Sensor &ldquo;A&rdquo; Circuit Intermittent
	//P0795 Pressure Control Solenoid "C"
	//P0796 Pressure Control Solenoid "C" Performance or Stuck off
	//P0797 Pressure Control Solenoid "C" Stuck On
	//P0798 Pressure Control Solenoid "C" Electrical
	//P0799 Pressure Control Solenoid "C" Intermittent
	//P0800 Transfer Case Control System (MIL Request)
	//P0801 Reverse Inhibit Control Circuit Malfunction
	//P0802 Transmission Control System MIL Request Circuit/Open
	//P0803 1-4 Upshift (Skip Shift) Solenoid Control Circuit Malfunction
	//P0804 1-4 Upshift (Skip Shift) Lamp Control Circuit Malfunction
	//P0805 Clutch Position Sensor Circuit
	//P0806 Clutch Position Sensor Circuit Range/Performance
	//P0807 Clutch Position Sensor Circuit Low
	//P0808 Clutch Position Sensor Circuit High
	//P0809 Clutch Position Sensor Circuit Intermittent
	//P0810 Clutch Position Control Error
	//P0811 Excessive Clutch Slippage
	//P0812 Reverse Input Circuit
	//P0813 Reverse Output Circuit
	//P0814 Transmission Range Display Circuit
	//P0815 Upshift Switch Circuit
	//P0816 Downshift Switch Circuit
	//P0817 Starter Disable Circuit
	//P0818 Driveline Disconnect Switch Input Circuit
	//P0819 Up and Down Shift Switch to Transmission Range Correlation
	//P0820 Gear Lever X-Y Position Sensor Circuit
	//P0821 Gear Lever X Position Circuit
	//P0822 Gear Lever Y Position Circuit
	//P0823 Gear Lever X Position Circuit Intermittent
	//P0824 Gear Lever Y Position Circuit Intermittent
	//P0825 Gear Lever Push-Pull Switch (Shift Anticipate
	//P0826 Up and Down Shift Switch Circuit
	//P0827 Up and Down Shift Switch Circuit Low
	//P0828 Up and Down Shift Switch Circuit High
	//P0829 5-6 Shift
	//P0830 Clutch Pedal Switch "A" Circuit
	//P0831 Clutch Pedal Switch "A" Circuit Low
	//P0832 Clutch Pedal Switch "A" Circuit High
	//P0833 Clutch Pedal Switch "B" Circuit
	//P0834 Clutch Pedal Switch "B" Circuit Low
	//P0835 Clutch Pedal Switch "B" Circuit High
	//P0836 Four Wheel Drive (4WD) Switch Circuit
	//P0837 Four Wheel Drive (4WD) Switch Circuit Range/Performance
	//P0838 Four Wheel Drive (4WD) Switch Circuit Low
	//P0839 Four Wheel Drive (4WD) Switch Circuit High P0840 Transmission Fluid Pressure Sensor/Switch "A" Circuit
	//P0840 Transmission Fluid Pressure Sensor/Switch "A" Circuit
	//P0841 Transmission Fluid Pressure Sensor/Switch "A" Circuit Range/Performance
	//P0842 Transmission Fluid Pressure Sensor/Switch "A" Circuit Low
	//P0843 Transmission Fluid Pressure Sensor/Switch "A" Circuit High
	//P0844 Transmission Fluid Pressure Sensor/Switch "A" Circuit Intermittent
	//P0845 Transmission Fluid Pressure Sensor/Switch "B" Circuit
	//P0846 Transmission Fluid Pressure Sensor/Switch "B" Circuit Range/Performance
	//P0847 Transmission Fluid Pressure Sensor/Switch "B" Circuit Low
	//P0848 Transmission Fluid Pressure Sensor/Switch "B" Circuit High
	//P0849 Transmission Fluid Pressure Sensor/Switch "B" Circuit Intermittent
	//P0850 Park/Neutral Switch Input Circuit
	//P0851 Park/Neutral Switch Input Circuit Low
	//P0852 Park/Neutral Switch Input Circuit High
	//P0853 Drive Switch Input Circuit
	//P0854 Drive Switch Input Circuit Low
	//P0855 Drive Switch Input Circuit High
	//P0856 Traction Control Input Signal
	//P0857 Traction Control Input Signal Range/Performance
	//P0858 Traction Control Input Signal Low
	//P0859 Traction Control Input Signal High
	//P0860 Gear Shift Module Communication Circuit
	//P0861 Gear Shift Module Communication Circuit Low
	//P0862 Gear Shift Module Communication Circuit High
	//P0863 TCM Communication Circuit
	//P0864 TCM Communication Circuit Range/Performance
	//P0865 TCM Communication Circuit Low
	//P0866 TCM Communication Circuit High
	//P0867 Transmission Fluid Pressure
	//P0868 Transmission Fluid Pressure Low P0869 Transmission Fluid Pressure High
	//P0869 Transmission Fluid Pressure High
	//P0870 Transmission Fluid Pressure Sensor/Switch &ldquo;C&rdquo; Circuit
	//P0871 Transmission Fluid Pressure Sensor/Switch &ldquo;C&rdquo; Circuit Range/Performance
	//P0872 Transmission Fluid Pressure Sensor/Switch &ldquo;C&rdquo; Circuit Low
	//P0873 Transmission Fluid Pressure Sensor/Switch &ldquo;C&rdquo; Circuit High
	//P0874 Transmission Fluid Pressure Sensor/Switch &ldquo;C&rdquo; Circuit Intermittent
	//P0875 Transmission Fluid Pressure Sensor/Switch &ldquo;D&rdquo; Circuit
	//P0876 Transmission Fluid Pressure Sensor/Switch &ldquo;D&rdquo; Circuit Range/Performance
	//P0877 Transmission Fluid Pressure Sensor/Switch &ldquo;D&rdquo; Circuit Low
	//P0878 Transmission Fluid Pressure Sensor/Switch &ldquo;D&rdquo; Circuit High
	//P0879 Transmission Fluid Pressure Sensor/Switch &ldquo;D&rdquo; Circuit Intermittent
	//P0880 TCM Power Input Signal
	//P0881 TCM Power Input Signal Range/Performance
	//P0882 TCM Power Input Signal Low
	//P0883 TCM Power Input Signal High
	//P0884 TCM Power Input Signal Intermittent
	//P0885 TCM Power Relay Control Circuit/Open
	//P0886 TCM Power Relay Control Circuit Low
	//P0887 TCM Power Relay Control Circuit High
	//P0888 TCM Power Relay Sense Circuit
	//P0889 TCM Power Relay Sense Circuit Range/Performance
	//P0890 TCM Power Relay Sense Circuit Low
	//P0891 TCM Power Relay Sense Circuit High
	//P0892 TCM Power Relay Sense Circuit Intermittent
	//P0893 Multiple Gears Engaged
	//P0894 Transmission Component Slipping
	//P0895 Shift Time Too Short
	//P0896 Shift Time Too Long
	//P0897 Transmission Fluid Deteriorated
	//P0898 Transmission Control System MIL Request Circuit Low
	//P0899 Transmission Control System MIL Request Circuit High
	//P2000 NOx Trap Efficiency Below Threshold Bank1
	//P2001 NOx Trap Efficiency Below Threshold Bank2
	//P2002 Particulate Trap Efficiency Below Threshold Bank1
	//P2003 Particulate Trap Efficiency Below Threshold Bank2
	//P2004 Intake Manifold Runner Ctrl Stuck Open Bank1
	//P2005 Intake Manifold Runner Ctrl Stuck Open Bank2
	//P2006 Intake Manifold Runner Ctrl Stuck Closed Bank1
	//P2007 Intake Manifold Runner Ctrl Stuck Closed Bank2
	//P2008 Intake Manifold Runner Ctrl Circ/Open Bank1
	//P2009 Intake Manifold Runner Ctrl Circ Low Bank1
	//P2010 Intake Manifold Runner Ctrl Circ High Bank1
	//P2011 Intake Manifold Runner Ctrl Circ/Open Bank2
	//P2012 Intake Manifold Runner Ctrl Circ Low Bank2
	//P2013 Intake Manifold Runner Ctrl Circ High Bank2
	//P2014 Intake Manifold Runner Pos Sensor/Switch Circ Bank1
	//P2015 Intake Manifold Runner Pos Sensor/Switch Circ Range/Perf Bank1
	//P2016 Intake Manifold Runner Pos Sensor/Switch Circ Low Bank1
	//P2017 Intake Manifold Runner Pos Sensor/Switch Circ High Bank1
	//P2018 Intake Manifold Runner Pos Sensor/Switch Circ Interm Bank1
	//P2019 Intake Manifold Runner Pos Sensor/Switch Circ Bank2
	//P2020 Intake Manifold Runner Pos Sensor/Switch Circ Range/Perf Bank2
	//P2021 Intake Manifold Runner Pos Sensor/Switch Circ Low Bank2
	//P2022 Intake Manifold Runner Pos Sensor/Switch Circ High Bank2
	//P2023 Intake Manifold Runner Pos Sensor/Switch Circ Interm Bank2
	//P2024 EVAP Fuel Vapor Temp Sensor Circ
	//P2025 EVAP Fuel Vapor Temp Sensor Perf
	//P2026 EVAP Fuel Vapor Temp Sensor Circ Low Voltage
	//P2027 EVAP Fuel Vapor Temp Sensor Circ High Voltage
	//P2028 EVAP Fuel Vapor Temp Sensor Circ Interm
	//P2029 Fuel Fired Heater Disabled
	//P2030 Fuel Fired Heater Perf
	//P2031 Exhaust Gas Temp Sensor Circ Bank1 Sensor 2
	//P2032 Exhaust Gas Temp Sensor Circ Low Bank1 Sensor 2
	//P2033 Exhaust Gas Temp Sensor Circ High Bank1 Sensor 2
	//P2034 Exhaust Gas Temp Sensor Circ Bank2 Sensor 2
	//P2035 Exhaust Gas Temp Sensor Circ Low Bank2 Sensor 2
	//P2036 Exhaust Gas Temp Sensor Circ High Bank2 Sensor 2
	//P2037 Reductant Inj Air Press Sensor Circ
	//P2038 Reductant Inj Air Press Sensor Circ Range/Perf
	//P2039 Reductant Inj Air Press Sensor Circ Low Input
	//P2040 Reductant Inj Air Press Sensor Circ High Input
	//P2041 Reductant Inj Air Press Sensor Circ Interm
	//P2042 Reductant Temp Sensor Circ
	//P2043 Reductant Temp Sensor Circ Range/Perf
	//P2044 Reductant Temp Sensor Circ Low Input
	//P2045 Reductant Temp Sensor Circ High Input
	//P2046 Reductant Temp Sensor Circ Interm
	//P2047 Reductant Injector Circ/Open Bank1 Unit 1
	//P2048 Reductant Injector Circ Low Bank1 Unit 1
	//P2049 Reductant Injector Circ High Bank1 Unit 1
	//P2050 Reductant Injector Circ/Open Bank2 Unit 1
	//P2051 Reductant Injector Circ Low Bank2 Unit 1
	//P2052 Reductant Injector Circ High Bank2 Unit 1
	//P2053 Reductant Injector Circ/Open Bank1 Unit 2
	//P2054 Reductant Injector Circ Low Bank1 Unit 2
	//P2055 Reductant Injector Circ High Bank1 Unit 2
	//P2056 Reductant Injector Circ/Open Bank2 Unit 2
	//P2057 Reductant Injector Circ Low Bank2 Unit 2
	//P2058 Reductant Injector Circ High Bank2 Unit 2
	//P2059 Reductant Inj Air Pump Ctrl Circ/Open
	//P2060 Reductant Inj Air Pump Ctrl Circ Low
	//P2061 Reductant Inj Air Pump Ctrl Circ High
	//P2062 Reductant Supply Ctrl Circ/Open
	//P2063 Reductant Supply Ctrl Circ Low
	//P2064 Reductant Supply Ctrl Circ High
	//P2065 Fuel Level SensorB Circ
	//P2066 Fuel Level SensorB Perf
	//P2067 Fuel Level SensorB Circ Low
	//P2068 Fuel Level SensorB Circ High
	//P2069 Fuel Level SensorB Circ Interm
	//P2070 Intake Manifold Tuning (IMT) Valve Stuck Open
	//P2071 IMT Valve Stuck Closed
	//P2072 Throttle Actuator Control System - Ice Blockage
	//P2073 Manifold Absolute Pressure/Mass Air Flow - Throttle Position Correlation at Idle
	//P2074 Manifold Absolute Pressure/Mass Air Flow - Throttle Position Correlation at Higher Load
	//P2075 IMT Valve Pos Sensor/Switch Circ
	//P2076 IMT Valve Pos Sensor/Switch Circ Range/Perf
	//P2077 IMT Valve Pos Sensor/Switch Circ Low
	//P2078 IMT Valve Pos Sensor/Switch Circ High
	//P2079 IMT Valve Pos Sensor/Switch Circ Interm
	//P2080 Exhaust Gas Temp Sensor Circ Range/Perf Bank1 Sensor 1
	//P2081 Exhaust Gas Temp Sensor Circ Interm Bank1 Sensor 1
	//P2082 Exhaust Gas Temp Sensor Circ Range/Perf Bank2 Sensor 1
	//P2083 Exhaust Gas Temp Sensor Circ Interm Bank2 Sensor 1
	//P2084 Exhaust Gas Temp Sensor Circ Range/Perf Bank1 Sensor 2
	//P2085 Exhaust Gas Temp Sensor Circ Interm Bank1 Sensor 2
	//P2086 Exhaust Gas Temp Sensor Circ Range/Perf Bank2 Sensor 2
	//P2087 Exhaust Gas Temp Sensor Circ Interm Bank2 Sensor 2
	//P2088 A Camshaft Pos Actuator Ctrl Circ Low Bank1
	//P2089 A Camshaft Pos Actuator Ctrl Circ High Bank1
	//P2090 B Camshaft Pos Actuator Ctrl Circ Low Bank1
	//P2091 B Camshaft Pos Actuator Ctrl Circ High Bank1
	//P2092 A Camshaft Pos Actuator Ctrl Circ Low Bank2
	//P2093 A Camshaft Pos Actuator Ctrl Circ High Bank2
	//P2094 B Camshaft Pos Actuator Ctrl Circ Low Bank2
	//P2095 B Camshaft Pos Actuator Ctrl Circ High Bank2
	//P2096 Post Catalyst Fuel Trim Sys Too Lean Bank1
	//P2097 Post Catalyst Fuel Trim Sys Too Rich Bank1
	//P2098 Post Catalyst Fuel Trim Sys Too Lean Bank2
	//P2099 Post Catalyst Fuel Trim Sys Too Rich Bank2
	//P2100 Throttle Actuator Ctrl Motor Circ/Open
	//P2101 Throttle Actuator Ctrl Motor Circ Range/Perf
	//P2102 Throttle Actuator Ctrl Motor Circ Low
	//P2103 Throttle Actuator Ctrl Motor Circ High
	//P2104 Throttle Actuator Ctrl Sys-Forced Idle
	//P2105 Throttle Actuator Ctrl Sys-Forced Engine Shutdown
	//P2106 Throttle Actuator Ctrl Sys-Forced Limited Power
	//P2107 Throttle Actuator Ctrl Mod Processor
	//P2108 Throttle Actuator Ctrl Mod Perf
	//P2109 Throttle/Pedal Pos SensorA Minimum Stop Perf
	//P2110 Throttle Actuator Ctrl Sys-Forced Limited RPM
	//P2111 Throttle Actuator Ctrl Sys-Stuck Open
	//P2112 Throttle Actuator Ctrl Sys-Stuck Closed
	//P2113 Throttle/Pedal Pos SensorB Minimum Stop Perf
	//P2114 Throttle/Pedal Pos Sensor C Minimum Stop Perf
	//P2115 Throttle/Pedal Pos Sensor D Minimum Stop Perf
	//P2116 Throttle/Pedal Pos Sensor E Minimum Stop Perf
	//P2117 Throttle/Pedal Pos Sensor F Minimum Stop Perf
	//P2118 Throttle Actuator Ctrl Motor Current Range/Perf
	//P2119 Throttle Actuator Ctrl Throttle Body Range/Perf
	//P2120 Throttle/Pedal Pos Sensor/Switch D Circ
	//P2121 Throttle/Pedal Pos Sensor/Switch D Circ Range/Perf
	//P2122 Throttle/Pedal Pos Sensor/Switch D Circ Low Input
	//P2123 Throttle/Pedal Pos Sensor/Switch D Circ High Input
	//P2124 Throttle/Pedal Pos Sensor/Switch D Circ Interm
	//P2125 Throttle/Pedal Pos Sensor/Switch E Circ
	//P2126 Throttle/Pedal Pos Sensor/Switch E Circ Range/Perf
	//P2127 Throttle/Pedal Pos Sensor/Switch E Circ Low Input
	//P2128 Throttle/Pedal Pos Sensor/Switch E Circ High Input
	//P2129 Throttle/Pedal Pos Sensor/Switch E Circ Interm
	//P2130 Throttle/Pedal Pos Sensor/Switch F Circ
	//P2131 Throttle/Pedal Pos Sensor/Switch F Circ Range Perf
	//P2132 Throttle/Pedal Pos Sensor/Switch F Circ Low Input
	//P2133 Throttle/Pedal Pos Sensor/Switch F Circ High Input
	//P2134 Throttle/Pedal Pos Sensor/Switch F Circ Interm
	//P2135 Throttle/Pedal Pos Sensor/Switch A / B Voltage Correlation
	//P2136 Throttle/Pedal Pos Sensor/Switch A / C Voltage Correlation
	//P2137 Throttle/Pedal Pos Sensor/Switch B / C Voltage Correlation
	//P2138 Throttle/Pedal Pos Sensor/Switch D / E Voltage Correlation
	//P2139 Throttle/Pedal Pos Sensor/Switch D / F Voltage Correlation
	//P2140 Throttle/Pedal Pos Sensor/Switch E / F Voltage Correlation
	//P2141 Exhaust Gas Recirculation Throttle Ctrl Circ Low
	//P2142 Exhaust Gas Recirculation Throttle Ctrl Circ High
	//P2143 Exhaust Gas Recirculation Vent Ctrl Circ/Open
	//P2144 Exhaust Gas Recirculation Vent Ctrl Circ Low
	//P2145 Exhaust Gas Recirculation Vent Ctrl Circ High
	//P2146 Fuel Injector Group A Supply Voltage Circ/Open
	//P2147 Fuel Injector Group A Supply Voltage Circ Low
	//P2148 Fuel Injector Group A Supply Voltage Circ High
	//P2149 Fuel Injector Group B Supply Voltage Circ/Open
	//P2150 Fuel Injector Group B Supply Voltage Circ Low
	//P2151 Fuel Injector Group B Supply Voltage Circ High
	//P2152 Fuel Injector Group C Supply Voltage Circ/Open
	//P2153 Fuel Injector Group C Supply Voltage Circ Low
	//P2154 Fuel Injector Group C Supply Voltage Circ High
	//P2155 Fuel Injector Group D Supply Voltage Circ/Open
	//P2156 Fuel Injector Group D Supply Voltage Circ Low
	//P2157 Fuel Injector Group D Supply Voltage Circ High
	//P2158 Vehicle Speed SensorB
	//P2159 Vehicle Speed SensorB Range/Perf
	//P2160 Vehicle Speed SensorB Circ Low
	//P2161 Vehicle Speed SensorB Interm/Erratic
	//P2162 Vehicle Speed SensorA / B Correlation
	//P2163 Throttle/Pedal Pos SensorA Maximum Stop Perf
	//P2164 Throttle/Pedal Pos SensorB Maximum Stop Perf
	//P2165 Throttle/Pedal Pos Sensor C Maximum Stop Perf
	//P2166 Throttle/Pedal Pos Sensor D Maximum Stop Perf
	//P2167 Throttle/Pedal Pos Sensor E Maximum Stop Perf
	//P2168 Throttle/Pedal Pos Sensor F Maximum Stop Perf
	//P2169 Exhaust Press Reg Vent Solenoid Ctrl Circ/Open
	//P2170 Exhaust Press Reg Vent Solenoid Ctrl Circ Low
	//P2171 Exhaust Press Reg Vent Solenoid Ctrl Circ High
	//P2172 Throttle Actuator Ctrl Sys-Sudden High Airflow Detected
	//P2173 Throttle Actuator Ctrl Sys-High Airflow Detected
	//P2174 Throttle Actuator Ctrl Sys-Sudden Low Airflow Detected
	//P2175 Throttle Actuator Ctrl Sys-Low Airflow Detected
	//P2176 Throttle Actuator Ctrl Sys-Idle Pos Not Learned
	//P2177 Sys Too Lean Off Idle Bank1
	//P2178 Sys Too Rich Off Idle Bank1
	//P2179 Sys Too Lean Off Idle Bank2
	//P2180 Sys Too Rich Off Idle Bank2
	//P2181 Cooling System Performance
	//P2182 Engine Coolant Temp Sensor 2 Circ
	//P2183 Engine Coolant Temp Sensor 2 Circ Range/Perf
	//P2184 Engine Coolant Temp Sensor 2 Circ Low
	//P2185 Engine Coolant Temp Sensor 2 Circ High
	//P2186 Engine Coolant Temp Sensor 2 Circ Interm/Erratic
	//P2187 Sys Too Lean at Idle Bank1
	//P2188 Sys Too Rich at Idle Bank1
	//P2189 Sys Too Lean at Idle Bank2
	//P2190 Sys Too Rich at Idle Bank2
	//P2191 Sys Too Lean at Higher Load Bank1
	//P2192 Sys Too Rich at Higher Load Bank1
	//P2193 Sys Too Lean at Higher Load Bank2
	//P2194 Sys Too Rich at Higher Load Bank2
	//P2195 O2 Sensor Signal Stuck Lean Bank1 Sensor 1
	//P2196 O2 Sensor Signal Stuck Rich Bank1 Sensor 1
	//P2197 O2 Sensor Signal Stuck Lean Bank2 Sensor 1
	//P2198 O2 Sensor Signal Stuck Rich Bank2 Sensor 1
	//P2199 Intake Air Temp Sensor 1 / 2 Correlation
	//P2200 NOx Sensor Circ Bank1
	//P2201 NOx Sensor Circ Range/Perf Bank1
	//P2202 NOx Sensor Circ Low Input Bank1
	//P2203 NOx Sensor Circ High Input Bank1
	//P2204 NOx Sensor Circ Interm Input Bank1
	//P2205 NOx Sensor Heater Ctrl Circ/Open Bank1
	//P2206 NOx Sensor Heater Ctrl Circ Low Bank1
	//P2207 NOx Sensor Heater Ctrl Circ High Bank1
	//P2208 NOx Sensor Heater Sense Circ Bank1
	//P2209 NOx Sensor Heater Sense Circ Range/Perf Bank1
	//P2210 NOx Sensor Heater Sense Circ Low Input Bank1
	//P2211 NOx Sensor Heater Sense Circ High Input Bank1
	//P2212 NOx Sensor Heater Sense Circ Interm Bank1
	//P2213 NOx Sensor Circ Bank2
	//P2214 NOx Sensor Circ Range/Perf Bank2
	//P2215 NOx Sensor Circ Low Input Bank2
	//P2216 NOx Sensor Circ High Input Bank2
	//P2217 NOx Sensor Circ Interm Input Bank2
	//P2218 NOx Sensor Heater Ctrl Circ/Open Bank2
	//P2219 NOx Sensor Heater Ctrl Circ Low Bank2
	//P2220 NOx Sensor Heater Ctrl Circ High Bank2
	//P2221 NOx Sensor Heater Sense Circ Bank2
	//P2222 NOx Sensor Heater Sense Circ Range/Perf Bank2
	//P2223 NOx Sensor Heater Sense Circ Low Bank2
	//P2224 NOx Sensor Heater Sense Circ High Bank2
	//P2225 NOx Sensor Heater Sense Circ Interm Bank2
	//P2226 Barometric Press Circ
	//P2227 Barometric Press Circ Range/Perf
	//P2228 Barometric Press Circ Low
	//P2229 Barometric Press Circ High
	//P2230 Barometric Press Circ Interm
	//P2231 O2 Sensor Signal Circ Shorted to Heater Circ Bank1 Sensor 1
	//P2232 O2 Sensor Signal Circ Shorted to Heater Circ Bank1 Sensor 2
	//P2233 O2 Sensor Signal Circ Shorted to Heater Circ Bank1 Sensor 3
	//P2234 O2 Sensor Signal Circ Shorted to Heater Circ Bank2 Sensor 1
	//P2235 O2 Sensor Signal Circ Shorted to Heater Circ Bank2 Sensor 2
	//P2236 O2 Sensor Signal Circ Shorted to Heater Circ Bank2 Sensor 3
	//P2237 O2 Sensor Positive Current Ctrl Circ/Open Bank1 Sensor 1
	//P2238 O2 Sensor Positive Current Ctrl Circ Low Bank1 Sensor 1
	//P2239 O2 Sensor Positive Current Ctrl Circ High Bank1 Sensor 1
	//P2240 O2 Sensor Positive Current Ctrl Circ/Open Bank2 Sensor 1
	//P2241 O2 Sensor Positive Current Ctrl Circ Low Bank2 Sensor 1
	//P2242 O2 Sensor Positive Current Ctrl Circ High Bank2 Sensor 1
	//P2243 O2 Sensor Ref Voltage Circ/Open Bank1 Sensor 1
	//P2244 O2 Sensor Ref Voltage Perf Bank1 Sensor 1
	//P2245 O2 Sensor Ref Voltage Circ Low Bank1 Sensor 1
	//P2246 O2 Sensor Ref Voltage Circ High Bank1 Sensor 1
	//P2247 O2 Sensor Ref Voltage Circ/Open Bank2 Sensor 1
	//P2248 O2 Sensor Ref Voltage Perf Bank2 Sensor 1
	//P2249 O2 Sensor Ref Voltage Circ Low Bank2 Sensor 1
	//P2250 O2 Sensor Ref Voltage Circ High Bank2 Sensor 1
	//P2251 O2 Sensor Negative Current Ctrl Circ/Open Bank1 Sensor 1
	//P2252 O2 Sensor Negative Current Ctrl Circ Low Bank1 Sensor 1
	//P2253 O2 Sensor Negative Current Ctrl Circ High Bank1 Sensor 1
	//P2254 O2 Sensor Negative Current Ctrl Circ/Open Bank2 Sensor 1
	//P2255 O2 Sensor Negative Current Ctrl Circ Low Bank2 Sensor 1
	//P2256 O2 Sensor Negative Current Ctrl Circ High Bank2 Sensor 1
	//P2257 Sec Air Inj Sys Ctrl A Circ Low
	//P2258 Sec Air Inj Sys Ctrl A Circ High
	//P2259 Sec Air Inj Sys Ctrl B Circ Low
	//P2260 Sec Air Inj Sys Ctrl B Circ High
	//P2261 T/S Charger Bypass Valve-Mechanical
	//P2262 Turbo Boost Press Not Detected-Mechanical
	//P2263 T/S Charger Boost Sys Perf
	//P2264 Water in Fuel Sensor Circ
	//P2265 Water in Fuel Sensor Circ Range/Perf
	//P2266 Water in Fuel Sensor Circ Low
	//P2267 Water in Fuel Sensor Circ High
	//P2268 Water in Fuel Sensor Circ Interm
	//P2269 Water in Fuel Condition
	//P2270 O2 Sensor Signal Stuck Lean Bank1 Sensor 2
	//P2271 O2 Sensor Signal Stuck Rich Bank1 Sensor 2
	//P2272 O2 Sensor Signal Stuck Lean Bank2 Sensor 2
	//P2273 O2 Sensor Signal Stuck Rich Bank2 Sensor 2
	//P2274 O2 Sensor Signal Stuck Lean Bank1 Sensor 3
	//P2275 O2 Sensor Signal Stuck Rich Bank1 Sensor 3
	//P2276 O2 Sensor Signal Stuck Lean Bank2 Sensor 3
	//P2277 O2 Sensor Signal Stuck Rich Bank2 Sensor 3
	//P2278 O2 Sensor Signals Swapped Bank1 Sensor 3 / Bank2 Sensor 3
	//P2279 Intake Air Sys Leak
	//P2280 Air Flow Restriction / Air Leak Between Air Filter and MAF
	//P2281 Air Leak Between MAF and Throttle Body
	//P2282 Air Leak Between Throttle Body and Intake Valves
	//P2283 Injector Ctrl Press Sensor Circ
	//P2284 Injector Ctrl Press Sensor Circ Range/Perf
	//P2285 Injector Ctrl Press Sensor Circ Low
	//P2286 Injector Ctrl Press Sensor Circ High
	//P2287 Injector Ctrl Press Sensor Circ Interm
	//P2288 Injector Ctrl Press Too High
	//P2289 Injector Ctrl Press Too High-Engine Off
	//P2290 Injector Ctrl Press Too Low
	//P2291 Injector Ctrl Press Too Low-Engine Cranking
	//P2292 Injector Ctrl Press Erratic
	//P2293 Fuel Press Reg 2 Perf
	//P2294 Fuel Press Reg 2 Ctrl Circ
	//P2295 Fuel Press Reg 2 Ctrl Circ Low
	//P2296 Fuel Press Reg 2 Ctrl Circ High
	//P2297 O2 Sensor Out of Range During Deceleration Bank1 Sensor 1
	//P2298 O2 Sensor Out of Range During Deceleration Bank2 Sensor 1
	//P2299 Brake Pedal Pos / Accelerator Pedal Pos Incompatible
	//P2300 Ignition Coil A Pri Ctrl Circ Low
	//P2301 Ignition Coil A Pri Ctrl Circ High
	//P2302 Ignition Coil A Sec Circ
	//P2303 Ignition Coil B Pri Ctrl Circ Low
	//P2304 Ignition Coil B Pri Ctrl Circ High
	//P2305 Ignition Coil B Sec Circ
	//P2306 Ignition Coil C Pri Ctrl Circ Low
	//P2307 Ignition Coil C Pri Ctrl Circ High
	//P2308 Ignition Coil C Sec Circ
	//P2309 Ignition Coil D Pri Ctrl Circ Low
	//P2310 Ignition Coil D Pri Ctrl Circ High
	//P2311 Ignition Coil D Sec Circ
	//P2312 Ignition Coil E Pri Ctrl Circ Low
	//P2313 Ignition Coil E Pri Ctrl Circ High
	//P2314 Ignition Coil E Sec Circ
	//P2315 Ignition Coil F Pri Ctrl Circ Low
	//P2316 Ignition Coil F Pri Ctrl Circ High
	//P2317 Ignition Coil F Sec Circ
	//P2318 Ignition Coil G Pri Ctrl Circ Low
	//P2319 Ignition Coil G Pri Ctrl Circ High
	//P2320 Ignition Coil G Sec Circ
	//P2321 Ignition Coil H Pri Ctrl Circ Low
	//P2322 Ignition Coil H Pri Ctrl Circ High
	//P2323 Ignition Coil H Sec Circ
	//P2324 Ignition Coil I Pri Ctrl Circ Low
	//P2325 Ignition Coil I Pri Ctrl Circ High
	//P2326 Ignition Coil I Sec Circ
	//P2327 Ignition Coil J Pri Ctrl Circ Low
	//P2328 Ignition Coil J Pri Ctrl Circ High
	//P2329 Ignition Coil J Sec Circ
	//P2330 Ignition Coil K Pri Ctrl Circ Low
	//P2331 Ignition Coil K Pri Ctrl Circ High
	//P2332 Ignition Coil K Sec Circ
	//P2333 Ignition Coil L Pri Ctrl Circ Low
	//P2334 Ignition Coil L Pri Ctrl Circ High
	//P2335 Ignition Coil L Sec Circ
	//P2336 Cylinder #1 Above Knock Threshold
	//P2337 Cylinder #2 Above Knock Threshold
	//P2338 Cylinder #3 Above Knock Threshold
	//P2339 Cylinder #4 Above Knock Threshold
	//P2340 Cylinder #5 Above Knock Threshold
	//P2341 Cylinder #6 Above Knock Threshold
	//P2342 Cylinder #7 Above Knock Threshold
	//P2343 Cylinder #8 Above Knock Threshold
	//P2344 Cylinder #9 Above Knock Threshold
	//P2345 Cylinder #10 Above Knock Threshold
	//P2346 Cylinder #11 Above Knock Threshold
	//P2347 Cylinder #12 Above Knock Threshold
	//P2400 EVAP Leak Detection Pump Ctrl Circ/Open
	//P2401 EVAP Leak Detection Pump Ctrl Circ Low
	//P2402 EVAP Leak Detection Pump Ctrl Circ High
	//P2403 EVAP Leak Detection Pump Sense Circ/Open
	//P2404 EVAP Leak Detection Pump Sense Circ Range/Perf
	//P2405 EVAP Leak Detection Pump Sense Circ Low
	//P2406 EVAP Leak Detection Pump Sense Circ High
	//P2407 EVAP Leak Detection Pump Sense Circ Interm/Erratic
	//P2408 Fuel Cap Sensor/Switch Circ
	//P2409 Fuel Cap Sensor/Switch Circ Range/Perf
	//P2410 Fuel Cap Sensor/Switch Circ Low
	//P2411 Fuel Cap Sensor/Switch Circ High
	//P2412 Fuel Cap Sensor/Switch Circ Interm/Erratic
	//P2413 Exhaust Gas Recirculation Sys Perf
	//P2414 O2 Sensor Exhaust Sample Error Bank1 Sensor 1
	//P2415 O2 Sensor Exhaust Sample Error Bank2 Sensor 1
	//P2416 O2 Sensor Signals Swapped Bank1 Sensor 2 / Bank1 Sensor 3
	//P2417 O2 Sensor Signals Swapped Bank2 Sensor 2 / Bank2 Sensor 3
	//P2418 EVAP Switching Valve Ctrl Circ /Open
	//P2419 EVAP Switching Valve Ctrl Circ Low
	//P2420 EVAP Switching Valve Ctrl Circ High
	//P2421 EVAP Vent Valve Stuck Open
	//P2422 EVAP Vent Valve Stuck Closed
	//P2423 HC Adsorption Catalyst Efficiency Below Threshold Bank1
	//P2424 HC Adsorption Catalyst Efficiency Below Threshold Bank2
	//P2425 Exhaust Gas Recirculation Cooling Valve Ctrl Circ/Open
	//P2426 Exhaust Gas Recirculation Cooling Valve Ctrl Circ Low
	//P2427 Exhaust Gas Recirculation Cooling Valve Ctrl Circ High
	//P2428 Exhaust Gas Temp Too High Bank1
	//P2429 Exhaust Gas Temp Too High Bank2
	//P2430 Sec Air Inj Sys Air Flow/Press Sensor Circ Bank1
	//P2431 Sec Air Inj Sys Air Flow/Press Sensor Circ Range/Perf Bank1
	//P2432 Sec Air Inj Sys Air Flow/Press Sensor Circ Low Bank1
	//P2433 Sec Air Inj Sys Air Flow/Press Sensor Circ High Bank1
	//P2434 Sec Air Inj Sys Air Flow/Press Sensor Circ Interm/Erratic Bank1
	//P2435 Sec Air Inj Sys Air Flow/Press Sensor Circ Bank2
	//P2436 Sec Air Inj Sys Air Flow/Press Sensor Circ Range/Perf Bank2
	//P2437 Sec Air Inj Sys Air Flow/Press Sensor Circ Low Bank2
	//P2438 Sec Air Inj Sys Air Flow/Press Sensor Circ High Bank2
	//P2439 Sec Air Inj Sys Air Flow/Press Sensor Circ Interm/Eratic Bank2
	//P2440 Sec Air Inj Sys Switching Valve Stuck Open Bank1
	//P2441 Sec Air Inj Sys Switching Valve Stuck Closed Bank1
	//P2442 Sec Air Inj Sys Switching Valve Stuck Open Bank2
	//P2443 Sec Air Inj Sys Switching Valve Stuck Closed Bank2
	//P2444 Sec Air Inj Sys Pump Stuck On Bank1
	//P2445 Sec Air Inj Sys Pump Stuck Off Bank1
	//P2446 Sec Air Inj Sys Pump Stuck On Bank2
	//P2447 Sec Air Inj Sys Pump Stuck Off Bank2
	//P2453 Particulate Matter Trap Differential Pressure Sensor Signal Performance
	//P2455 DPF Differential Pressure Sensor Short to Voltage
	//P2500 Generator Lamp/L-Terminal Circ Low
	//P2501 Generator Lamp/L-Terminal Circ High
	//P2502 Charging Sys Voltage
	//P2503 Charging Sys Voltage Low
	//P2504 Charging Sys Voltage High
	//P2505 ECM/PCM Power Input Signal
	//P2506 ECM/PCM Power Input Signal Range/Perf
	//P2507 ECM/PCM Power Input Signal Low
	//P2508 ECM/PCM Power Input Signal High
	//P2509 ECM/PCM Power Input Signal Interm
	//P2510 ECM/PCM Power Relay Sense Circ Range/Perf
	//P2511 ECM/PCM Power Relay Sense Circ Interm
	//P2512 Event Data Recorder Request Circ/ Open
	//P2513 Event Data Recorder Request Circ Low
	//P2514 Event Data Recorder Request Circ High
	//P2515 A/C Refrigerant Press SensorB Circ
	//P2516 A/C Refrigerant Press SensorB Circ Range/Perf
	//P2517 A/C Refrigerant Press SensorB Circ Low
	//P2518 A/C Refrigerant Press SensorB Circ High
	//P2519 A/C Request A Circ
	//P2520 A/C Request A Circ Low
	//P2521 A/C Request A Circ High
	//P2522 A/C Request B Circ
	//P2523 A/C Request B Circ Low
	//P2524 A/C Request B Circ High
	//P2525 Vacuum Reservoir Press Sensor Circ
	//P2526 Vacuum Reservoir Press Sensor Circ Range/Perf
	//P2527 Vacuum Reservoir Press Sensor Circ Low
	//P2528 Vacuum Reservoir Press Sensor Circ High
	//P2529 Vacuum Reservoir Press Sensor Circ Interm
	//P2530 Ignition Switch Run Pos Circ
	//P2531 Ignition Switch Run Pos Circ Low
	//P2532 Ignition Switch Run Pos Circ High
	//P2533 Ignition Switch Run/Start Pos Circ
	//P2534 Ignition Switch Run/Start Pos Circ Low
	//P2535 Ignition Switch Run/Start Pos Circ High
	//P2536 Ignition Switch Accessory Pos Circ
	//P2537 Ignition Switch Accessory Pos Circ Low
	//P2538 Ignition Switch Accessory Pos Circ High
	//P2539 Low Press Fuel Sys Sensor Circ
	//P2540 Low Press Fuel Sys Sensor Circ Range/Perf
	//P2541 Low Press Fuel Sys Sensor Circ Low
	//P2542 Low Press Fuel Sys Sensor Circ High
	//P2543 Low Press Fuel Sys Sensor Circ Interm
	//P2544 Torque Mgmt Request Input Signal A
	//P2545 Torque Mgmt Request Input Signal A Range/Perf
	//P2546 Torque Mgmt Request Input Signal A Low
	//P2547 Torque Mgmt Request Input Signal A High
	//P2548 Torque Mgmt Request Input Signal B
	//P2549 Torque Mgmt Request Input Signal B Range/Perf
	//P2550 Torque Mgmt Request Input Signal B Low
	//P2551 Torque Mgmt Request Input Signal B High
	//P2552 Throttle/Fuel Inhibit Circ
	//P2553 Throttle/Fuel Inhibit Circ Range/Perf
	//P2554 Throttle/Fuel Inhibit Circ Low
	//P2555 Throttle/Fuel Inhibit Circ High
	//P2556 Engine Coolant Level Sensor/Switch Circ
	//P2557 Engine Coolant Level Sensor/Switch Circ Range/Perf
	//P2558 Engine Coolant Level Sensor/Switch Circ Low
	//P2559 Engine Coolant Level Sensor/Switch Circ High
	//P2560 Engine Coolant Level Low
	//P2561 A/C Ctrl Mod Requested MIL Illumination
	//P2562 Turbocharger Boost Ctrl Pos Sensor Circ
	//P2563 Turbocharger Boost Ctrl Pos Sensor Circ Range/Perf
	//P2564 Turbocharger Boost Ctrl Pos Sensor Circ Low
	//P2565 Turbocharger Boost Ctrl Pos Sensor Circ High
	//P2566 Turbocharger Boost Ctrl Pos Sensor Circ Interm
	//P2567 Direct Ozone Reduction Catalyst Temp Sensor Circ
	//P2568 Direct Ozone Reduction Catalyst Temp Sensor Circ Range/Perf
	//P2569 Direct Ozone Reduction Catalyst Temp Sensor Circ Low
	//P2570 Direct Ozone Reduction Catalyst Temp Sensor Circ High
	//P2571 Direct Ozone Reduction Catalyst Temp Sensor Circ Interm/Erratic4
	//P2572 Direct Ozone Reduction Catalyst Deterioration Sensor Circ4
	//P2573 Direct Ozone Reduction Catalyst Deterioration Sensor Circ Range/Perf4
	//P2574 Direct Ozone Reduction Catalyst Deterioration Sensor Circ Low4
	//P2575 Direct Ozone Reduction Catalyst Deterioration Sensor Circ High4
	//P2576 Direct Ozone Reduction Catalyst Deterioration Sensor Circ Interm/Erratic
	//P2577 Direct Ozone Reduction Catalyst Efficiency Below Threshold
	//P2600 Coolant Pump Ctrl Circ/Open
	//P2601 Coolant Pump Ctrl Circ Range/Perf
	//P2602 Coolant Pump Ctrl Circ Low
	//P2603 Coolant Pump Ctrl Circ High
	//P2604 Intake Air Heater A Circ Range/Perf
	//P2605 Intake Air Heater A Circ/Open
	//P2606 Intake Air Heater B Circ Range/Perf
	//P2607 Intake Air Heater B Circ Low
	//P2608 Intake Air Heater B Circ High
	//P2609 Intake Air Heater Sys Perf
	//P2610 ECM/PCM Internal Engine Off Timer Perf
	//P2611 A/C Refrigerant Distribution Valve Ctrl Circ/Open
	//P2612 A/C Refrigerant Distribution Valve Ctrl Circ Low
	//P2613 A/C Refrigerant Distribution Valve Ctrl Circ High
	//P2614 Camshaft Pos Signal Output Circ/Open
	//P2615 Camshaft Pos Signal Output Circ Low
	//P2616 Camshaft Pos Signal Output Circ High
	//P2617 Crank Pos Signal Output Circ/Open
	//P2618 Crank Pos Signal Output Circ Low
	//P2619 Crank Pos Signal Output Circ High
	//P2620 Throttle Pos Output Circ/Open
	//P2621 Throttle Pos Output Circ Low
	//P2622 Throttle Pos Output Circ High
	//P2623 Injector Ctrl Press Reg Circ/Open
	//P2624 Injector Ctrl Press Reg Circ Low
	//P2625 Injector Ctrl Press Reg Circ High
	//P2626 O2 Sensor Pumping Current Trim Circ/Open Bank1 Sensor 1
	//P2627 O2 Sensor Pumping Current Trim Circ Low Bank1 Sensor 1
	//P2628 O2 Sensor Pumping Current Trim Circ High Bank1 Sensor 1
	//P2629 O2 Sensor Pumping Current Trim Circ/Open Bank2 Sensor 1
	//P2630 O2 Sensor Pumping Current Trim Circ Low Bank2 Sensor 1
	//P2631 O2 Sensor Pumping Current Trim Circ High Bank2 Sensor 1
	//P2632 Fuel Pump B Ctrl Circ /Open
	//P2633 Fuel Pump B Ctrl Circ Low
	//P2634 Fuel Pump B Ctrl Circ High
	//P2635 Fuel Pump A Low Flow / Perf
	//P2636 Fuel Pump B Low Flow / Perf
	//P2637 Torque Mgmt Feedback Signal A
	//P2638 Torque Mgmt Feedback Signal A Range/Perf
	//P2639 Torque Mgmt Feedback Signal A Low
	//P2640 Torque Mgmt Feedback Signal A High
	//P2641 Torque Mgmt Feedback Signal B
	//P2642 Torque Mgmt Feedback Signal B Range/Perf
	//P2643 Torque Mgmt Feedback Signal B Low
	//P2644 Torque Mgmt Feedback Signal B High
	//P2645 A Rocker Arm Actuator Ctrl Circ/Open Bank1
	//P2646 A Rocker Arm Actuator Sys Perf or Stuck Off Bank1
	//P2647 A Rocker Arm Actuator Sys Stuck On Bank1
	//P2648 A Rocker Arm Actuator Ctrl Circ Low Bank1
	//P2649 A Rocker Arm Actuator Ctrl Circ High Bank1
	//P2650 B Rocker Arm Actuator Ctrl Circ/Open Bank1
	//P2651 B Rocker Arm Actuator Sys Perf or Stuck Off Bank1
	//P2652 B Rocker Arm Actuator Sys Stuck On Bank1
	//P2653 B Rocker Arm Actuator Ctrl Circ Low Bank1
	//P2654 B Rocker Arm Actuator Ctrl Circ High Bank1
	//P2655 A Rocker Arm Actuator Ctrl Circ/Open Bank2
	//P2656 A Rocker Arm Actuator Sys Perf or Stuck Off Bank2
	//P2657 A Rocker Arm Actuator Sys Stuck On Bank2
	//P2658 A Rocker Arm Actuator Ctrl Circ Low Bank2
	//P2659 A Rocker Arm Actuator Ctrl Circ High Bank2
	//P2660 B Rocker Arm Actuator Ctrl Circ/Open Bank2
	//P2661 B Rocker Arm Actuator Sys Perf or Stuck Off Bank2
	//P2662 B Rocker Arm Actuator Sys Stuck On Bank2
	//P2663 B Rocker Arm Actuator Ctrl Circ Low Bank2
	//P2664 B Rocker Arm Actuator Ctrl Circ High Bank2
	//P2665 Fuel Shutoff Valve B Ctrl Circ/Open
	//P2666 Fuel Shutoff Valve B Ctrl Circ Low
	//P2667 Fuel Shutoff Valve B Ctrl Circ High
	//P2668 Fuel Mode Indicator Lamp Ctrl Circ
	//P2669 Actuator Supply Voltage B Circ /Open



	//P2670 Actuator Supply Voltage B Circ Low
	//P2671 Actuator Supply Voltage B Circ High
	//P2700 Trans Friction Element A Apply Time Range/Perf
	//P2701 Trans Friction Element B Apply Time Range/Perf
	//P2702 Trans Friction Element C Apply Time Range/Perf
	//P2703 Trans Friction Element D Apply Time Range/Perf
	//P2704 Trans Friction Element E Apply Time Range/Perf
	//P2705 Trans Friction Element F Apply Time Range/Perf
	//P2706 Shift Solenoid F
	//P2707 Shift Solenoid F Perf or Stuck Off
	//P2708 Shift Solenoid F Stuck On
	//P2709 Shift Solenoid F Electrical
	//P2710 Shift Solenoid F Interm
	//P2711 Unexpected Mechanical Gear Disengagement
	//P2712 Hydraulic Power Unit Leakage
	//P2713 Press Ctrl Solenoid D
	//P2714 Press Ctrl Solenoid D Perf or Stuck Off
	//P2715 Press Ctrl Solenoid D Stuck On
	//P2716 Press Ctrl Solenoid D Electrical
	//P2717 Press Ctrl Solenoid D Interm
	//P2718 Press Ctrl Solenoid D Ctrl Circ / Open
	//P2719 Press Ctrl Solenoid D Ctrl Circ Range/Perf
	//P2720 Press Ctrl Solenoid D Ctrl Circ Low
	//P2721 Press Ctrl Solenoid D Ctrl Circ High
	//P2722 Press Ctrl Solenoid E
	//P2723 Press Ctrl Solenoid E Perf or Stuck Off
	//P2724 Press Ctrl Solenoid E Stuck On
	//P2725 Press Ctrl Solenoid E Electrical
	//P2726 Press Ctrl Solenoid E Interm
	//P2727 Press Ctrl Solenoid E Ctrl Circ / Open
	//P2728 Press Ctrl Solenoid E Ctrl Circ Range/Perf
	//P2729 Press Ctrl Solenoid E Ctrl Circ Low
	//P2730 Press Ctrl Solenoid E Ctrl Circ High
	//P2731 Press Ctrl Solenoid F
	//P2732 Press Ctrl Solenoid F Perf or Stuck Off
	//P2733 Press Ctrl Solenoid F Stuck On
	//P2734 Press Ctrl Solenoid F Electrical
	//P2735 Press Ctrl Solenoid F Interm
	//P2736 Press Ctrl Solenoid F Ctrl Circ/Open
	//P2737 Press Ctrl Solenoid F Ctrl Circ Range/Perf
	//P2738 Press Ctrl Solenoid F Ctrl Circ Low
	//P2739 Press Ctrl Solenoid F Ctrl Circ High
	//P2740 Trans Fluid Temp SensorB Circ
	//P2741 Trans Fluid Temp SensorB Circ Range Perf
	//P2742 Trans Fluid Temp SensorB Circ Low
	//P2743 Trans Fluid Temp SensorB Circ High
	//P2744 Trans Fluid Temp SensorB Circ Interm
	//P2745 Intermediate Shaft Speed SensorB Circ
	//P2746 Intermediate Shaft Speed SensorB Circ Range/Perf
	//P2747 Intermediate Shaft Speed SensorB Circ No Signal
	//P2748 Intermediate Shaft Speed SensorB Circ Interm
	//P2749 Intermediate Shaft Speed Sensor C Circ
	//P2750 Intermediate Shaft Speed Sensor C Circ Range/Perf
	//P2751 Intermediate Shaft Speed Sensor C Circ No Signal
	//P2752 Intermediate Shaft Speed Sensor C Circ Interm
	//P2753 Trans Fluid Cooler Ctrl Circ/Open
	//P2754 Trans Fluid Cooler Ctrl Circ Low
	//P2755 Trans Fluid Cooler Ctrl Circ High
	//P2756 Torq Conv Clutch Press Ctrl Solenoid
	//P2757 Torq Conv Clutch Press Ctrl Solenoid Ctrl Circ Perf or Stuck Off
	//P2758 Torq Conv Clutch Press Ctrl Solenoid Ctrl Circ Stuck On
	//P2759 Torq Conv Clutch Press Ctrl Solenoid Ctrl Circ Electrical
	//P2760 Torq Conv Clutch Press Ctrl Solenoid Ctrl Circ Interm
	//P2761 Torq Conv Clutch Press Ctrl Solenoid Ctrl Circ/Open
	//P2762 Torq Conv Clutch Press Ctrl Solenoid Ctrl Circ Range/Perf
	//P2763 Torq Conv Clutch Press Ctrl Solenoid Ctrl Circ High
	//P2764 Torq Conv Clutch Press Ctrl Solenoid Ctrl Circ Low
	//P2765 Input/Turbine Speed SensorB Circ
	//P2766 Input/Turbine Speed SensorB Circ Range/Perf
	//P2767 Input/Turbine Speed SensorB Circ No Signal
	//P2768 Input/Turbine Speed SensorB Circ Interm
	//P2769 Torq Conv Clutch Circ Low
	//P2770 Torq Conv Clutch Circ High
	//P2771 4WD Low Switch Circ
	//P2772 4WD Low Switch Circ Range/Perf
	//P2773 4WD Low Switch Circ Low
	//P2774 4WD Low Switch Circ High
	//P2775 Upshift Switch Circ Range/Perf
	//P2776 Upshift Switch Circ Low
	//P2777 Upshift Switch Circ High
	//P2778 Upshift Switch Circ Interm/Erratic
	//P2779 Downshift Switch Circ Range/Perf
	//P2780 Downshift Switch Circ Low
	//P2781 Downshift Switch Circ High
	//P2782 Downshift Switch Circ Interm/Erratic
	//P2783 Torq Conv Temp Too High
	//P2784 Input/Turbine Speed SensorA/B Correlation
	//P2785 Clutch Actuator Temp Too High
	//P2786 Gear Shift Actuator Temp Too High
	//P2787 Clutch Temp Too High
	//P2788 Auto Shift Manual Adaptive Learning at Limit
	//P2789 Clutch Adaptive Learning at Limit
	//P2790 Gate Select Direction Circ
	//P2791 Gate Select Direction Circ Low
	//P2792 Gate Select Direction Circ High
	//P2793 Gear Shift Direction Circ
	//P2794 Gear Shift Direction Circ Low
	//P2795 Gear Shift Direction Circ High
	//P2A00 O2 Sensor Circ Range/Perf Bank1 Sensor 1
	//P2A01 O2 Sensor Circ Range/Perf Bank1 Sensor 2
	//P2A02 O2 Sensor Circ Range/Perf Bank1 Sensor 3
	//P2A03 O2 Sensor Circ Range/Perf Bank2 Sensor 1
	//P2A04 O2 Sensor Circ Range/Perf Bank2 Sensor 2
	//P2A05 O2 Sensor Circ Range/Perf Bank2 Sensor 3
	//P3xxx Generic Powertrain Diagnostic Codes DTC
	//P3400 Cylinder Deactivation Sys Bank1
	//P3401 Cyl1 Deactivation/Intake Valve Ctrl Circ/Open
	//P3402 Cyl1 Deactivation/Intake Valve Ctrl Perf
	//P3403 Cyl1 Deactivation/Intake Valve Ctrl Circ Low
	//P3404 Cyl1 Deactivation/Intake Valve Ctrl Circ High
	//P3405 Cyl1 Exhaust Valve Ctrl Circ/Open
	//P3406 Cyl1 Exhaust Valve Ctrl Perf
	//P3407 Cyl1 Exhaust Valve Ctrl Circ Low
	//P3408 Cyl1 Exhaust Valve Ctrl Circ High
	//P3409 Cyl2 Deactivation/Intake Valve Ctrl Circ/Open
	//P3410 Cyl2 Deactivation/Intake Valve Ctrl Perf
	//P3411 Cyl2 Deactivation/Intake Valve Ctrl Circ Low
	//P3412 Cyl2 Deactivation/Intake Valve Ctrl Circ High
	//P3413 Cyl2 Exhaust Valve Ctrl Circ/Open
	//P3414 Cyl2 Exhaust Valve Ctrl Perf
	//P3415 Cyl2 Exhaust Valve Ctrl Circ Low
	//P3416 Cyl2 Exhaust Valve Ctrl Circ High
	//P3417 Cyl3 Deactivation/Intake Valve Ctrl Circ/Open
	//P3418 Cyl3 Deactivation/Intake Valve Ctrl Perf
	//P3419 Cyl3 Deactivation/Intake Valve Ctrl Circ Low
	//P3420 Cyl3 Deactivation/Intake Valve Ctrl Circ High
	//P3421 Cyl3 Exhaust Valve Ctrl Circ/Open
	//P3422 Cyl3 Exhaust Valve Ctrl Perf
	//P3423 Cyl3 Exhaust Valve Ctrl Circ Low
	//P3424 Cyl3 Exhaust Valve Ctrl Circ High
	//P3425 Cyl4 Deactivation/Intake Valve Ctrl Circ/Open
	//P3426 Cyl4 Deactivation/Intake Valve Ctrl Perf
	//P3427 Cyl4 Deactivation/Intake Valve Ctrl Circ Low
	//P3428 Cyl4 Deactivation/Intake Valve Ctrl Circ High
	//P3429 Cyl4 Exhaust Valve Ctrl Circ/Open
	//P3430 Cyl4 Exhaust Valve Ctrl Perf
	//P3431 Cyl4 Exhaust Valve Ctrl Circ Low
	//P3432 Cyl4 Exhaust Valve Ctrl Circ High
	//P3433 Cyl5 Deactivation/Intake Valve Ctrl Circ/Open
	//P3434 Cyl5 Deactivation/Intake Valve Ctrl Perf
	//P3435 Cyl5 Deactivation/Intake Valve Ctrl Circ Low
	//P3436 Cyl5 Deactivation/Intake Valve Ctrl Circ High
	//P3437 Cyl5 Exhaust Valve Ctrl Circ/Open
	//P3438 Cyl5 Exhaust Valve Ctrl Perf
	//P3439 Cyl5 Exhaust Valve Ctrl Circ Low
	//P3440 Cyl5 Exhaust Valve Ctrl Circ High
	//P3441 Cyl6 Deactivation/Intake Valve Ctrl Circ/Open
	//P3442 Cyl6 Deactivation/Intake Valve Ctrl Perf
	//P3443 Cyl6 Deactivation/Intake Valve Ctrl Circ Low
	//P3444 Cyl6 Deactivation/Intake Valve Ctrl Circ High
	//P3445 Cyl6 Exhaust Valve Ctrl Circ/Open
	//P3446 Cyl6 Exhaust Valve Ctrl Perf
	//P3447 Cyl6 Exhaust Valve Ctrl Circ Low
	//P3448 Cyl6 Exhaust Valve Ctrl Circ High
	//P3449 Cyl7 Deactivation/Intake Valve Ctrl Circ/Open
	//P3450 Cyl7 Deactivation/Intake Valve Ctrl Perf
	//P3451 Cyl7 Deactivation/Intake Valve Ctrl Circ Low
	//P3452 Cyl7 Deactivation/Intake Valve Ctrl Circ High
	//P3453 Cyl7 Exhaust Valve Ctrl Circ/Open
	//P3454 Cyl7 Exhaust Valve Ctrl Perf
	//P3455 Cyl7 Exhaust Valve Ctrl Circ Low
	//P3456 Cyl7 Exhaust Valve Ctrl Circ High
	//P3457 Cyl8 Deactivation/Intake Valve Ctrl Circ/Open
	//P3458 Cyl8 Deactivation/Intake Valve Ctrl Perf
	//P3459 Cyl8 Deactivation/Intake Valve Ctrl Circ Low
	//P3460 Cyl8 Deactivation/Intake Valve Ctrl Circ High
	//P3461 Cyl8 Exhaust Valve Ctrl Circ/Open
	//P3462 Cyl8 Exhaust Valve Ctrl Perf
	//P3463 Cyl8 Exhaust Valve Ctrl Circ Low
	//P3464 Cyl8 Exhaust Valve Ctrl Circ High
	//P3465 Cyl9 Deactivation/Intake Valve Ctrl Circ/Open
	//P3466 Cyl9 Deactivation/Intake Valve Ctrl Perf
	//P3467 Cyl9 Deactivation/Intake Valve Ctrl Circ Low
	//P3468 Cyl9 Deactivation/Intake Valve Ctrl Circ High
	//P3469 Cyl9 Exhaust Valve Ctrl Circ/Open
	//P3470 Cyl9 Exhaust Valve Ctrl Perf
	//P3471 Cyl9 Exhaust Valve Ctrl Circ Low
	//P3472 Cyl9 Exhaust Valve Ctrl Circ High
	//P3473 Cyl10 Deactivation/Intake Valve Ctrl Circ/Open
	//P3474 Cyl10 Deactivation/Intake Valve Ctrl Perf
	//P3475 Cyl10 Deactivation/Intake Valve Ctrl Circ Low
	//P3476 Cyl10 Deactivation/Intake Valve Ctrl Circ High
	//P3477 Cyl10 Exhaust Valve Ctrl Circ/Open
	//P3478 Cyl10 Exhaust Valve Ctrl Perf
	//P3479 Cyl10 Exhaust Valve Ctrl Circ Low
	//P3480 Cyl10 Exhaust Valve Ctrl Circ High
	//P3481 Cyl11 Deactivation/Intake Valve Ctrl Circ/Open
	//P3482 Cyl11 Deactivation/Intake Valve Ctrl Perf
	//P3483 Cyl11 Deactivation/Intake Valve Ctrl Circ Low
	//P3484 Cyl11 Deactivation/Intake Valve Ctrl Circ High
	//P3485 Cyl11 Exhaust Valve Ctrl Circ/Open
	//P3486 Cyl11 Exhaust Valve Ctrl Perf
	//P3487 Cyl11 Exhaust Valve Ctrl Circ Low
	//P3488 Cyl11 Exhaust Valve Ctrl Circ High
	//P3489 Cyl12 Deactivation/Intake Valve Ctrl Circ/Open
	//P3490 Cyl12 Deactivation/Intake Valve Ctrl Perf
	//P3491 Cyl12 Deactivation/Intake Valve Ctrl Circ Low
	//P3492 Cyl12 Deactivation/Intake Valve Ctrl Circ High
	//P3493 Cyl12 Exhaust Valve Ctrl Circ/Open

	// this is needed for proper enum size, this matters for malfunction_central
	Internal_ForceMyEnumIntSize_cranking_obd_code = ENUM_32_BITS,
} obd_code_e;

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* OBD_ERROR_CODES_H_ */