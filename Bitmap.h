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
class DiffractiveStructure;
void releaseVector(std::vector<DiffractiveStructure*> &toMerge);
void outerMergeMaps(DiffractiveStructure* a, DiffractiveStructure* b);
class Bitmap {
public:
	int row_count, col_count;
	std::unique_ptr<double[]> bmap; //sztuczka z indeksowaniem
	int index( int x, int y ) const;
	void printMap();
	void printMap(char* fileName);
	void generateImage(char* filename);
	void setMaxValue(double max);
	void mergeMaps(std::vector<DiffractiveStructure*> &toMerge);

//	Bitmap(Bitmap bmap, double max_bitmap_value);
	Bitmap(int row_count, int col_count);
	Bitmap(const Bitmap &);
	Bitmap& operator=(const Bitmap &b);
	virtual ~Bitmap();

private:
	double norm;
	double max_bitmap_value;
	int bit_depth;

};

#endif /* BITMAP_H_ */
