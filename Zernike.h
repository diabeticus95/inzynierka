/*
 * Zernike.h
 *
 *  Created on: 25.08.2017
 *      Author: Patryk Kowalski
 */

#ifndef ZERNIKE_H_
#define ZERNIKE_H_
#include "Bitmap.h"
#include "DiffractiveStructure.h"
class Zernike : public DiffractiveStructure {
public:
	Zernike(int max_row, int max_col,double coeff, double (*ZernFunc)(double, double));
	virtual ~Zernike();
};
double Z0(double x, double y);
double Z1(double x, double y);
double Z2(double x, double y);
double Z3(double x, double y);
double Z4(double x, double y);
double Z5(double x,double y);
double Z6(double x, double y);
double Z7(double x, double y);
double Z8(double x, double y);
double Z9(double x, double y);
double Z10(double x, double y);
double Z11(double x, double y);
double Z12(double x, double y);
double Z13(double x, double y);
double Z14(double x, double y);
double Z15(double x, double y);
double Z16(double x, double y);
double Z17(double x, double y);
double Z18(double x, double y);
double Z19(double x, double y);
double Z20(double x, double y);
#endif /* ZERNIKE_H_ */
