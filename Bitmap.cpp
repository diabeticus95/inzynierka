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
#include "fftw/fftw3.h"
Bitmap::Bitmap(int row_count, int col_count) :
		norm(255),
		bit_depth(24) {
	this->row_count = row_count;
	this->col_count = col_count;
	bmap = std::make_unique<double[]>(row_count * col_count);
}
Bitmap::Bitmap(const Bitmap &b){
	*this = b;
	norm = b.norm;
	bit_depth = b.bit_depth;
	row_count = b.row_count;
	col_count = b.col_count;
}
Bitmap& Bitmap::operator=(const Bitmap &b){
	if (row_count != b.row_count)  throw std::invalid_argument("size not matching");
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
				AnImage(row,col)->Green = bmap[index(row,col)]*norm;
				AnImage(row,col)->Red = bmap[index(row,col)]*norm;
				AnImage(row,col)->Blue = bmap[index(row,col)]*norm;
		 }
	}

	AnImage.WriteToFile(fileName);

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
	double tmp = 0;
	for(int i=0; i<row_count*col_count; i++) {
		tmp = this->bmap[i];
		this->bmap[i] = tmp - floor(tmp);
	}

}


void outerMergeMaps(DiffractiveStructure* a, DiffractiveStructure* b){
        int size = a->returnBitmap()->row_count*a->returnBitmap()->col_count;
        for(int i=0; i<size; i++)
            b->returnBitmap()->bmap[i] += a->returnBitmap()->bmap[i];
}

Bitmap fft(const Bitmap& b){

	fftw_complex *out;
	fftw_plan p;
	out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * b.col_count * b.row_count);
	p = fftw_plan_dft_r2c_2d(b.row_count, b.col_count, b.bmap.get(), out, FFTW_ESTIMATE);
	fftw_execute(p);
	Bitmap result(b.row_count, b.col_count);
	double* tmp_pointer = result.bmap.get();
	double tmp = 0;
	double max_val = 0;
	for (int i = 0; i < b.col_count; i++){
		tmp = sqrt(pow(out[0][i],2) + pow(out[1][i],2));
		tmp_pointer[i] = tmp;
		if(tmp>max_val) max_val = tmp;
		std::cout<<tmp_pointer[i]<<" "<<std::endl;
	}
	for (int i = 0; i < b.col_count; i++){
		tmp_pointer[i] /= (double)max_val;
		std::cout<<tmp_pointer[i]<<" ";
	}
	fftw_destroy_plan(p);
	fftw_free(out);
	return result;
}

