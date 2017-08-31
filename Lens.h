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
	Lens(int max_row, int max_col);
	virtual ~Lens();

	Bitmap* returnBitmap();

private:
	double probkowanie;
	double lambda;
	double k;
	int f;
	double coeff;
	int MAX_ROW;
	int MAX_COL;
	Bitmap* bitmap;
	double max_bitmap_value;
};

#endif /* LENS_H_ */
