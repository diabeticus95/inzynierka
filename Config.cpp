/*
 * Config.cpp
 *
 *  Created on: 28.08.2017
 *      Author: Patryk Kowalski
 */

#include "Config.h"

Config::Config() {
	probkowanie = pow(10,5);
	lambda = 632.8*0.000000001 * probkowanie;
	k = 2*M_PI/lambda;
	bit_depth = 24;
	f = 1 * probkowanie;
	coeff = (double)k/(2*f);
	MAX_ROW = 2048;
	MAX_COL = 2048;
}

