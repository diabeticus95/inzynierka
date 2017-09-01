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

Bitmap::Bitmap(int row_count, int col_count) : norm(255), max_bitmap_value(0),
																bit_depth(24) {
	this->row_count = row_count;
	this->col_count = col_count;
	bmap = new double[row_count * col_count];
}

Bitmap::~Bitmap() {
	delete bmap;
}
int Bitmap::index(int x, int y ){
	 return x + col_count * y;
}
void Bitmap::printMap(){
	for (int row = 0; row < row_count; row++){
			for (int col = 0; col < col_count; col++){
				if (col == col_count - 1) std::cout<<std::endl;
				std::cout<<bmap[index(row,col)]<<" ";
			}
	}
}
void Bitmap::printMap(char* fileName){
	std::fstream plik;
	plik.open(fileName, std::ios::app);
	for (int row = 0; row < row_count; row++){
			for (int col = 0; col < col_count; col++){
				if (col == col_count - 1) plik<<std::endl;
				plik<<bmap[index(row,col)]<<" ";
			}
	}
	plik<<std::endl<<std::endl;
	plik.close();
}
void Bitmap::generateImage(char* fileName){
	for (double row = 0; row < row_count; row++){
			for (double col = 0; col < col_count; col++){
				bmap[index(row,col)] = (bmap[index(row,col)] * norm/max_bitmap_value);
			}
	}

	BMP AnImage;
	AnImage.SetSize(row_count,col_count);
	AnImage.SetBitDepth(bit_depth);
	for (int row = 0; row < row_count; row++){
			for (int col = 0; col < col_count; col++){
				AnImage(row,col)-> Green = bmap[ index(row,col)];
				AnImage(row,col)-> Red = bmap[ index(row,col)];
				AnImage(row,col)-> Blue = bmap[ index(row,col)];
		 }
	}
	AnImage.WriteToFile(fileName);

}
void Bitmap::setMaxValue(double max){
	max_bitmap_value = max;
}

