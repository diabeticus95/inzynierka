/*
 * DiffractiveStructure.h
 *
 *  Created on: 01.09.2017
 *      Author: Patryk Kowalski
 */
#ifndef DIFFRACTIVESTRUCTURE_H_
#define DIFFRACTIVESTRUCTURE_H_
#include "Bitmap.h"

class DiffractiveStructure {
public:
	DiffractiveStructure(int max_row, int max_col);
	virtual ~DiffractiveStructure();
	Bitmap* returnBitmap();
	int getRowCount();
	int getColCount();
protected:
	Bitmap* bitmap;
	int MAX_ROW;
	int MAX_COL;
};
//DiffractiveStructure::~DiffractiveStructure() {}
Bitmap* mergeMaps(Bitmap* a, Bitmap* b);
#endif
