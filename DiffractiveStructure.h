/*
 * DiffractiveStructure.h
 *
 *  Created on: 01.09.2017
 *      Author: Patryk Kowalski
 */
#ifndef DIFFRACTIVESTRUCTURE_H_
#define DIFFRACTIVESTRUCTURE_H_
#include <vector>
#include <memory>

class Bitmap;
class DiffractiveStructure {
public:
	DiffractiveStructure(int max_row, int max_col);
	virtual ~DiffractiveStructure();
	Bitmap* returnBitmap();
	int getRowCount();
	int getColCount();
protected:
	std::unique_ptr<Bitmap> bitmap;
	int MAX_ROW;
	int MAX_COL;
};

#endif
