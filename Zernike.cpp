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
	MAX_ROW = 2048;
	MAX_COL = 2048;
	bitmap = new Bitmap(MAX_ROW, MAX_COL);
	double max_bitmap_value = 0;
	for (double row = -MAX_ROW/2; row < MAX_ROW/2; row++){
		for (double col = -MAX_COL/2; col < MAX_COL/2; col++){
//			bitmap->bmap[bitmap->index(row+MAX_ROW/2,col+MAX_COL/2)] = row/(MAX_ROW/2);
			bitmap->bmap[bitmap->index(row+MAX_ROW/2,col+MAX_COL/2)] = pow(row/1024,2) - pow(col/1024,2);
//			bitmap->bmap[bitmap->index(row+MAX_ROW/2,col+MAX_COL/2)] = row+1;
			if (bitmap->bmap[bitmap->index(row+MAX_ROW/2,col+MAX_COL/2)]>max_bitmap_value) max_bitmap_value = bitmap->bmap[bitmap->index(row+MAX_ROW/2,col+MAX_COL/2)];
		}
	}
	bitmap->setMaxValue(max_bitmap_value);
	// normalize to 2*pi, to make it compatibile with lens && deal with negatives
	for (int row = 0; row < MAX_ROW; row++){
		for (int col = 0; col < MAX_COL; col++){
			bitmap->bmap[bitmap->index(row,col)] = (bitmap->bmap[bitmap->index(row,col)] * 2*M_PI/max_bitmap_value) + 4*M_PI;
			bitmap->bmap[bitmap->index(row,col)] = fmod(bitmap->bmap[bitmap->index(row,col)], 2*M_PI);
		}
	}
	bitmap->setMaxValue(2*M_PI);
}

Zernike::~Zernike() {
	delete bitmap;
}

Bitmap* Zernike::returnBitmap(){
	return bitmap;
}
