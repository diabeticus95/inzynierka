/*
 * DiffractiveStructure.cpp
 *
 *  Created on: 01.09.2017
 *      Author: Patryk Kowalski
 */
#include "DiffractiveStructure.h"
#include "Bitmap.h"
#include "math.h"
#include <iostream>
#include <vector>



DiffractiveStructure::DiffractiveStructure(int max_row, int max_col)
	: MAX_ROW(max_row)
	, MAX_COL(max_col){
		bitmap = std::make_unique<Bitmap>(max_row, max_col);
}
int DiffractiveStructure::getRowCount(){
	return MAX_ROW;
}

int DiffractiveStructure::getColCount(){
	return MAX_COL;
}
Bitmap* DiffractiveStructure::returnBitmap(){
	return bitmap.get();
}
DiffractiveStructure::~DiffractiveStructure(){
	std::cerr<<"usunalem strukture"<<std::endl;
}

