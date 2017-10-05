/*
 * Bitmap.h
 *
 *  Created on: 03.08.2017
 *      Author: Patryk Kowalski
 */

#ifndef BITMAP_H_
#define BITMAP_H_
#include <vector>
#include <memory>
#include "fftw/fftw3.h"
class DiffractiveStructure;


class Bitmap {
public:
	int row_count, col_count;
	std::unique_ptr<double[]> bmap; //sztuczka z indeksowaniem
	int index( int x, int y ) const;
	void printMap();
	void printMap(char* fileName);
	void generateImage(char* filename);
	void mergeMaps(std::vector<DiffractiveStructure*> &toMerge);

	Bitmap(int row_count, int col_count);
	Bitmap(const Bitmap &);
	Bitmap& operator=(const Bitmap &b);
	virtual ~Bitmap();

private:
	double norm;
	int bit_depth;

};
void outerMergeMaps(DiffractiveStructure* a, DiffractiveStructure* b);
Bitmap fft(const Bitmap& b);
#endif /* BITMAP_H_ */
