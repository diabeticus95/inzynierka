/*
 * Lens.h
 *
 *  Created on: 25.08.2017
 *      Author: Patryk Kowalski
 */

#ifndef LENS_H_
#define LENS_H_
#include "Bitmap.h"
class Lens {
public:
	Lens();
	virtual ~Lens();

	Bitmap* returnBitmap();

private:
	double probkowanie;
	double lambda;
	double k;
	int bit_depth;
	int f;
	double coeff;
	int MAX_ROW;
	int MAX_COL;
	Bitmap* bitmap;
	int norm;
	double max_bitmap_value;
};

#endif /* LENS_H_ */
