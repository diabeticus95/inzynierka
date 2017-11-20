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
	Lens(int max_row, int max_col, double Lambda, double F, double probkowanie, double (*LensForm)(double, double, double));
	virtual ~Lens();
	static double paraxial_formula(double x, double y, double f);
	static double non_paraxial_formula(double x, double y,  double f);

private:
	double probkowanie;
	double lambda;
	double f;
	double coeff;
//	double max_bitmap_value;
};

#endif /* LENS_H_ */
