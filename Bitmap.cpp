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
//		norm(-195),
		norm(255),
		bit_depth(24) {
	this->row_count = row_count;
	this->col_count = col_count;
	bmap = std::make_unique<double[]>(row_count * col_count);
}
Bitmap::Bitmap(const Bitmap &b){
	norm = b.norm;
	bit_depth = b.bit_depth;
	row_count = b.row_count;
	col_count = b.col_count;
	*this = b;

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
				std::cout<<bmap[index(row,col)]<<" ";
				if (row == row_count - 1) std::cout<<std::endl;

			}
	}
}
void Bitmap::printMap(char* fileName){
	std::fstream plik;
	plik.open(fileName, std::ios::app);
	for (int col = 0; col < col_count; col++){
			for (int row = 0; row < row_count; row++){
				plik<<bmap[index(row,col)]<<" ";
				if (row == row_count - 1) plik<<std::endl;
			}
	}
	plik<<std::endl<<std::endl;
	plik.close();
}

void Bitmap::generateImage(char* fileName){
	BMP AnImage;
	AnImage.SetSize(row_count,col_count);
	AnImage.SetBitDepth(24);
	for (int col = 0; col < col_count; col++){
			for (int row = 0; row < row_count; row++){/*
				AnImage(row,col)->Green = bmap[index(row,col)]*norm +236;
				AnImage(row,col)->Red = bmap[index(row,col)]*norm + 236;
				AnImage(row,col)->Blue = bmap[index(row,col)]*norm + 236;*/

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

//PAMIĘTAJ ŻE MODYFIKUJESZ STRUKTURY!
void outerMergeMaps(DiffractiveStructure* a, DiffractiveStructure* b){
        int size = a->returnBitmap()->row_count*a->returnBitmap()->col_count;
        for(int i=0; i<size; i++)
            b->returnBitmap()->bmap[i] += a->returnBitmap()->bmap[i];
}
void Bitmap::rot90(){
	int n = row_count;
	Bitmap tmp(*this);
	for (int j = 0; j < n; j++) {
		for (int i = 0; i < n; i++) {
			bmap[index(i,j)] = tmp.bmap[index(n - j - 1, i)];
		}
	}
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
	fftw_complex *in;
	fftw_plan p;

	int n_out = b.row_count * b.col_count;

	out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * n_out);
	in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * n_out);

	for (int j = 0; j < b.row_count; j++){
		for (int i = 0; i < b.row_count; i++){
			in[b.index(i,j)][0] = sin(b.bmap[b.index(i,j)]) * pow(-1,i+j);
			in[b.index(i,j)][1] = cos(b.bmap[b.index(i,j)]) * pow(-1,i+j);
		}
	}

	p = fftw_plan_dft_2d(b.row_count, b.col_count, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
	fftw_execute(p);


	Bitmap result(b.row_count, b.col_count);
	double* tmp_pointer = result.bmap.get();
	double tmp = 0;
	double max_val = 0;
//result index i b index to tu to samo. konwersja 2d -> id
	for (int j = 0; j < b.col_count; j++){
		for (int i = 0; i < b.row_count; i++){
					tmp = sqrt(pow(out[b.index(i,j)][0],2) + pow(out[b.index(i,j)][1],2));
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
	fftw_free(in);
	return result;
}
Bitmap rot90(char* fileName){
	BMP AnImage;
	AnImage.ReadFromFile(fileName);
	int n = AnImage.TellHeight();
	Bitmap rot90(n,n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			rot90.bmap[rot90.index(i,j)] = (double)((double)AnImage(n - j - 1, i)->Green/255 + (double)AnImage(n - j - 1, i)->Red/255 + (double)AnImage(n - j - 1, i)->Blue/255)/3;
		}
	}
	for (int i = -n/2; i < n/2; i++) {
		for (int j = -n/2; j < n/2; j++) {
			if (i*i + j*j > pow(n/2,2)){
				rot90.bmap[rot90.index(i+n/2,j+n/2)] = 0;
			}
		}
	}
	return rot90;
}
Bitmap load2Bitmap(char* fileName){
	BMP AnImage;
	AnImage.ReadFromFile(fileName);
	int n = AnImage.TellHeight();
	Bitmap loaded(n,n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			loaded.bmap[loaded.index(i,j)] = (double)((double)AnImage(n - j - 1, i)->Green/256 + (double)AnImage(n - j - 1, i)->Red/256 + (double)AnImage(n - j - 1, i)->Blue/256)/3;
		}
	}
	return loaded;
}


