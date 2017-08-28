/*
 * Bitmap.h
 *
 *  Created on: 03.08.2017
 *      Author: Patryk Kowalski
 */

#ifndef BITMAP_H_
#define BITMAP_H_

class Bitmap {
public:
	double* bmap; //sztuczka z indeksowaniem
	int index( int x, int y );
	void printMap();

	Bitmap(int row_count, int col_count);
	virtual ~Bitmap();

private:
	int row_count, col_count;


};

#endif /* BITMAP_H_ */
