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
#include <algorithm>
Bitmap::Bitmap(int row_count, int col_count) :
		norm(-195),
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
	 return x + row_count * y;
}
void Bitmap::printMap(){	//debugging
	for (int col = 0; col < col_count; col++){
			for (int row = 0; row < row_count; row++){
				if (row == row_count - 1) std::cout<<std::endl;
				std::cout<<bmap[index(row,col)]<<" ";
			}
	}
/*	for (int i = 0; i < col_count*row_count; i++){
			std::cout<<i<<"  "<<bmap[i]<<std::endl;
	}
*/
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
				AnImage(row,col)->Green = bmap[index(row,col)]*norm +236;
				AnImage(row,col)->Red = bmap[index(row,col)]*norm + 236;
				AnImage(row,col)->Blue = bmap[index(row,col)]*norm + 236;
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
/*void fftVerticalShift(double *data, int col_count){
	//parzyste, N>>1 to po prostu N/2 które się szybciej liczy
	if (col_count%2 == 0)
		std::rotate(&data[0], &data[col_count>>1], &data[col_count]);
	else
		std::rotate(&data[0], &data[(col_count>>1) + 1], &data[col_count]);
}*/
Bitmap fft(const Bitmap& b){

	fftw_complex *out;
	fftw_plan p;
	int fft_size = (b.row_count/2) + 1;
	int n_out = (fft_size*b.col_count);
	Bitmap result(b.row_count, b.col_count);
	double* tmp_pointer = result.bmap.get();
	for (int j = 0; j < result.col_count; j++){
		for (int i = 0; i < result.row_count; i++){
			tmp_pointer[result.index(i,j)] = b.bmap[b.index(i,j)] * pow(-1,i+j);
		}
	}
	out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * n_out);
	p = fftw_plan_dft_r2c_2d(result.row_count, result.col_count, tmp_pointer, out, FFTW_ESTIMATE);
	fftw_execute(p);



	double tmp = 0;
	double max_val = 0;

	for (int j = 0; j < b.col_count; j++){
		for (int i = 0; i < fft_size; i++){
					tmp = log10(sqrt(pow(out[i+(j*fft_size)][0],2) + pow(out[i+(j*fft_size)][1],2)));
					tmp_pointer[result.index(i,j)] = tmp;
					if(tmp>max_val) max_val = tmp;
			}
		for (int i = fft_size; i < b.row_count; i++){
					tmp = log10(sqrt(pow(out[b.row_count/2-(i - b.row_count/2)+(j*fft_size)][0],2) + pow(out[b.row_count/2-(i - b.row_count/2)+(j*fft_size)][1],2)));
					tmp_pointer[result.index(i,j)] = tmp;
					if(tmp>max_val) max_val = tmp;
		}
	}
	std::cout<<max_val;
	for (int i = 0; i < result.row_count*result.col_count; i++){
		tmp_pointer[i] /= (double)max_val;
	}
	fftw_destroy_plan(p);
	fftw_free(out);
	return result;
}

