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
	void generateImage();
	void setMaxValue(double max);

//	Bitmap(Bitmap bmap, double max_bitmap_value);
	Bitmap(int row_count, int col_count);
	virtual ~Bitmap();

private:
	int row_count, col_count;
	int norm;
	double max_bitmap_value;
	int bit_depth;

};

#endif /* BITMAP_H_ */
