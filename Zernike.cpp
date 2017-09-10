/*
 * Zernike.cpp
 *
 *  Created on: 25.08.2017
 *      Author: Patryk Kowalski
 */

#include "Zernike.h"
#include <iostream>
#include "bmp/EasyBMP.h"
#include <tgmath.h>
#include "Bitmap.h"
#define M_PI 3.14159265358979323846
Zernike::Zernike(int max_row, int max_col,double coeff, double (*ZernFunc)(double, double)) : DiffractiveStructure(max_row, max_col) {
	double max_bitmap_value = 0;
        for (double col = -MAX_COL/2; col < MAX_COL/2; col++){
		for (double row = -MAX_ROW/2; row < MAX_ROW/2; row++){
			bitmap->bmap[bitmap->index(row+MAX_ROW/2,col+MAX_COL/2)] = ZernFunc(row/(MAX_ROW/2), col/(MAX_COL/2));
			if (bitmap->bmap[bitmap->index(row+MAX_ROW/2,col+MAX_COL/2)]>max_bitmap_value) max_bitmap_value = bitmap->bmap[bitmap->index(row+MAX_ROW/2,col+MAX_COL/2)];
		}
	}
	bitmap->setMaxValue(max_bitmap_value);
        
        double tmp;
        for(int i = 0; i < MAX_ROW*MAX_COL; i++) {
            tmp = bitmap->bmap[i]*coeff/max_bitmap_value; //normalizacja do 1
            bitmap->bmap[i] = 2*M_PI*(tmp - floor(tmp));
/* floor(1) = 1. floor(ulamek) = 0. floor (ujemna - -1). wynik zawsze jest dodatni i jego wartosc % 2pi sie nii zmienia
 *
 */
        }

	bitmap->setMaxValue(2*M_PI);
}

Zernike::~Zernike() {}

double Z0(double x, double y){ //Piston
    (void)x; (void)y;
 return 1;
}
double Z1(double x, double y){ //Tilt in y direction
    (void)x;
	return y;
}
double Z2(double x, double y){ //Tilt in x direction
    (void)y;
	return x;
}
double Z3(double x, double y){ //Astigmatism with axis at +/- 45
	return 2*x*y;
}
double Z4(double x, double y){ //defocus (field curvature)
	return -1 + 2*pow(x,2) + 2*pow(y,2);
}
double Z5(double x, double y){ // Astigmatism with axis at 0 or 90
	return pow(x,2) - pow(y,2);
}
double Z6(double x, double y){ //
	return -pow(y,3) + 3*y*pow(x,2);
}
double Z7(double x, double y){ //Coma along x axis
	return 3*pow(y,3) + 3*pow(x,2)*y - 2*y;
}
double Z8(double x, double y){ //Coma along y axis
	return 3*pow(x,3) + 3*pow(y,2)*x - 2*x;
}
double Z9(double x, double y){ //
	return pow(x,3) - 3*x*pow(y,2);
}
double Z10(double x, double y){
	return 4*pow(x,3)*y - 4*pow(y,3)*x;
}
double Z11(double x, double y){ //secondary astigmatism
	return 8*pow(x,3)*y + 8*pow(y,3)*x -6*x*y;
}
double Z12(double x, double y){ //spherical aberration, defocus
	return 6*pow(x,4) + 6*pow(y,4) - 6*pow(x,2) - 6*pow(y,2) + 12*pow(x,2)*pow(y,2) + 1;
}
double Z13(double x, double y){ //secondary astigmatism
	return 4*pow(x,4) - 4*pow(y,4) - 3*pow(x,2) + 3*pow(y,2);
}
double Z14(double x, double y){
	return pow(x,4) + pow(y,4) - 6*pow(x,2)*pow(y,2);
}
double Z15(double x, double y){
	return pow(y,5) - 10*pow(x,2)*pow(y,3) + 5*pow(x,4)*y;
}
double Z16(double x, double y){
	return 15*pow(x,4)*y + 10*pow(x,2)*pow(y,3) - 12*pow(x,2)*y - 5*pow(y,5) + 4*pow(y,3);
}
double Z17(double x, double y){
	return 10*pow(x,4)*y + 20*pow(x,2)*pow(y,3) - 12*pow(x,2)*y + 10*pow(y,5) - 12*pow(y,3) + 3*y;
}
double Z18(double x, double y){
	return 10*pow(x,5) + 20*pow(y,2)*pow(x,3) - 12*pow(x,3) + 10*pow(y,4)*x - 12*x*pow(y,2) + 3*x;
}
double Z19(double x, double y){
	return 5*pow(x,5) - 10*pow(y,2)*pow(x,3) - 4*pow(x,3) - 15*x*pow(y,4) + 12*x*pow(y,2);
}
double Z20(double x, double y){
	return pow(x,5) - 10*pow(x,3)*pow(y,2) + 5*x*pow(y,4);
}
