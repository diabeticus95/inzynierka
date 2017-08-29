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
	int row_count, col_count;
	double* bmap; //sztuczka z indeksowaniem
	int index( int x, int y );
	void printMap();
	void generateImage();
	void setMaxValue(double max);

//	Bitmap(Bitmap bmap, double max_bitmap_value);
	Bitmap(int row_count, int col_count);
	virtual ~Bitmap();

private:
	int norm;
	double max_bitmap_value;
	int bit_depth;

};
Bitmap mergeMaps(Bitmap* a, Bitmap* b);
#endif /* BITMAP_H_ */
