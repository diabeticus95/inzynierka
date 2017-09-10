/*
 * Bitmap.cpp
 *
 *  Created on: 03.08.2017
 *      Author: Patryk Kowalski
 */

#include "Bitmap.h"
#include <iostream>
#include "bmp/EasyBMP.h"
#include <fstream>
#include "DiffractiveStructure.h"
#include <vector>
#define M_PI 3.14159265358979323846
Bitmap::Bitmap(int row_count, int col_count) :
		norm(255),
		max_bitmap_value(0),
		bit_depth(24) {
	this->row_count = row_count;
	this->col_count = col_count;
	bmap = std::make_unique<double[]>(row_count * col_count);
}
Bitmap::Bitmap(const Bitmap &b){
	*this = b;
}
Bitmap& Bitmap::operator=(const Bitmap &b){
	if (row_count != b.row_count)  throw std::invalid_argument("size not matching");
	norm = b.norm;
	max_bitmap_value = b.max_bitmap_value;
	bit_depth = b.bit_depth;
	row_count = b.row_count;
	col_count = b.col_count;
	bmap = std::make_unique<double[]>(row_count * col_count);
	for (int col = 0; col < col_count; col++){
			for (int row = 0; row < row_count; row++){
				bmap[index(row,col)] = b.bmap[b.index(row,col)];
			}
	}
	return *this;
}

Bitmap::~Bitmap() {
	std::cerr<<"usunalem bitmape"<<std::endl;
}
int Bitmap::index(int x, int y ) const{
	 return x + col_count * y;
}
void Bitmap::printMap(){	//debugging
	for (int col = 0; col < col_count; col++){
			for (int row = 0; row < row_count; row++){
				if (row == row_count - 1) std::cout<<std::endl;
				std::cout<<bmap[index(row,col)]<<" ";
			}
	}
}
void Bitmap::printMap(char* fileName){
	std::fstream plik;
	plik.open(fileName, std::ios::app);
	for (int col = 0; col < col_count; col++){
			for (int row = 0; row < row_count; row++){
				if (row == row_count - 1) plik<<std::endl;
				plik<<bmap[index(row,col)]<<" ";
			}
	}
	plik<<std::endl<<std::endl;
	plik.close();
}
void Bitmap::generateImage(char* fileName){
	BMP AnImage;
	AnImage.SetSize(row_count,col_count);
	AnImage.SetBitDepth(bit_depth);
	for (int col = 0; col < col_count; col++){
			for (int row = 0; row < row_count; row++){
				AnImage(row,col)->Green = bmap[index(row,col)]*norm/max_bitmap_value;
				AnImage(row,col)->Red = bmap[index(row,col)]*norm/max_bitmap_value;
				AnImage(row,col)->Blue = bmap[index(row,col)]*norm/max_bitmap_value;
		 }
	}

	AnImage.WriteToFile(fileName);

}
void Bitmap::setMaxValue(double max){
	max_bitmap_value = max;
}
void Bitmap::mergeMaps(std::vector<DiffractiveStructure*> &toMerge){
	for (auto it = toMerge.begin() + 1; it < toMerge.end(); it++){
		outerMergeMaps(*(it-1),*it);
	}
	try{
		*this = *(toMerge.back()->returnBitmap());
	}
	catch (const std::invalid_argument& e ) {
		std::cerr << "exception: " << e.what() << std::endl;
	}

        for(int i=0; i<row_count*col_count; i++) {
            this->bmap[i] = fmod(this->bmap[i], 2*M_PI);
        }

}


void outerMergeMaps(DiffractiveStructure* a, DiffractiveStructure* b){
        int size = a->getRowCount()*a->getColCount();
        for(int i=0; i<size; i++)
            b->returnBitmap()->bmap[i] += a->returnBitmap()->bmap[i];
}
