/*
 * Zernike.h
 *
 *  Created on: 25.08.2017
 *      Author: Patryk Kowalski
 */

#ifndef ZERNIKE_H_
#define ZERNIKE_H_
#include "Bitmap.h"
class Zernike {
public:

	Zernike();
	virtual ~Zernike();

	Bitmap* returnBitmap();

private:
	double probkowanie;
	int MAX_ROW;
	int MAX_COL;
	int bit_depth;
	Bitmap* bitmap;

double Z0(int x,int y);
double Z1(int x,int y);
double Z2(int x,int y);
double Z3(int x,int y);
double Z4(int x,int y);
double Z5(int x,int y);
double Z6(int x,int y);
double Z7(int x,int y);
double Z8(int x,int y);
double Z9(int x,int y);
double Z10(int x,int y);
double Z11(int x,int y);
double Z12(int x,int y);
double Z13(int x,int y);
double Z14(int x,int y);

};

#endif /* ZERNIKE_H_ */
