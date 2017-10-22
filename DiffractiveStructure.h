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
protected:
	std::unique_ptr<Bitmap> bitmap;
};

#endif
