/**
 * @file	advance_map.c
 *
 * @date Mar 27, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "advance_map.h"
#include "interpolation.h"
// that's for 'max' function
#include "idle_controller.h"

#include "engine_controller.h"

extern EngineConfiguration *engineConfiguration;
extern EngineConfiguration2 *engineConfiguration2;

#define AD_RPM_COUNT 23
static float ad_rpm_table[] = {400.0, 650.0, 900.0, 1150.0, 1400.0, 1650.0, 1900.0, 2150.0, 2400.0, 2650.0, 2900.0, 3150.0, 3400.0, 3650.0, 3900.0, 4150.0, 4400.0, 4650.0, 4900.0, 5150.0, 5400.0, 5650.0, 5900.0};

#define AD_MAF_COUNT 35
static float ad_maf_table[] = {1.0, 1.1, 1.2000000000000002, 1.3000000000000003, 1.4000000000000004, 1.5000000000000004, 1.6000000000000005, 1.7000000000000006, 1.8000000000000007, 1.9000000000000008, 2.000000000000001, 2.100000000000001, 2.200000000000001, 2.300000000000001, 2.4000000000000012, 2.5000000000000013, 2.6000000000000014, 2.7000000000000015, 2.8000000000000016, 2.9000000000000017, 3.0000000000000018, 3.100000000000002, 3.200000000000002, 3.300000000000002, 3.400000000000002, 3.500000000000002, 3.6000000000000023, 3.7000000000000024, 3.8000000000000025, 3.9000000000000026, 4.000000000000003, 4.100000000000002, 4.200000000000002, 4.300000000000002, 4.400000000000001};

static float ad_table[23][35] = {
{/*0*//*0*/0.888, /*1*/0.863, /*2*/0.864, /*3*/0.888, /*4*/0.864, /*5*/0.863, /*6*/0.888, /*7*/0.888, /*8*/0.863, /*9*/0.888, /*10*/0.864, /*11*/1.031, /*12*/2.459, /*13*/3.875, /*14*/5.256, /*15*/5.268, /*16*/5.28, /*17*/5.255, /*18*/5.28, /*19*/5.28, /*20*/5.255, /*21*/5.28, /*22*/5.244, /*23*/5.256, /*24*/5.268, /*25*/5.279, /*26*/5.255, /*27*/5.279, /*28*/5.28, /*29*/5.256, /*30*/5.279, /*31*/5.28, /*32*/5.244, /*33*/5.244, /*34*/0.072},
{/*1*//*0*/0.312, /*1*/0.292, /*2*/0.331, /*3*/0.331, /*4*/0.273, /*5*/0.331, /*6*/0.292, /*7*/0.331, /*8*/0.292, /*9*/0.331, /*10*/0.292, /*11*/0.292, /*12*/-0.682, /*13*/0.117, /*14*/0.682, /*15*/4.347, /*16*/4.932, /*17*/4.893, /*18*/4.932, /*19*/4.933, /*20*/4.932, /*21*/4.932, /*22*/4.893, /*23*/4.932, /*24*/4.894, /*25*/4.933, /*26*/4.894, /*27*/4.932, /*28*/4.931, /*29*/4.932, /*30*/4.933, /*31*/4.875, /*32*/4.933, /*33*/4.894, /*34*/0.175},
{/*2*//*0*/-0.837, /*1*/-0.756, /*2*/-0.809, /*3*/-0.755, /*4*/-0.863, /*5*/-0.755, /*6*/-0.783, /*7*/-0.755, /*8*/-0.837, /*9*/-0.783, /*10*/-0.782, /*11*/-0.783, /*12*/-1.674, /*13*/-2.862, /*14*/-2.349, /*15*/0.89, /*16*/3.347, /*17*/3.887, /*18*/4.05, /*19*/4.049, /*20*/4.049, /*21*/3.996, /*22*/4.05, /*23*/3.995, /*24*/4.049, /*25*/3.996, /*26*/4.05, /*27*/4.05, /*28*/4.05, /*29*/4.047, /*30*/4.05, /*31*/4.05, /*32*/4.05, /*33*/4.05, /*34*/4.05},
{/*3*//*0*/-3.761, /*1*/-3.863, /*2*/-3.865, /*3*/-3.83, /*4*/-3.831, /*5*/-3.931, /*6*/-3.935, /*7*/-3.896, /*8*/-3.829, /*9*/-3.934, /*10*/-3.931, /*11*/-3.862, /*12*/-3.863, /*13*/-5.622, /*14*/-5.245, /*15*/-5.139, /*16*/-5.208, /*17*/1.69, /*18*/2.828, /*19*/2.726, /*20*/2.827, /*21*/2.726, /*22*/2.828, /*23*/2.758, /*24*/2.828, /*25*/2.759, /*26*/2.828, /*27*/2.758, /*28*/2.828, /*29*/2.759, /*30*/2.828, /*31*/2.759, /*32*/2.829, /*33*/2.725, /*34*/2.795},
{/*4*//*0*/-8.311, /*1*/-8.357, /*2*/-8.361, /*3*/-8.315, /*4*/-8.441, /*5*/-8.273, /*6*/-8.357, /*7*/-8.311, /*8*/-8.357, /*9*/-8.277, /*10*/-8.269, /*11*/-8.235, /*12*/-8.403, /*13*/-8.273, /*14*/-8.353, /*15*/-8.319, /*16*/-5.84, /*17*/-3.361, /*18*/-3.316, /*19*/1.427, /*20*/1.427, /*21*/1.427, /*22*/1.427, /*23*/1.427, /*24*/1.427, /*25*/1.427, /*26*/1.427, /*27*/1.386, /*28*/1.427, /*29*/1.427, /*30*/1.428, /*31*/1.302, /*32*/1.427, /*33*/1.301, /*34*/0.251},
{/*5*//*0*/-10.588, /*1*/-10.588, /*2*/-10.538, /*3*/-10.594, /*4*/-10.599, /*5*/-10.495, /*6*/-10.588, /*7*/-10.445, /*8*/-10.445, /*9*/-10.495, /*10*/-10.451, /*11*/-10.594, /*12*/-10.495, /*13*/-10.439, /*14*/-10.247, /*15*/-9.455, /*16*/-8.168, /*17*/-8.271, /*18*/-8.213, /*19*/-0.148, /*20*/-0.148, /*21*/0.643, /*22*/0.545, /*23*/0.841, /*24*/0.792, /*25*/0.742, /*26*/0.544, /*27*/0.594, /*28*/0.741, /*29*/0.594, /*30*/0.742, /*31*/0.544, /*32*/0.693, /*33*/0.544, /*34*/0.297},
{/*6*//*0*/-11.634, /*1*/-11.62, /*2*/-11.57, /*3*/-11.684, /*4*/-11.741, /*5*/-11.57, /*6*/-11.513, /*7*/-11.563, /*8*/-11.627, /*9*/-11.62, /*10*/-11.627, /*11*/-11.62, /*12*/-11.627, /*13*/-11.62, /*14*/-11.221, /*15*/-10.544, /*16*/-9.575, /*17*/-8.321, /*18*/-8.326, /*19*/-8.606, /*20*/-1.993, /*21*/-0.171, /*22*/0.0, /*23*/-0.113, /*24*/0.056, /*25*/0.0, /*26*/0.0, /*27*/-0.113, /*28*/0.0, /*29*/0.0, /*30*/-0.056, /*31*/0.0, /*32*/-0.113, /*33*/0.0, /*34*/0.455},
{/*7*//*0*/-12.958, /*1*/-12.903, /*2*/-13.032, /*3*/-12.958, /*4*/-12.967, /*5*/-12.893, /*6*/-12.893, /*7*/-12.893, /*8*/-12.884, /*9*/-12.802, /*10*/-13.022, /*11*/-12.967, /*12*/-12.977, /*13*/-13.087, /*14*/-12.571, /*15*/-12.258, /*16*/-12.451, /*17*/-12.137, /*18*/-9.225, /*19*/-6.322, /*20*/-6.382, /*21*/-6.58, /*22*/-0.774, /*23*/-0.774, /*24*/-0.709, /*25*/-0.838, /*26*/-0.774, /*27*/-0.645, /*28*/-0.709, /*29*/-0.838, /*30*/-0.774, /*31*/-0.708, /*32*/-0.774, /*33*/-0.774, /*34*/0.58},
{/*8*//*0*/-14.76, /*1*/-14.532, /*2*/-14.699, /*3*/-14.904, /*4*/-14.76, /*5*/-14.831, /*6*/-14.771, /*7*/-14.616, /*8*/-14.676, /*9*/-14.843, /*10*/-14.616, /*11*/-14.904, /*12*/-14.82, /*13*/-14.699, /*14*/-14.051, /*15*/-14.051, /*16*/-12.877, /*17*/-11.223, /*18*/-10.727, /*19*/-8.776, /*20*/-7.776, /*21*/-6.263, /*22*/-1.296, /*23*/-1.369, /*24*/-1.366, /*25*/-1.511, /*26*/-1.366, /*27*/-1.366, /*28*/-1.366, /*29*/-1.44, /*30*/-1.366, /*31*/-1.44, /*32*/-1.15, /*33*/-1.511, /*34*/0.432},
{/*9*//*0*/-15.503, /*1*/-15.835, /*2*/-15.634, /*3*/-15.503, /*4*/-15.662, /*5*/-15.437, /*6*/-15.583, /*7*/-15.596, /*8*/-15.489, /*9*/-15.489, /*10*/-15.648, /*11*/-15.755, /*12*/-15.503, /*13*/-15.596, /*14*/-15.119, /*15*/-14.708, /*16*/-13.968, /*17*/-13.992, /*18*/-14.084, /*19*/-10.344, /*20*/-8.984, /*21*/-8.109, /*22*/-8.022, /*23*/-1.908, /*24*/-1.828, /*25*/-1.908, /*26*/-1.75, /*27*/-1.75, /*28*/-1.828, /*29*/-1.908, /*30*/-1.75, /*31*/-1.827, /*32*/-2.067, /*33*/-1.908, /*34*/0.477},
{/*10*//*0*/-16.332, /*1*/-16.102, /*2*/-16.189, /*3*/-16.276, /*4*/-16.102, /*5*/-16.173, /*6*/-16.071, /*7*/-15.81, /*8*/-16.466, /*9*/-16.102, /*10*/-16.102, /*11*/-15.652, /*12*/-16.26, /*13*/-16.173, /*14*/-15.913, /*15*/-15.739, /*16*/-15.565, /*17*/-15.565, /*18*/-13.391, /*19*/-13.117, /*20*/-9.043, /*21*/-8.87, /*22*/-9.139, /*23*/-3.481, /*24*/-3.052, /*25*/-2.785, /*26*/-2.872, /*27*/-2.571, /*28*/-2.695, /*29*/-2.608, /*30*/-2.782, /*31*/-3.049, /*32*/-2.782, /*33*/-2.695, /*34*/0.521},
{/*11*//*0*/-15.943, /*1*/-16.165, /*2*/-16.054, /*3*/-16.149, /*4*/-16.054, /*5*/-16.26, /*6*/-16.088, /*7*/-16.054, /*8*/-16.071, /*9*/-16.054, /*10*/-16.26, /*11*/-16.149, /*12*/-16.149, /*13*/-16.26, /*14*/-16.182, /*15*/-16.054, /*16*/-16.277, /*17*/-14.763, /*18*/-14.622, /*19*/-12.83, /*20*/-12.641, /*21*/-10.682, /*22*/-9.594, /*23*/-5.962, /*24*/-3.497, /*25*/-3.214, /*26*/-3.116, /*27*/-3.399, /*28*/-3.071, /*29*/-3.21, /*30*/-3.217, /*31*/-3.025, /*32*/-3.217, /*33*/-3.068, /*34*/0.662},
{/*12*//*0*/-15.918, /*1*/-15.492, /*2*/-15.594, /*3*/-15.714, /*4*/-15.629, /*5*/-15.9, /*6*/-15.594, /*7*/-15.816, /*8*/-15.816, /*9*/-15.629, /*10*/-15.798, /*11*/-15.696, /*12*/-15.492, /*13*/-15.696, /*14*/-15.492, /*15*/-15.492, /*16*/-15.204, /*17*/-14.864, /*18*/-14.591, /*19*/-13.877, /*20*/-13.076, /*21*/-13.061, /*22*/-9.081, /*23*/-8.052, /*24*/-5.365, /*25*/-3.771, /*26*/-3.917, /*27*/-3.571, /*28*/-3.886, /*29*/-3.673, /*30*/-3.669, /*31*/-3.571, /*32*/-3.877, /*33*/-3.636, /*34*/-3.771},
{/*13*//*0*/-15.456, /*1*/-15.237, /*2*/-15.218, /*3*/-15.785, /*4*/-15.328, /*5*/-15.347, /*6*/-15.27, /*7*/-15.437, /*8*/-15.437, /*9*/-15.237, /*10*/-15.071, /*11*/-15.291, /*12*/-15.456, /*13*/-15.237, /*14*/-15.36, /*15*/-15.109, /*16*/-15.328, /*17*/-17.158, /*18*/-13.248, /*19*/-13.905, /*20*/-13.795, /*21*/-13.795, /*22*/-10.266, /*23*/-9.404, /*24*/-7.007, /*25*/-3.894, /*26*/-3.936, /*27*/-4.051, /*28*/-3.941, /*29*/-4.16, /*30*/-3.786, /*31*/-3.444, /*32*/-3.832, /*33*/-3.804, /*34*/-3.718},
{/*14*//*0*/-15.117, /*1*/-15.448, /*2*/-15.448, /*3*/-15.214, /*4*/-15.234, /*5*/-15.331, /*6*/-15.134, /*7*/-15.311, /*8*/-15.448, /*9*/-17.148, /*10*/-15.194, /*11*/-15.565, /*12*/-14.941, /*13*/-15.311, /*14*/-15.448, /*15*/-15.214, /*16*/-15.077, /*17*/-14.961, /*18*/-14.648, /*19*/-13.846, /*20*/-13.593, /*21*/-12.89, /*22*/-10.312, /*23*/-10.519, /*24*/-9.713, /*25*/-9.713, /*26*/-4.33, /*27*/-4.33, /*28*/-5.734, /*29*/-4.213, /*30*/-4.523, /*31*/-4.186, /*32*/-4.313, /*33*/-4.447, /*34*/0.585},
{/*15*//*0*/-16.565, /*1*/-14.544, /*2*/-14.833, /*3*/-14.315, /*4*/-14.584, /*5*/-14.419, /*6*/-14.439, /*7*/-13.798, /*8*/-14.419, /*9*/-14.295, /*10*/-14.439, /*11*/-14.439, /*12*/-14.459, /*13*/-13.864, /*14*/-14.709, /*15*/-14.668, /*16*/-13.817, /*17*/-14.439, /*18*/-14.584, /*19*/-13.741, /*20*/-13.462, /*21*/-13.088, /*22*/-12.0, /*23*/-9.944, /*24*/-9.958, /*25*/-7.831, /*26*/-5.726, /*27*/-5.228, /*28*/-4.226, /*29*/-4.226, /*30*/-4.481, /*31*/-4.605, /*32*/-4.475, /*33*/-4.542, /*34*/0.871},
{/*16*//*0*/-13.856, /*1*/-13.215, /*2*/-13.328, /*3*/-13.064, /*4*/-13.44, /*5*/-12.8, /*6*/-13.208, /*7*/-13.177, /*8*/-13.254, /*9*/-13.367, /*10*/-12.952, /*11*/-13.348, /*12*/-13.196, /*13*/-12.951, /*14*/-13.304, /*15*/-14.494, /*16*/-13.592, /*17*/-13.177, /*18*/-13.624, /*19*/-13.612, /*20*/-13.004, /*21*/-12.085, /*22*/-12.272, /*23*/-10.769, /*24*/-8.403, /*25*/-10.43, /*26*/-6.598, /*27*/-4.75, /*28*/-5.022, /*29*/-4.266, /*30*/-5.41, /*31*/-4.682, /*32*/-4.75, /*33*/0.527, /*34*/0.527},
{/*17*//*0*/-12.638, /*1*/-12.837, /*2*/-12.697, /*3*/-12.697, /*4*/-13.395, /*5*/-12.697, /*6*/-10.588, /*7*/-12.857, /*8*/-15.187, /*9*/-12.697, /*10*/-12.678, /*11*/-12.956, /*12*/-12.976, /*13*/-13.116, /*14*/-12.418, /*15*/-11.301, /*16*/-12.697, /*17*/-13.116, /*18*/-12.956, /*19*/-13.095, /*20*/-11.164, /*21*/-15.022, /*22*/-11.581, /*23*/-8.498, /*24*/-10.62, /*25*/-9.667, /*26*/-10.588, /*27*/-5.31, /*28*/-4.894, /*29*/-5.17, /*30*/-5.294, /*31*/-3.948, /*32*/-5.294, /*33*/-5.162, /*34*/-5.581},
{/*18*//*0*/-12.398, /*1*/-12.647, /*2*/-12.352, /*3*/-12.154, /*4*/-12.373, /*5*/-12.352, /*6*/-12.067, /*7*/-12.647, /*8*/-12.279, /*9*/-12.185, /*10*/-12.185, /*11*/-12.647, /*12*/-12.332, /*13*/-12.626, /*14*/-12.332, /*15*/-12.352, /*16*/-12.626, /*17*/-13.36, /*18*/-12.857, /*19*/-12.941, /*20*/-12.773, /*21*/-12.332, /*22*/-9.705, /*23*/-10.605, /*24*/-10.495, /*25*/-9.983, /*26*/-8.352, /*27*/-5.894, /*28*/-6.019, /*29*/-5.735, /*30*/-4.713, /*31*/-5.882, /*32*/-5.872, /*33*/-6.47, /*34*/1.029},
{/*19*//*0*/-12.293, /*1*/-11.627, /*2*/-12.554, /*3*/-11.889, /*4*/-12.371, /*5*/-12.293, /*6*/-12.504, /*7*/-12.424, /*8*/-12.195, /*9*/-12.349, /*10*/-12.041, /*11*/-12.482, /*12*/-13.617, /*13*/-12.371, /*14*/-12.216, /*15*/-12.482, /*16*/-11.406, /*17*/-12.216, /*18*/-12.041, /*19*/-12.68, /*20*/-12.682, /*21*/-12.792, /*22*/-13.407, /*23*/-11.114, /*24*/-11.211, /*25*/-10.515, /*26*/-10.36, /*27*/-10.066, /*28*/-5.266, /*29*/-5.721, /*30*/-4.168, /*31*/-5.866, /*32*/-7.666, /*33*/-5.721, /*34*/1.049},
{/*20*//*0*/-12.787, /*1*/-13.135, /*2*/-12.486, /*3*/-12.625, /*4*/-12.162, /*5*/-12.81, /*6*/-12.625, /*7*/-12.424, /*8*/-12.346, /*9*/-12.926, /*10*/-12.561, /*11*/-12.464, /*12*/-12.625, /*13*/-12.162, /*14*/-12.464, /*15*/-12.302, /*16*/-12.857, /*17*/-12.561, /*18*/-13.135, /*19*/-12.926, /*20*/-13.273, /*21*/-13.221, /*22*/-13.111, /*23*/-11.486, /*24*/-12.14, /*25*/-10.197, /*26*/-10.421, /*27*/-7.607, /*28*/-6.162, /*29*/-5.827, /*30*/-5.675, /*31*/-5.625, /*32*/-5.189, /*33*/-6.462, /*34*/0.159},
{/*21*//*0*/-12.735, /*1*/-12.542, /*2*/-12.566, /*3*/-12.881, /*4*/-14.516, /*5*/-12.881, /*6*/-12.349, /*7*/-12.504, /*8*/-12.881, /*9*/-12.542, /*10*/-12.396, /*11*/-12.711, /*12*/-12.687, /*13*/-12.881, /*14*/-12.25, /*15*/-12.669, /*16*/-12.226, /*17*/-13.22, /*18*/-12.881, /*19*/-13.05, /*20*/-13.45, /*21*/-13.245, /*22*/-13.026, /*23*/-12.523, /*24*/-11.855, /*25*/-10.698, /*26*/-10.338, /*27*/-10.036, /*28*/-9.339, /*29*/-6.805, /*30*/-5.582, /*31*/-5.932, /*32*/-6.113, /*33*/-6.101, /*34*/1.318},
{/*22*//*0*/-12.542, /*1*/-12.578, /*2*/-12.73, /*3*/-12.426, /*4*/-12.781, /*5*/-12.757, /*6*/-13.084, /*7*/-12.73, /*8*/-17.746, /*9*/-12.607, /*10*/-12.176, /*11*/-13.136, /*12*/-12.709, /*13*/-13.261, /*14*/-12.755, /*15*/-13.261, /*16*/-12.61, /*17*/-12.603, /*18*/-12.094, /*19*/-13.996, /*20*/-13.438, /*21*/-15.984, /*22*/-12.562, /*23*/-12.578, /*24*/-11.846, /*25*/-10.785, /*26*/-11.161, /*27*/-10.255, /*28*/-6.365, /*29*/-6.011, /*30*/-6.568, /*31*/-6.188, /*32*/-6.011, /*33*/-6.352, /*34*/-6.176}
};

float getBaseAdvance(int rpm, float key) {
	// todo: use interpolation
	int rpm_index = findIndex(ad_rpm_table, AD_RPM_COUNT, rpm);
	rpm_index = max(rpm_index, 0);
	int maf_index = findIndex(ad_maf_table, AD_MAF_COUNT, key);
	maf_index = max(maf_index, 0);

	return ad_table[rpm_index][maf_index];
}

float getAdvance(int rpm, float key) {
	if(isCrankingR(rpm))
		return engineConfiguration->crankingChargeAngle;


	return getBaseAdvance(rpm, key) + engineConfiguration->ignitonOffset;
}
