/*
 * Lens.h
 *
 *  Created on: 25.08.2017
 *      Author: Patryk Kowalski
 */

#ifndef LENS_H_
#define LENS_H_
#include "Bitmap.h"
#include "DiffractiveStructure.h"

class Lens : public DiffractiveStructure {
public:
	Lens(int max_row, int max_col, double probkowanie);
	virtual ~Lens();

private:
	double probkowanie;
	double lambda;
	double k;
	int f;
	double coeff;
	double max_bitmap_value;
};

#endif /* LENS_H_ */
