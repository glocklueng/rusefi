/*
 *  Created on: Oct 17, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

/**
 * @file    interpolation_3d.h
 */


#ifndef INTERPOLATION_3D_H_
#define INTERPOLATION_3D_H_

float interpolate3d(int rpm, float y, float rpmBin[], int rpmBinSize, float yBin[], int yBinSize, float* map[]);

#endif /* INTERPOLATION_3D_H_ */
