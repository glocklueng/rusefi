/**
 * @file    ford_aspire.c
 * @brief	1996 Ford Aspire default engine configuraion
 *
 *  Created on: Sep 9, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include <string.h>

#if EFI_ENGINE_FORD_ASPIRE

#include "ford_aspire.h"

#include "sensors.h"
#include "engines.h"
#include "engine_math.h"
#include "settings.h"
#include "rpm_calculator.h"
#include "fuel_map.h"
#include "engine_controller.h"
#include "engine_configuration.h"

extern EngineConfiguration2 engineConfiguration2;
extern EngineConfiguration *engineConfiguration;

float fuel_rpm_bins[] = {/*0*/400.0, /*1*/650.0, /*2*/900.0, /*3*/1150.0, /*4*/1400.0, /*5*/1650.0, /*6*/1900.0, /*7*/
2150.0, /*8*/2400.0, /*9*/2650.0, /*10*/2900.0, /*11*/3150.0, /*12*/3400.0, /*13*/3650.0, /*14*/3900.0, /*15*/
4150.0, /*16*/4400.0, /*17*/4650.0, /*18*/4900.0, /*19*/5150.0, /*20*/5400.0, /*21*/5650.0, /*22*/5900.0 };

float fuel_maf_bins[] = {/*0*/1.2000000476837158, /*1*/1.300000047683716, /*2*/1.400000047683716, /*3*/
1.500000047683716, /*4*/1.6000000476837162, /*5*/1.7000000476837163, /*6*/1.8000000476837164, /*7*/
1.9000000476837164, /*8*/2.0000000476837165, /*9*/2.1000000476837166, /*10*/2.2000000476837167, /*11*/
2.300000047683717, /*12*/2.400000047683717, /*13*/2.500000047683717, /*14*/2.600000047683717, /*15*/
2.700000047683717, /*16*/2.8000000476837172, /*17*/2.9000000476837173, /*18*/3.0000000476837174, /*19*/
3.1000000476837175, /*20*/3.2000000476837176, /*21*/3.3000000476837177, /*22*/3.4000000476837178, /*23*/
3.500000047683718, /*24*/3.600000047683718, /*25*/3.700000047683718, /*26*/3.800000047683718, /*27*/
3.900000047683718, /*28*/4.000000047683718, /*29*/4.100000047683718, /*30*/4.200000047683718, /*31*/
4.300000047683717, /*32*/4.400000047683717 };

float fuel_table[FUEL_RPM_COUNT][FUEL_MAF_COUNT] = { {/*0 rpm=400.0*//*0 1.2000000476837158*/1.55, /*1 1.300000047683716*/
1.55, /*2 1.400000047683716*/1.52, /*3 1.500000047683716*/1.54, /*4 1.6000000476837162*/1.58, /*5 1.7000000476837163*/
1.52, /*6 1.8000000476837164*/1.53, /*7 1.9000000476837164*/4.03, /*8 2.0000000476837165*/6.55, /*9 2.1000000476837166*/
8.13, /*10 2.2000000476837167*/13.69, /*11 2.300000047683717*/16.14, /*12 2.400000047683717*/16.35, /*13 2.500000047683717*/
25.07, /*14 2.600000047683717*/25.11, /*15 2.700000047683717*/25.13, /*16 2.8000000476837172*/25.12, /*17 2.9000000476837173*/
25.09, /*18 3.0000000476837174*/25.09, /*19 3.1000000476837175*/25.13, /*20 3.2000000476837176*/25.1, /*21 3.3000000476837177*/
25.12, /*22 3.4000000476837178*/25.12, /*23 3.500000047683718*/25.12, /*24 3.600000047683718*/25.14, /*25 3.700000047683718*/
25.12, /*26 3.800000047683718*/25.1, /*27 3.900000047683718*/25.12, /*28 4.000000047683718*/25.11, /*29 4.100000047683718*/
24.39, /*30 4.200000047683718*/24.06, /*31 4.300000047683717*/23.21, /*32 4.400000047683717*/22.55 }, {/*1 rpm=650.0*//*0 1.2000000476837158*/
1.53, /*1 1.300000047683716*/1.55, /*2 1.400000047683716*/1.54, /*3 1.500000047683716*/1.52, /*4 1.6000000476837162*/
1.52, /*5 1.7000000476837163*/1.52, /*6 1.8000000476837164*/1.52, /*7 1.9000000476837164*/1.54, /*8 2.0000000476837165*/
1.53, /*9 2.1000000476837166*/1.54, /*10 2.2000000476837167*/6.01, /*11 2.300000047683717*/10.64, /*12 2.400000047683717*/
11.93, /*13 2.500000047683717*/18.35, /*14 2.600000047683717*/17.72, /*15 2.700000047683717*/22.67, /*16 2.8000000476837172*/
21.79, /*17 2.9000000476837173*/21.12, /*18 3.0000000476837174*/20.25, /*19 3.1000000476837175*/19.4, /*20 3.2000000476837176*/
18.7, /*21 3.3000000476837177*/18.29, /*22 3.4000000476837178*/17.68, /*23 3.500000047683718*/17.14, /*24 3.600000047683718*/
16.98, /*25 3.700000047683718*/16.98, /*26 3.800000047683718*/16.97, /*27 3.900000047683718*/16.92, /*28 4.000000047683718*/
17.01, /*29 4.100000047683718*/16.97, /*30 4.200000047683718*/16.92, /*31 4.300000047683717*/16.97, /*32 4.400000047683717*/
17.01 }, {/*2 rpm=900.0*//*0 1.2000000476837158*/1.55, /*1 1.300000047683716*/1.57, /*2 1.400000047683716*/1.53, /*3 1.500000047683716*/
1.52, /*4 1.6000000476837162*/1.57, /*5 1.7000000476837163*/1.53, /*6 1.8000000476837164*/1.55, /*7 1.9000000476837164*/
1.54, /*8 2.0000000476837165*/2.72, /*9 2.1000000476837166*/2.96, /*10 2.2000000476837167*/3.17, /*11 2.300000047683717*/
8.56, /*12 2.400000047683717*/8.77, /*13 2.500000047683717*/13.44, /*14 2.600000047683717*/14.77, /*15 2.700000047683717*/
21.12, /*16 2.8000000476837172*/20.03, /*17 2.9000000476837173*/19.38, /*18 3.0000000476837174*/18.57, /*19 3.1000000476837175*/
17.67, /*20 3.2000000476837176*/17.32, /*21 3.3000000476837177*/16.97, /*22 3.4000000476837178*/16.96, /*23 3.500000047683718*/
16.97, /*24 3.600000047683718*/16.96, /*25 3.700000047683718*/17.03, /*26 3.800000047683718*/16.95, /*27 3.900000047683718*/
17.02, /*28 4.000000047683718*/16.95, /*29 4.100000047683718*/17.02, /*30 4.200000047683718*/16.98, /*31 4.300000047683717*/
17.01, /*32 4.400000047683717*/16.97 }, {/*3 rpm=1150.0*//*0 1.2000000476837158*/1.54, /*1 1.300000047683716*/
1.58, /*2 1.400000047683716*/1.57, /*3 1.500000047683716*/1.54, /*4 1.6000000476837162*/1.54, /*5 1.7000000476837163*/
1.54, /*6 1.8000000476837164*/1.55, /*7 1.9000000476837164*/2.05, /*8 2.0000000476837165*/3.18, /*9 2.1000000476837166*/
4.01, /*10 2.2000000476837167*/5.17, /*11 2.300000047683717*/6.92, /*12 2.400000047683717*/8.35, /*13 2.500000047683717*/
10.01, /*14 2.600000047683717*/13.76, /*15 2.700000047683717*/17.3, /*16 2.8000000476837172*/16.48, /*17 2.9000000476837173*/
15.84, /*18 3.0000000476837174*/15.27, /*19 3.1000000476837175*/15.26, /*20 3.2000000476837176*/15.28, /*21 3.3000000476837177*/
15.26, /*22 3.4000000476837178*/15.26, /*23 3.500000047683718*/15.27, /*24 3.600000047683718*/15.25, /*25 3.700000047683718*/
15.27, /*26 3.800000047683718*/15.25, /*27 3.900000047683718*/15.23, /*28 4.000000047683718*/15.22, /*29 4.100000047683718*/
15.28, /*30 4.200000047683718*/15.26, /*31 4.300000047683717*/15.22, /*32 4.400000047683717*/15.25 }, {/*4 rpm=1400.0*//*0 1.2000000476837158*/
1.57, /*1 1.300000047683716*/1.54, /*2 1.400000047683716*/1.57, /*3 1.500000047683716*/1.52, /*4 1.6000000476837162*/
1.57, /*5 1.7000000476837163*/1.54, /*6 1.8000000476837164*/1.55, /*7 1.9000000476837164*/1.97, /*8 2.0000000476837165*/
2.88, /*9 2.1000000476837166*/2.92, /*10 2.2000000476837167*/2.92, /*11 2.300000047683717*/5.8, /*12 2.400000047683717*/
5.86, /*13 2.500000047683717*/5.86, /*14 2.600000047683717*/11.1, /*15 2.700000047683717*/10.52, /*16 2.8000000476837172*/
18.84, /*17 2.9000000476837173*/17.88, /*18 3.0000000476837174*/16.86, /*19 3.1000000476837175*/16.14, /*20 3.2000000476837176*/
15.71, /*21 3.3000000476837177*/15.68, /*22 3.4000000476837178*/15.68, /*23 3.500000047683718*/15.72, /*24 3.600000047683718*/
15.68, /*25 3.700000047683718*/15.65, /*26 3.800000047683718*/15.67, /*27 3.900000047683718*/15.72, /*28 4.000000047683718*/
15.69, /*29 4.100000047683718*/15.68, /*30 4.200000047683718*/15.68, /*31 4.300000047683717*/15.69, /*32 4.400000047683717*/
15.68 }, {/*5 rpm=1650.0*//*0 1.2000000476837158*/1.55, /*1 1.300000047683716*/1.55, /*2 1.400000047683716*/
1.55, /*3 1.500000047683716*/1.55, /*4 1.6000000476837162*/1.55, /*5 1.7000000476837163*/1.57, /*6 1.8000000476837164*/
1.55, /*7 1.9000000476837164*/1.53, /*8 2.0000000476837165*/2.33, /*9 2.1000000476837166*/3.23, /*10 2.2000000476837167*/
3.88, /*11 2.300000047683717*/5.09, /*12 2.400000047683717*/6.63, /*13 2.500000047683717*/6.63, /*14 2.600000047683717*/
6.57, /*15 2.700000047683717*/11.31, /*16 2.8000000476837172*/10.93, /*17 2.9000000476837173*/17.22, /*18 3.0000000476837174*/
16.14, /*19 3.1000000476837175*/15.63, /*20 3.2000000476837176*/15.22, /*21 3.3000000476837177*/15.11, /*22 3.4000000476837178*/
15.19, /*23 3.500000047683718*/15.14, /*24 3.600000047683718*/15.13, /*25 3.700000047683718*/15.15, /*26 3.800000047683718*/
15.1, /*27 3.900000047683718*/15.5, /*28 4.000000047683718*/15.18, /*29 4.100000047683718*/15.11, /*30 4.200000047683718*/
15.17, /*31 4.300000047683717*/15.19, /*32 4.400000047683717*/15.17 }, {/*6 rpm=1900.0*//*0 1.2000000476837158*/
1.57, /*1 1.300000047683716*/1.53, /*2 1.400000047683716*/1.57, /*3 1.500000047683716*/1.55, /*4 1.6000000476837162*/
1.54, /*5 1.7000000476837163*/1.54, /*6 1.8000000476837164*/1.55, /*7 1.9000000476837164*/1.69, /*8 2.0000000476837165*/
2.13, /*9 2.1000000476837166*/2.68, /*10 2.2000000476837167*/3.44, /*11 2.300000047683717*/4.46, /*12 2.400000047683717*/
5.34, /*13 2.500000047683717*/5.36, /*14 2.600000047683717*/5.34, /*15 2.700000047683717*/9.63, /*16 2.8000000476837172*/
9.4, /*17 2.9000000476837173*/17.94, /*18 3.0000000476837174*/16.8, /*19 3.1000000476837175*/15.9, /*20 3.2000000476837176*/
15.35, /*21 3.3000000476837177*/15.52, /*22 3.4000000476837178*/15.44, /*23 3.500000047683718*/15.38, /*24 3.600000047683718*/
15.43, /*25 3.700000047683718*/15.42, /*26 3.800000047683718*/15.43, /*27 3.900000047683718*/15.43, /*28 4.000000047683718*/
15.39, /*29 4.100000047683718*/15.39, /*30 4.200000047683718*/15.43, /*31 4.300000047683717*/15.44, /*32 4.400000047683717*/
15.44 }, {/*7 rpm=2150.0*//*0 1.2000000476837158*/1.57, /*1 1.300000047683716*/1.54, /*2 1.400000047683716*/
1.54, /*3 1.500000047683716*/1.55, /*4 1.6000000476837162*/1.54, /*5 1.7000000476837163*/1.58, /*6 1.8000000476837164*/
1.54, /*7 1.9000000476837164*/1.64, /*8 2.0000000476837165*/2.1, /*9 2.1000000476837166*/2.1, /*10 2.2000000476837167*/
3.07, /*11 2.300000047683717*/4.0, /*12 2.400000047683717*/5.23, /*13 2.500000047683717*/5.69, /*14 2.600000047683717*/
6.88, /*15 2.700000047683717*/8.44, /*16 2.8000000476837172*/10.4, /*17 2.9000000476837173*/13.64, /*18 3.0000000476837174*/
16.37, /*19 3.1000000476837175*/15.06, /*20 3.2000000476837176*/15.19, /*21 3.3000000476837177*/15.21, /*22 3.4000000476837178*/
15.23, /*23 3.500000047683718*/15.18, /*24 3.600000047683718*/15.18, /*25 3.700000047683718*/15.18, /*26 3.800000047683718*/
15.22, /*27 3.900000047683718*/15.22, /*28 4.000000047683718*/15.19, /*29 4.100000047683718*/15.22, /*30 4.200000047683718*/
15.18, /*31 4.300000047683717*/15.22, /*32 4.400000047683717*/15.22 }, {/*8 rpm=2400.0*//*0 1.2000000476837158*/
1.55, /*1 1.300000047683716*/1.55, /*2 1.400000047683716*/1.57, /*3 1.500000047683716*/1.58, /*4 1.6000000476837162*/
1.57, /*5 1.7000000476837163*/1.55, /*6 1.8000000476837164*/1.57, /*7 1.9000000476837164*/1.55, /*8 2.0000000476837165*/
1.85, /*9 2.1000000476837166*/2.42, /*10 2.2000000476837167*/2.79, /*11 2.300000047683717*/3.6, /*12 2.400000047683717*/
4.34, /*13 2.500000047683717*/5.69, /*14 2.600000047683717*/5.71, /*15 2.700000047683717*/5.65, /*16 2.8000000476837172*/
9.22, /*17 2.9000000476837173*/11.52, /*18 3.0000000476837174*/12.56, /*19 3.1000000476837175*/12.05, /*20 3.2000000476837176*/
12.14, /*21 3.3000000476837177*/15.25, /*22 3.4000000476837178*/15.23, /*23 3.500000047683718*/15.3, /*24 3.600000047683718*/
15.25, /*25 3.700000047683718*/15.27, /*26 3.800000047683718*/15.3, /*27 3.900000047683718*/15.27, /*28 4.000000047683718*/
15.22, /*29 4.100000047683718*/15.25, /*30 4.200000047683718*/15.19, /*31 4.300000047683717*/15.31, /*32 4.400000047683717*/
15.27 }, {/*9 rpm=2650.0*//*0 1.2000000476837158*/1.55, /*1 1.300000047683716*/1.57, /*2 1.400000047683716*/
1.55, /*3 1.500000047683716*/0.82, /*4 1.6000000476837162*/0.87, /*5 1.7000000476837163*/0.85, /*6 1.8000000476837164*/
0.0, /*7 1.9000000476837164*/0.0, /*8 2.0000000476837165*/1.75, /*9 2.1000000476837166*/2.26, /*10 2.2000000476837167*/
2.23, /*11 2.300000047683717*/2.26, /*12 2.400000047683717*/4.01, /*13 2.500000047683717*/4.0, /*14 2.600000047683717*/
3.99, /*15 2.700000047683717*/6.84, /*16 2.8000000476837172*/8.43, /*17 2.9000000476837173*/8.39, /*18 3.0000000476837174*/
11.44, /*19 3.1000000476837175*/16.5, /*20 3.2000000476837176*/15.88, /*21 3.3000000476837177*/15.56, /*22 3.4000000476837178*/
15.5, /*23 3.500000047683718*/15.47, /*24 3.600000047683718*/15.55, /*25 3.700000047683718*/15.48, /*26 3.800000047683718*/
15.5, /*27 3.900000047683718*/15.42, /*28 4.000000047683718*/15.52, /*29 4.100000047683718*/15.48, /*30 4.200000047683718*/
15.51, /*31 4.300000047683717*/15.53, /*32 4.400000047683717*/15.47 }, {/*10 rpm=2900.0*//*0 1.2000000476837158*/
0.81, /*1 1.300000047683716*/0.8, /*2 1.400000047683716*/0.81, /*3 1.500000047683716*/0.0, /*4 1.6000000476837162*/
0.0, /*5 1.7000000476837163*/0.0, /*6 1.8000000476837164*/0.0, /*7 1.9000000476837164*/0.0, /*8 2.0000000476837165*/
0.0, /*9 2.1000000476837166*/2.0, /*10 2.2000000476837167*/2.42, /*11 2.300000047683717*/2.43, /*12 2.400000047683717*/
2.42, /*13 2.500000047683717*/4.84, /*14 2.600000047683717*/4.8, /*15 2.700000047683717*/4.79, /*16 2.8000000476837172*/
7.63, /*17 2.9000000476837173*/7.65, /*18 3.0000000476837174*/7.61, /*19 3.1000000476837175*/13.02, /*20 3.2000000476837176*/
12.28, /*21 3.3000000476837177*/15.27, /*22 3.4000000476837178*/15.55, /*23 3.500000047683718*/15.5, /*24 3.600000047683718*/
15.65, /*25 3.700000047683718*/15.72, /*26 3.800000047683718*/15.71, /*27 3.900000047683718*/15.38, /*28 4.000000047683718*/
15.52, /*29 4.100000047683718*/15.63, /*30 4.200000047683718*/15.46, /*31 4.300000047683717*/15.59, /*32 4.400000047683717*/
15.59 }, {/*11 rpm=3150.0*//*0 1.2000000476837158*/0.8, /*1 1.300000047683716*/0.79, /*2 1.400000047683716*/
0.81, /*3 1.500000047683716*/0.81, /*4 1.6000000476837162*/0.0, /*5 1.7000000476837163*/0.0, /*6 1.8000000476837164*/
0.0, /*7 1.9000000476837164*/0.0, /*8 2.0000000476837165*/0.0, /*9 2.1000000476837166*/1.91, /*10 2.2000000476837167*/
1.89, /*11 2.300000047683717*/2.86, /*12 2.400000047683717*/3.43, /*13 2.500000047683717*/4.05, /*14 2.600000047683717*/
4.07, /*15 2.700000047683717*/5.84, /*16 2.8000000476837172*/7.03, /*17 2.9000000476837173*/7.73, /*18 3.0000000476837174*/
7.69, /*19 3.1000000476837175*/7.71, /*20 3.2000000476837176*/7.71, /*21 3.3000000476837177*/16.63, /*22 3.4000000476837178*/
15.55, /*23 3.500000047683718*/15.47, /*24 3.600000047683718*/15.8, /*25 3.700000047683718*/15.81, /*26 3.800000047683718*/
15.79, /*27 3.900000047683718*/15.77, /*28 4.000000047683718*/15.85, /*29 4.100000047683718*/15.81, /*30 4.200000047683718*/
15.81, /*31 4.300000047683717*/15.86, /*32 4.400000047683717*/15.8 }, {/*12 rpm=3400.0*//*0 1.2000000476837158*/
0.79, /*1 1.300000047683716*/0.81, /*2 1.400000047683716*/0.81, /*3 1.500000047683716*/0.81, /*4 1.6000000476837162*/
0.0, /*5 1.7000000476837163*/0.0, /*6 1.8000000476837164*/0.0, /*7 1.9000000476837164*/0.0, /*8 2.0000000476837165*/
0.0, /*9 2.1000000476837166*/0.0, /*10 2.2000000476837167*/2.2, /*11 2.300000047683717*/2.48, /*12 2.400000047683717*/
2.47, /*13 2.500000047683717*/2.51, /*14 2.600000047683717*/4.57, /*15 2.700000047683717*/4.55, /*16 2.8000000476837172*/
4.55, /*17 2.9000000476837173*/4.61, /*18 3.0000000476837174*/8.56, /*19 3.1000000476837175*/9.51, /*20 3.2000000476837176*/
11.93, /*21 3.3000000476837177*/12.81, /*22 3.4000000476837178*/12.81, /*23 3.500000047683718*/15.76, /*24 3.600000047683718*/
15.53, /*25 3.700000047683718*/15.84, /*26 3.800000047683718*/15.81, /*27 3.900000047683718*/15.97, /*28 4.000000047683718*/
16.04, /*29 4.100000047683718*/15.8, /*30 4.200000047683718*/15.85, /*31 4.300000047683717*/15.68, /*32 4.400000047683717*/
16.12 }, {/*13 rpm=3650.0*//*0 1.2000000476837158*/0.77, /*1 1.300000047683716*/0.8, /*2 1.400000047683716*/
0.78, /*3 1.500000047683716*/0.81, /*4 1.6000000476837162*/0.0, /*5 1.7000000476837163*/0.0, /*6 1.8000000476837164*/
0.0, /*7 1.9000000476837164*/0.0, /*8 2.0000000476837165*/0.0, /*9 2.1000000476837166*/0.0, /*10 2.2000000476837167*/
0.0, /*11 2.300000047683717*/2.54, /*12 2.400000047683717*/3.0, /*13 2.500000047683717*/3.57, /*14 2.600000047683717*/
4.28, /*15 2.700000047683717*/4.32, /*16 2.8000000476837172*/6.13, /*17 2.9000000476837173*/7.44, /*18 3.0000000476837174*/
8.17, /*19 3.1000000476837175*/8.97, /*20 3.2000000476837176*/8.93, /*21 3.3000000476837177*/12.06, /*22 3.4000000476837178*/
11.96, /*23 3.500000047683718*/15.31, /*24 3.600000047683718*/15.79, /*25 3.700000047683718*/15.71, /*26 3.800000047683718*/
15.75, /*27 3.900000047683718*/15.77, /*28 4.000000047683718*/15.85, /*29 4.100000047683718*/15.82, /*30 4.200000047683718*/
15.84, /*31 4.300000047683717*/15.76, /*32 4.400000047683717*/15.73 }, {/*14 rpm=3900.0*//*0 1.2000000476837158*/
0.8, /*1 1.300000047683716*/0.79, /*2 1.400000047683716*/0.81, /*3 1.500000047683716*/0.81, /*4 1.6000000476837162*/
0.0, /*5 1.7000000476837163*/0.0, /*6 1.8000000476837164*/0.0, /*7 1.9000000476837164*/0.0, /*8 2.0000000476837165*/
0.0, /*9 2.1000000476837166*/0.0, /*10 2.2000000476837167*/1.99, /*11 2.300000047683717*/2.39, /*12 2.400000047683717*/
2.8, /*13 2.500000047683717*/2.78, /*14 2.600000047683717*/4.05, /*15 2.700000047683717*/4.82, /*16 2.8000000476837172*/
4.73, /*17 2.9000000476837173*/6.94, /*18 3.0000000476837174*/7.55, /*19 3.1000000476837175*/8.39, /*20 3.2000000476837176*/
10.25, /*21 3.3000000476837177*/11.09, /*22 3.4000000476837178*/12.43, /*23 3.500000047683718*/14.85, /*24 3.600000047683718*/
14.85, /*25 3.700000047683718*/15.6, /*26 3.800000047683718*/15.52, /*27 3.900000047683718*/15.55, /*28 4.000000047683718*/
15.55, /*29 4.100000047683718*/15.61, /*30 4.200000047683718*/15.64, /*31 4.300000047683717*/15.6, /*32 4.400000047683717*/
15.6 }, {/*15 rpm=4150.0*//*0 1.2000000476837158*/0.79, /*1 1.300000047683716*/0.8, /*2 1.400000047683716*/0.81, /*3 1.500000047683716*/
0.8, /*4 1.6000000476837162*/0.0, /*5 1.7000000476837163*/0.0, /*6 1.8000000476837164*/0.0, /*7 1.9000000476837164*/
0.0, /*8 2.0000000476837165*/0.0, /*9 2.1000000476837166*/0.0, /*10 2.2000000476837167*/1.91, /*11 2.300000047683717*/
2.31, /*12 2.400000047683717*/2.92, /*13 2.500000047683717*/2.9, /*14 2.600000047683717*/4.19, /*15 2.700000047683717*/
4.51, /*16 2.8000000476837172*/4.57, /*17 2.9000000476837173*/6.61, /*18 3.0000000476837174*/6.57, /*19 3.1000000476837175*/
7.88, /*20 3.2000000476837176*/7.88, /*21 3.3000000476837177*/10.5, /*22 3.4000000476837178*/11.61, /*23 3.500000047683718*/
11.76, /*24 3.600000047683718*/15.22, /*25 3.700000047683718*/16.0, /*26 3.800000047683718*/15.81, /*27 3.900000047683718*/
15.65, /*28 4.000000047683718*/15.71, /*29 4.100000047683718*/15.73, /*30 4.200000047683718*/15.68, /*31 4.300000047683717*/
15.69, /*32 4.400000047683717*/15.81 }, {/*16 rpm=4400.0*//*0 1.2000000476837158*/0.8, /*1 1.300000047683716*/
0.79, /*2 1.400000047683716*/0.79, /*3 1.500000047683716*/0.81, /*4 1.6000000476837162*/0.0, /*5 1.7000000476837163*/
0.0, /*6 1.8000000476837164*/0.0, /*7 1.9000000476837164*/0.0, /*8 2.0000000476837165*/0.0, /*9 2.1000000476837166*/
0.0, /*10 2.2000000476837167*/1.86, /*11 2.300000047683717*/2.23, /*12 2.400000047683717*/2.21, /*13 2.500000047683717*/
3.04, /*14 2.600000047683717*/3.65, /*15 2.700000047683717*/3.64, /*16 2.8000000476837172*/5.19, /*17 2.9000000476837173*/
6.34, /*18 3.0000000476837174*/6.23, /*19 3.1000000476837175*/6.21, /*20 3.2000000476837176*/6.13, /*21 3.3000000476837177*/
10.07, /*22 3.4000000476837178*/11.03, /*23 3.500000047683718*/12.26, /*24 3.600000047683718*/12.22, /*25 3.700000047683718*/
12.27, /*26 3.800000047683718*/15.93, /*27 3.900000047683718*/15.57, /*28 4.000000047683718*/16.0, /*29 4.100000047683718*/
15.86, /*30 4.200000047683718*/15.89, /*31 4.300000047683717*/15.93, /*32 4.400000047683717*/15.79 }, {/*17 rpm=4650.0*//*0 1.2000000476837158*/
0.8, /*1 1.300000047683716*/0.8, /*2 1.400000047683716*/0.8, /*3 1.500000047683716*/0.0, /*4 1.6000000476837162*/
0.0, /*5 1.7000000476837163*/0.0, /*6 1.8000000476837164*/0.0, /*7 1.9000000476837164*/0.0, /*8 2.0000000476837165*/
0.0, /*9 2.1000000476837166*/0.0, /*10 2.2000000476837167*/1.8, /*11 2.300000047683717*/2.16, /*12 2.400000047683717*/
2.5, /*13 2.500000047683717*/2.88, /*14 2.600000047683717*/3.49, /*15 2.700000047683717*/3.47, /*16 2.8000000476837172*/
3.47, /*17 2.9000000476837173*/5.92, /*18 3.0000000476837174*/5.9, /*19 3.1000000476837175*/7.09, /*20 3.2000000476837176*/
8.6, /*21 3.3000000476837177*/9.5, /*22 3.4000000476837178*/9.46, /*23 3.500000047683718*/9.43, /*24 3.600000047683718*/
9.55, /*25 3.700000047683718*/15.86, /*26 3.800000047683718*/15.79, /*27 3.900000047683718*/15.85, /*28 4.000000047683718*/
15.76, /*29 4.100000047683718*/15.72, /*30 4.200000047683718*/15.77, /*31 4.300000047683717*/16.0, /*32 4.400000047683717*/
15.97 }, {/*18 rpm=4900.0*//*0 1.2000000476837158*/0.8, /*1 1.300000047683716*/0.8, /*2 1.400000047683716*/0.79, /*3 1.500000047683716*/
0.0, /*4 1.6000000476837162*/0.0, /*5 1.7000000476837163*/0.0, /*6 1.8000000476837164*/0.0, /*7 1.9000000476837164*/
0.0, /*8 2.0000000476837165*/0.0, /*9 2.1000000476837166*/0.0, /*10 2.2000000476837167*/0.0, /*11 2.300000047683717*/
2.06, /*12 2.400000047683717*/2.07, /*13 2.500000047683717*/2.76, /*14 2.600000047683717*/2.74, /*15 2.700000047683717*/
3.97, /*16 2.8000000476837172*/4.76, /*17 2.9000000476837173*/5.67, /*18 3.0000000476837174*/5.67, /*19 3.1000000476837175*/
5.61, /*20 3.2000000476837176*/5.59, /*21 3.3000000476837177*/9.06, /*22 3.4000000476837178*/8.98, /*23 3.500000047683718*/
10.97, /*24 3.600000047683718*/12.25, /*25 3.700000047683718*/14.48, /*26 3.800000047683718*/14.77, /*27 3.900000047683718*/
16.1, /*28 4.000000047683718*/16.11, /*29 4.100000047683718*/16.11, /*30 4.200000047683718*/15.98, /*31 4.300000047683717*/
16.13, /*32 4.400000047683717*/16.12 }, {/*19 rpm=5150.0*//*0 1.2000000476837158*/0.79, /*1 1.300000047683716*/
0.8, /*2 1.400000047683716*/0.81, /*3 1.500000047683716*/0.81, /*4 1.6000000476837162*/0.0, /*5 1.7000000476837163*/
0.0, /*6 1.8000000476837164*/0.0, /*7 1.9000000476837164*/0.0, /*8 2.0000000476837165*/0.0, /*9 2.1000000476837166*/
0.0, /*10 2.2000000476837167*/0.0, /*11 2.300000047683717*/2.01, /*12 2.400000047683717*/2.31, /*13 2.500000047683717*/
2.9, /*14 2.600000047683717*/3.48, /*15 2.700000047683717*/3.44, /*16 2.8000000476837172*/4.51, /*17 2.9000000476837173*/
4.53, /*18 3.0000000476837174*/5.88, /*19 3.1000000476837175*/7.09, /*20 3.2000000476837176*/7.82, /*21 3.3000000476837177*/
8.65, /*22 3.4000000476837178*/9.48, /*23 3.500000047683718*/10.56, /*24 3.600000047683718*/11.77, /*25 3.700000047683718*/
13.94, /*26 3.800000047683718*/15.28, /*27 3.900000047683718*/16.22, /*28 4.000000047683718*/16.23, /*29 4.100000047683718*/
16.23, /*30 4.200000047683718*/15.96, /*31 4.300000047683717*/16.27, /*32 4.400000047683717*/16.11 }, {/*20 rpm=5400.0*//*0 1.2000000476837158*/
0.81, /*1 1.300000047683716*/0.81, /*2 1.400000047683716*/0.79, /*3 1.500000047683716*/0.0, /*4 1.6000000476837162*/
0.0, /*5 1.7000000476837163*/0.0, /*6 1.8000000476837164*/0.0, /*7 1.9000000476837164*/0.0, /*8 2.0000000476837165*/
0.0, /*9 2.1000000476837166*/0.0, /*10 2.2000000476837167*/0.0, /*11 2.300000047683717*/1.91, /*12 2.400000047683717*/
1.95, /*13 2.500000047683717*/2.55, /*14 2.600000047683717*/3.03, /*15 2.700000047683717*/3.07, /*16 2.8000000476837172*/
3.0, /*17 2.9000000476837173*/4.75, /*18 3.0000000476837174*/5.65, /*19 3.1000000476837175*/6.21, /*20 3.2000000476837176*/
6.11, /*21 3.3000000476837177*/8.31, /*22 3.4000000476837178*/8.31, /*23 3.500000047683718*/10.1, /*24 3.600000047683718*/
11.03, /*25 3.700000047683718*/11.14, /*26 3.800000047683718*/11.14, /*27 3.900000047683718*/11.18, /*28 4.000000047683718*/
16.03, /*29 4.100000047683718*/16.01, /*30 4.200000047683718*/16.04, /*31 4.300000047683717*/15.86, /*32 4.400000047683717*/
15.97 }, {/*21 rpm=5650.0*//*0 1.2000000476837158*/0.81, /*1 1.300000047683716*/0.8, /*2 1.400000047683716*/0.8, /*3 1.500000047683716*/
0.0, /*4 1.6000000476837162*/0.0, /*5 1.7000000476837163*/0.0, /*6 1.8000000476837164*/0.0, /*7 1.9000000476837164*/
0.0, /*8 2.0000000476837165*/0.0, /*9 2.1000000476837166*/0.0, /*10 2.2000000476837167*/0.0, /*11 2.300000047683717*/
0.0, /*12 2.400000047683717*/2.14, /*13 2.500000047683717*/2.69, /*14 2.600000047683717*/2.69, /*15 2.700000047683717*/
3.49, /*16 2.8000000476837172*/4.15, /*17 2.9000000476837173*/4.94, /*18 3.0000000476837174*/4.9, /*19 3.1000000476837175*/
5.94, /*20 3.2000000476837176*/7.21, /*21 3.3000000476837177*/8.01, /*22 3.4000000476837178*/7.96, /*23 3.500000047683718*/
7.96, /*24 3.600000047683718*/11.85, /*25 3.700000047683718*/12.06, /*26 3.800000047683718*/13.11, /*27 3.900000047683718*/
12.86, /*28 4.000000047683718*/15.65, /*29 4.100000047683718*/15.72, /*30 4.200000047683718*/15.75, /*31 4.300000047683717*/
15.65, /*32 4.400000047683717*/15.63 }, {/*22 rpm=5900.0*//*0 1.2000000476837158*/0.81, /*1 1.300000047683716*/
0.8, /*2 1.400000047683716*/0.81, /*3 1.500000047683716*/0.81, /*4 1.6000000476837162*/0.0, /*5 1.7000000476837163*/
0.0, /*6 1.8000000476837164*/0.0, /*7 1.9000000476837164*/0.0, /*8 2.0000000476837165*/0.0, /*9 2.1000000476837166*/
0.0, /*10 2.2000000476837167*/0.0, /*11 2.300000047683717*/0.0, /*12 2.400000047683717*/0.0, /*13 2.500000047683717*/
2.42, /*14 2.600000047683717*/2.78, /*15 2.700000047683717*/3.34, /*16 2.8000000476837172*/4.03, /*17 2.9000000476837173*/
4.01, /*18 3.0000000476837174*/3.97, /*19 3.1000000476837175*/5.73, /*20 3.2000000476837176*/6.86, /*21 3.3000000476837177*/
6.9, /*22 3.4000000476837178*/6.92, /*23 3.500000047683718*/9.23, /*24 3.600000047683718*/9.31, /*25 3.700000047683718*/
9.23, /*26 3.800000047683718*/12.56, /*27 3.900000047683718*/14.61, /*28 4.000000047683718*/15.22, /*29 4.100000047683718*/
15.19, /*30 4.200000047683718*/15.13, /*31 4.300000047683717*/15.17, /*32 4.400000047683717*/15.15 } };

void configureShaftPositionEmulatorShape(PwmConfig *state) {
	myfloat x = ASPIRE_MAGIC_DUTY_CYCLE / 4;

	/**
	 * 1993 Ford Aspire has two hall sensors for CKP sensor
	 *
	 * X__X__X__X__  38% duty cycle
	 * __XXXXXX____  50% duty cycle
	 */

	myfloat secondStart = 0.17; //x + (0.25 - x) / 2;

	myfloat switchTimes[] = { x, secondStart, 0.25, 0.25 + x, 0.5, 0.5 + x,
			secondStart + 0.5,
			0.75, 0.75 + x, 1 };

	/**
	 * One signal per cam shaft revolution
	 */
	int pinStates0[] = { 1, 0, 0, 0, 0,
			             0, 1, 1, 1, 1};

	/**
	 * Four signals per cam shaft revolution
	 */
	int pinStates1[] = { 0, 0, 1 /* start of 2nd signal*/ , 0, 1 /* start of 3rd signal*/, 0, 0, 1, 0, 1 };


	int *pinStates[2] = { pinStates0, pinStates1 };

	weComplexInit("distributor", state, 0, 10, switchTimes, 2, pinStates);
}

void configureEngineEventHandler(EventHandlerConfiguration *config) {
  memset(config->injectAtEventIndex, sizeof(config->injectAtEventIndex), 0);
  memset(config->igniteAtEventIndex, sizeof(config->igniteAtEventIndex), 0);
	config->injectAtEventIndex[6] = 1;
	config->injectAtEventIndex[3] = 2;
	config->injectAtEventIndex[8] = 3;
	config->injectAtEventIndex[1] = 4;

	config->igniteAtEventIndex[1] = 1;
	config->igniteAtEventIndex[3] = 1;
	config->igniteAtEventIndex[6] = 1;
	config->igniteAtEventIndex[8] = 1;
}

static void setDefaultFuelMap(void) {
	for (int i = 0; i < FUEL_MAF_COUNT; i++)
		engineConfiguration->fuelKeyBins[i] = fuel_maf_bins[i];
	for (int i = 0; i < FUEL_RPM_COUNT; i++)
		engineConfiguration->fuelRpmBins[i] = fuel_rpm_bins[i];
	for (int k = 0; k < FUEL_MAF_COUNT; k++) {
		for (int r = 0; r < FUEL_RPM_COUNT; r++) {
			// todo: this is BAD, this needs to be fixed - TS table indexes are different from default indexes
			engineConfiguration->fuelTable[k][r] = fuel_table[r][k];
		}
	}
}

void setDefaultEngineConfiguration(EngineConfiguration *engineConfiguration) {
	engineConfiguration->tpsMin = 1;
	engineConfiguration->tpsMax = 1000;

	engineConfiguration->rpmHardLimit = 7000;

	setDefaultFuelMap();
}
#endif /* EFI_ENGINE_FORD_ASPIRE */
