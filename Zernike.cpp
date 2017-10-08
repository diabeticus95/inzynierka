/*
 * Zernike.cpp
 *
 *  Created on: 25.08.2017
 *      Author: Patryk Kowalski
 */

#include "Zernike.h"
#include <iostream>
#include "bmp/EasyBMP.h"
#include <cmath>
#include "Bitmap.h"
Zernike::Zernike(int max_row, int max_col,double coeff, double (*ZernFunc)(double, double)) :
			DiffractiveStructure(max_row, max_col) {
	int MAX_ROW = bitmap->row_count/2;
	int MAX_COL = bitmap->col_count/2;
        for (int col = -MAX_COL; col < MAX_COL; col++){
        	for (int row = -MAX_ROW; row < MAX_ROW; row++){
                    double xx = (double)row/MAX_ROW, yy = (double)col/MAX_COL;
                    if( xx*xx + yy*yy > 1.0) {
                    	bitmap->bmap[bitmap->index(row+MAX_ROW,col+MAX_COL)] = 0;
                        continue;
                    }
		    bitmap->bmap[bitmap->index(row+MAX_ROW,col+MAX_COL)] = ZernFunc(xx, yy);
		}
	}
        double tmp; int size = bitmap->row_count*bitmap->col_count;
        for(int i = 0; i < size; i++) {
            tmp = bitmap->bmap[i]*coeff;
            bitmap->bmap[i] = (tmp - floor(tmp)); //modulo 1
        }
}

Zernike::~Zernike() {}

double Z0(double x, double y){ //Piston
    (void)x; (void)y;
 return 1;
}
double Z1(double x, double y){ //Tilt in y direction
    (void)x;
	return 2*y;
}
double Z2(double x, double y){ //Tilt in x direction
    (void)y;
	return 2*x;
}
double Z3(double x, double y){ //Astigmatism with axis at +/- 45
	return sqrt(6)*2*x*y;
}
double Z4(double x, double y){ //defocus (field curvature)
	return sqrt(3) * (-1 + 2*pow(x,2) + 2*pow(y,2));
}
double Z5(double x, double y){ // Astigmatism with axis at 0 or 90
	return sqrt(6)*(pow(x,2) - pow(y,2));
}
double Z6(double x, double y){ //
	return (2*sqrt(2))*(-pow(y,3) + 3*y*pow(x,2));
}
double Z7(double x, double y){ //Coma along x axis
//	return  (2*sqrt(2))*(3*pow(y,3) + 3*pow(x,2)*y - 2*y);
	return  (2*sqrt(2)) *y* (3*y*y + 3*x*x - 2); //optymalizacja mnozen; >0.9s -> <0.7s
//	return  (3*pow(y,3) + 3*pow(x,2)*y - 2*y);
}
double Z8(double x, double y){ //Coma along y axis
	return  (2*sqrt(2))*(3*pow(x,3) + 3*pow(y,2)*x - 2*x);
}
double Z9(double x, double y){ //
	return  (2*sqrt(2))*(pow(x,3) - 3*x*pow(y,2));
}
double Z10(double x, double y){
	return sqrt(10)*(4*pow(x,3)*y - 4*pow(y,3)*x);
}
double Z11(double x, double y){ //secondary astigmatism
	return sqrt(10)*(8*pow(x,3)*y + 8*pow(y,3)*x -6*x*y);
}
double Z12(double x, double y){ //spherical aberration, defocus
	return sqrt(5)*(6*pow(x,4) + 6*pow(y,4) - 6*pow(x,2) - 6*pow(y,2) + 12*pow(x,2)*pow(y,2) + 1);
}
double Z13(double x, double y){ //secondary astigmatism
	return sqrt(10)*(4*pow(x,4) - 4*pow(y,4) - 3*pow(x,2) + 3*pow(y,2));
}
double Z14(double x, double y){
	return sqrt(10)*(pow(x,4) + pow(y,4) - 6*pow(x,2)*pow(y,2));
}
double Z15(double x, double y){
	return (2*sqrt(3))*y*((y*y - 10*x*x)*y*y + 5*pow(x,4)); // poprawa czasu z ~1.2s na 0.8s
	//return (2*sqrt(3))*(pow(y,5) - 10*pow(x,2)*pow(y,3) + 5*pow(x,4)*y);
}
double Z16(double x, double y){
	return (2*sqrt(3))*(15*pow(x,4)*y + 10*pow(x,2)*pow(y,3) - 12*pow(x,2)*y - 5*pow(y,5) + 4*pow(y,3));
}
double Z17(double x, double y){
	return (2*sqrt(3))*(10*pow(x,4)*y + 20*pow(x,2)*pow(y,3) - 12*pow(x,2)*y + 10*pow(y,5) - 12*pow(y,3) + 3*y);
}
double Z18(double x, double y){
	return (2*sqrt(3))*(10*pow(x,5) + 20*pow(y,2)*pow(x,3) - 12*pow(x,3) + 10*pow(y,4)*x - 12*x*pow(y,2) + 3*x);
}
double Z19(double x, double y){
	return (2*sqrt(3))*(5*pow(x,5) - 10*pow(y,2)*pow(x,3) - 4*pow(x,3) - 15*x*pow(y,4) + 12*x*pow(y,2));
}
double Z20(double x, double y){
	return (2*sqrt(3))*(pow(x,5) - 10*pow(x,3)*pow(y,2) + 5*x*pow(y,4));
}
