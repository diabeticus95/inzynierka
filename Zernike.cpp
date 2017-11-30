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
Zernike::Zernike(int max_row, int max_col,double Coeff, double (*ZernFunc)(double, double)) :
			DiffractiveStructure(max_row, max_col),
			coeff(Coeff){
	int MAX_ROW = bitmap->row_count;
	int MAX_COL = bitmap->col_count;
        for (double col = -MAX_COL/2; col < MAX_COL/2; col++){
        	for (double row = -MAX_ROW/2; row < MAX_ROW/2; row++){
                    if( (pow(row/(MAX_ROW/2),2) + pow(col/(MAX_COL/2),2)) > 1.0 ) {
                    	bitmap->bmap[bitmap->index(row+MAX_ROW/2,col+MAX_COL/2)] = 0;
                        continue;
                    }
			bitmap->bmap[bitmap->index(row+MAX_ROW/2,col+MAX_COL/2)] = ZernFunc(row/(MAX_ROW/2), col/(MAX_COL/2));
		}
	}
        double tmp;
        for(int i = 0; i < MAX_ROW*MAX_COL; i++) {
            tmp = bitmap->bmap[i]*coeff;
            bitmap->bmap[i] = (tmp - floor(tmp)); //modulo 1
        }
}
Zernike::Zernike(Bitmap &bitmapOuter) :
			DiffractiveStructure(bitmapOuter.row_count, bitmapOuter.col_count){
	bitmap.reset(&bitmapOuter);
}

Zernike::~Zernike() {
	std::cerr<<"usuwam zernike o wspolczynniku"<<coeff<<std::endl;
}

double Zernike::Z0(double x, double y){ //Piston
    (void)x; (void)y;
 return 1;
}
double Zernike::Z1(double x, double y){ //Tilt in y direction
    (void)x;
	return 2*y;
}
double Zernike::Z2(double x, double y){ //Tilt in x direction
    (void)y;
	return 2*x;
}
double Zernike::Z3(double x, double y){ //Astigmatism with axis at +/- 45
	return sqrt(6)*2*x*y;
}
double Zernike::Z4(double x, double y){ //defocus (field curvature)
	return sqrt(3) * (-1 + 2*pow(x,2) + 2*pow(y,2));
}
double Zernike::Z5(double x, double y){ // Astigmatism with axis at 0 or 90
	return sqrt(6)*(pow(x,2) - pow(y,2));
}
double Zernike::Z6(double x, double y){ //
	return (2*sqrt(2))*(-pow(y,3) + 3*y*pow(x,2));
}
double Zernike::Z7(double x, double y){ //Coma along x axis
	return  (2*sqrt(2))*(3*pow(y,3) + 3*pow(x,2)*y - 2*y);
//	return  (3*pow(y,3) + 3*pow(x,2)*y - 2*y);
}
double Zernike::Z8(double x, double y){ //Coma along y axis
	return  (2*sqrt(2))*(3*pow(x,3) + 3*pow(y,2)*x - 2*x);
}
double Zernike::Z9(double x, double y){ //
	return  (2*sqrt(2))*(pow(x,3) - 3*x*pow(y,2));
}
double Zernike::Z10(double x, double y){
	return sqrt(10)*(4*pow(x,3)*y - 4*pow(y,3)*x);
}
double Zernike::Z11(double x, double y){ //secondary astigmatism
	return sqrt(10)*(8*pow(x,3)*y + 8*pow(y,3)*x -6*x*y);
}
double Zernike::Z12(double x, double y){ //spherical aberration, defocus
	return sqrt(5)*(6*pow(x,4) + 6*pow(y,4) - 6*pow(x,2) - 6*pow(y,2) + 12*pow(x,2)*pow(y,2) + 1);
}
double Zernike::Z13(double x, double y){ //secondary astigmatism
	return sqrt(10)*(4*pow(x,4) - 4*pow(y,4) - 3*pow(x,2) + 3*pow(y,2));
}
double Zernike::Z14(double x, double y){
	return sqrt(10)*(pow(x,4) + pow(y,4) - 6*pow(x,2)*pow(y,2));
}
double Zernike::Z15(double x, double y){
	return (2*sqrt(3))*(pow(y,5) - 10*pow(x,2)*pow(y,3) + 5*pow(x,4)*y);
}
double Zernike::Z16(double x, double y){
	return (2*sqrt(3))*(15*pow(x,4)*y + 10*pow(x,2)*pow(y,3) - 12*pow(x,2)*y - 5*pow(y,5) + 4*pow(y,3));
}
double Zernike::Z17(double x, double y){
	return (2*sqrt(3))*(10*pow(x,4)*y + 20*pow(x,2)*pow(y,3) - 12*pow(x,2)*y + 10*pow(y,5) - 12*pow(y,3) + 3*y);
}
double Zernike::Z18(double x, double y){
	return (2*sqrt(3))*(10*pow(x,5) + 20*pow(y,2)*pow(x,3) - 12*pow(x,3) + 10*pow(y,4)*x - 12*x*pow(y,2) + 3*x);
}
double Zernike::Z19(double x, double y){
	return (2*sqrt(3))*(5*pow(x,5) - 10*pow(y,2)*pow(x,3) - 4*pow(x,3) - 15*x*pow(y,4) + 12*x*pow(y,2));
}
double Zernike::Z20(double x, double y){
	return (2*sqrt(3))*(pow(x,5) - 10*pow(x,3)*pow(y,2) + 5*x*pow(y,4));
}
