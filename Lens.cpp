/*
 * Lens.cpp
 *
 *  Created on: 25.08.2017
 *      Author: Patryk Kowalski
 */

#include "Lens.h"
#include <iostream>
#include <tgmath.h>
#include <math.h>
#include "Bitmap.h"
Lens::Lens() {
	probkowanie = pow(10,5);
	lambda = 632.8*0.000000001 * probkowanie;
	k = 2*M_PI/lambda;
	f = 1 * probkowanie;
	coeff = (double)k/(2*f);
	MAX_ROW = 2048;
	MAX_COL = 2048;
	bitmap = new Bitmap(MAX_ROW, MAX_COL);
	max_bitmap_value = 0;

	for (int row = -MAX_ROW/2; row < MAX_ROW/2; row++){
			for (int col = -MAX_COL/2; col < MAX_COL/2; col++){
				// w przyblizeniu przyosiowym
			bitmap->bmap[bitmap->index(row+MAX_COL/2,col+MAX_COL/2)] = fmod(coeff*(pow(row,2) + pow(col,2)),2*M_PI);
			if (bitmap->bmap[bitmap->index(row+MAX_COL/2,col+MAX_COL/2)]>max_bitmap_value) max_bitmap_value = bitmap->bmap[bitmap->index(row,col)];
			}
	}
	bitmap->setMaxValue(max_bitmap_value);
}
Lens::~Lens() {
	// TODO Auto-generated destructor stub
}

Bitmap* Lens::returnBitmap(){
	return bitmap;
}
