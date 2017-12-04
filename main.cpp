#include <iostream>
#include "bmp/EasyBMP.h"
#include "Bitmap.h"
#include "Lens.h"
#include "Zernike.h"
#include "DiffractiveStructure.h"
#include <vector>
#include <memory>
#include <chrono>

int main(int argc, char** argv){
    int size = 2048;
    double probkowanie = 100000;
    double f = 1;
	double lambda = 632.8*0.000000001;

	std::unique_ptr<DiffractiveStructure> soczewka = std::make_unique<Lens>(size,size, lambda, f, probkowanie, Lens::paraxial_formula);
	std::unique_ptr<DiffractiveStructure> zernik = std::make_unique<Zernike>(size,size, 0.5, Zernike::Z7);
	std::unique_ptr<DiffractiveStructure> zernik2 = std::make_unique<Zernike>(size,size, 0.5, Zernike::Z19);
	std::unique_ptr<DiffractiveStructure> zernik3 = std::make_unique<Zernike>(size,size, 0.5, Zernike::Z20);
    std::vector<DiffractiveStructure*> toMergeLens;
	toMergeLens.push_back(soczewka.get());
	toMergeLens.push_back(zernik.get());
	Bitmap mercz(size,size);
	Bitmap mercz2(size,size);
	Bitmap mercz3(size,size);
	soczewka->returnBitmap()->generateImage("socz.bmp");
//	mercz.mergeMaps(toMergeLens);
	toMergeLens.clear();
	toMergeLens.push_back(soczewka.get());
	toMergeLens.push_back(zernik3.get());
	mercz2.mergeMaps(toMergeLens);
	mercz2.generateImage("mer.bmp");
//	toMergeLens.clear();
//	toMergeLens.push_back(soczewka.get());
//	toMergeLens.push_back(zernik3.get());
//	mercz3.mergeMaps(toMergeLens);
//	Bitmap fftTest = fft(mercz,f*probkowanie,lambda*probkowanie);
	Bitmap fftTest2 = fft(mercz2,f*probkowanie,lambda*probkowanie);
//	Bitmap fftTest3 = fft(mercz3,f*probkowanie,lambda*probkowanie);
//	fftTest.generateImage("test.bmp");
	fftTest2.generateImage("test2.bmp");
//	fftTest3.generateImage("test3.bmp");
}


