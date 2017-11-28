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
private:
	int counter;
public:
	Zernike(int max_row, int max_col,double coeff, double (*ZernFunc)(double, double));
	Zernike(Bitmap &bitmapOuter);
	virtual ~Zernike();
	int getCounter();
	void setCounter();
	static double Z0(double x, double y);
	static double Z1(double x, double y);
	static double Z2(double x, double y);
	static double Z3(double x, double y);
	static double Z4(double x, double y);
	static double Z5(double x,double y);
	static double Z6(double x, double y);
	static double Z7(double x, double y);
	static double Z8(double x, double y);
	static double Z9(double x, double y);
	static double Z10(double x, double y);
	static double Z11(double x, double y);
	static double Z12(double x, double y);
	static double Z13(double x, double y);
	static double Z14(double x, double y);
	static double Z15(double x, double y);
	static double Z16(double x, double y);
	static double Z17(double x, double y);
	static double Z18(double x, double y);
	static double Z19(double x, double y);
	static double Z20(double x, double y);
};

#endif /* ZERNIKE_H_ */
