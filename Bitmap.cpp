/*
 * Bitmap.cpp
 *
 *  Created on: 03.08.2017
 *      Author: Patryk Kowalski
 */

#include "Bitmap.h"
#include <iostream>
#include "bmp/EasyBMP.h"
#include <iostream>
#include <fstream>
/*Bitmap::Bitmap(int row_count, int col_count, double MAX_VALUE) : norm(255), max_bitmap_value(MAX_VALUE),
																bit_depth(24) {
	this->row_count = row_count;
	this->col_count = col_count;
	bmap = new double[row_count * col_count];
}
*/
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
//	this->printMap("debug.txt");
	for (double row = 0; row < row_count; row++){
			for (double col = 0; col < col_count; col++){
				bmap[index(row,col)] = (bmap[index(row,col)] * norm/max_bitmap_value);
			}
	}
	this->printMap("debug.txt");

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
Bitmap* mergeMaps(Bitmap* a, Bitmap* b){
//	a->printMap("debug.txt");
//	b->printMap("debug.txt");
	int count = a->row_count;
	Bitmap* nowa = new Bitmap(count,count);
	for (int row = 0; row < count; row++){
			for (int col = 0; col < count; col++){
				nowa->bmap[nowa->index(row,col)] = fmod(a->bmap[a->index(row,col)] + b->bmap[b->index(row,col)],2*M_PI);
			}
	}
	nowa->setMaxValue(2*M_PI);
//	nowa->printMap("debug.txt");
	return nowa;
}
