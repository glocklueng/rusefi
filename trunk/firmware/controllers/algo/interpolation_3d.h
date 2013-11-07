/*
 *  Created on: Oct 17, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

/**
 * @file    interpolation_3d.h
 */


#ifndef INTERPOLATION_3D_H_
#define INTERPOLATION_3D_H_

float interpolate2d(float value, float bin[], float values[], int size);
float interpolate3d(float x, float xBin[], int xBinSize, float y, float yBin[], int yBinSize, float* map[]);

#endif /* INTERPOLATION_3D_H_ */
