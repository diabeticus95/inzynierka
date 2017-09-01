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
#include <math.h>
#include "Bitmap.h"
Zernike::Zernike(int max_row, int max_col,double coeff, double (*ZernFunc)(double, double)):DiffractiveStructure(max_row, max_col) {
	probkowanie = pow(10,5);
	double max_bitmap_value = 0;
	for (double row = -MAX_ROW/2; row < MAX_ROW/2; row++){
		for (double col = -MAX_COL/2; col < MAX_COL/2; col++){
			bitmap->bmap[bitmap->index(row+MAX_ROW/2,col+MAX_COL/2)] = ZernFunc(row/(MAX_ROW/2), col/(MAX_COL/2));
			if (bitmap->bmap[bitmap->index(row+MAX_ROW/2,col+MAX_COL/2)]>max_bitmap_value) max_bitmap_value = bitmap->bmap[bitmap->index(row+MAX_ROW/2,col+MAX_COL/2)];
		}
	}
	bitmap->setMaxValue(max_bitmap_value);
	// normalize to 2*pi, to make it compatibile with lens && deal with negatives
	// tu przemnoz n razy
	for (int row = 0; row < MAX_ROW; row++){
		for (int col = 0; col < MAX_COL; col++){
			bitmap->bmap[bitmap->index(row,col)] = coeff * bitmap->bmap[bitmap->index(row,col)]; //eksperyment
			bitmap->bmap[bitmap->index(row,col)] = (bitmap->bmap[bitmap->index(row,col)] * 2*M_PI/max_bitmap_value) + 4*M_PI;
			bitmap->bmap[bitmap->index(row,col)] = fmod(bitmap->bmap[bitmap->index(row,col)], 2*M_PI);
		}
	}
	bitmap->setMaxValue(2*M_PI);
}

Zernike::~Zernike() {
	delete bitmap;
}

double Z0(double x, double y){ //Piston
 return 1;
}
double Z1(double x, double y){ //Tilt in y direction
	return y;
}
double Z2(double x, double y){ //Tilt in x direction
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
