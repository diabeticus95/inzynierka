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
Zernike::Zernike() {
	probkowanie = pow(10,5);
	MAX_ROW = 64;
	MAX_COL = 64;
	bitmap = new Bitmap(MAX_ROW, MAX_COL);
	double max_bitmap_value = 0;
	for (int row = -MAX_ROW/2; row < MAX_ROW/2; row++){
			for (int col = -MAX_COL/2; col < MAX_COL/2; col++){
				bitmap->bmap[bitmap->index(row+MAX_ROW/2,col+MAX_COL/2)] = fmod(2*row*col,2*2048*2048);
//				std::cout<<"row: "<<row<<"col: "<<col<<"  "<<"value: "<<bitmap->bmap[bitmap->index(row+MAX_ROW/2,col+MAX_COL/2)]<<std::endl;
				if (bitmap->bmap[bitmap->index(row+MAX_COL/2,col+MAX_COL/2)]>max_bitmap_value) max_bitmap_value = bitmap->bmap[bitmap->index(row,col)];
			}
	}
	bitmap->setMaxValue(max_bitmap_value);
}

Zernike::~Zernike() {
}

Bitmap* Zernike::returnBitmap(){
	return bitmap;
}
