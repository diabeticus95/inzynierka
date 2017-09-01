/*
 * DiffractiveStructure.cpp
 *
 *  Created on: 01.09.2017
 *      Author: Patryk Kowalski
 */
#include "DiffractiveStructure.h"
#include "Bitmap.h"
#include "math.h"

Bitmap* mergeMaps(DiffractiveStructure a, DiffractiveStructure b){
	for (int row = 0; row < a.getRowCount(); row++){
			for (int col = 0; col < a.getColCount(); col++){
				a.returnBitmap()->bmap[a.returnBitmap()->index(row,col)] = fmod(a.returnBitmap()->bmap[a.returnBitmap()->index(row,col)] + b.returnBitmap()->bmap[b.returnBitmap()->index(row,col)],2*M_PI);
			}
	}
	a.returnBitmap()->setMaxValue(2*M_PI);
	return a.returnBitmap();
}

DiffractiveStructure::DiffractiveStructure(int max_row, int max_col):MAX_ROW(max_row), MAX_COL(max_col){
	bitmap = new Bitmap(max_row, max_col);
}
int DiffractiveStructure::getRowCount(){
	return MAX_ROW;
}

int DiffractiveStructure::getColCount(){
	return MAX_COL;
}
Bitmap* DiffractiveStructure::returnBitmap(){
	return bitmap;
}
DiffractiveStructure::~DiffractiveStructure(){
	delete bitmap;
}

