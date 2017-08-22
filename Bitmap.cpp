/*
 * Bitmap.cpp
 *
 *  Created on: 03.08.2017
 *      Author: Patryk Kowalski
 */

#include "Bitmap.h"

Bitmap::Bitmap(int row_count, int col_count) {
	this->row_count = row_count;
	this->col_count = col_count;
	bmap = new double[row_count * col_count];
}

Bitmap::~Bitmap() {

}
int Bitmap::index(int x, int y ){
	 return x + col_count * y;
}

