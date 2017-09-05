#include <iostream>
#include "bmp/EasyBMP.h"
#include <tgmath.h>
#include <math.h>
#include "Bitmap.h"
#include "Lens.h"
#include "Zernike.h"
#include "DiffractiveStructure.h"
#include <vector>
/* TO DO:
 * - dodac wersje bez przyblizenia przyosiowego
 * - making DiffractiveStr "guaranteed to not throw while moving (move constructible) makes vector optimise moving
 */

int main(int argc, char** argv){
	int size = 1024	;
//	Zernike wielomian0(256,256,100,Z0);
//	Zernike wielomian1(256,256,Z1);
//	DiffractiveStructure *wielomian2 = new Zernike(size,size,4,Z2);
	DiffractiveStructure *soczewka = new Lens(size,size);
//	DiffractiveStructure *wielomian3 = new Zernike(size,size,1,Z3);
	DiffractiveStructure *wielomian5 = new Zernike(size,size,1,Z4);
//	DiffractiveStructure *wielomian6 = new Zernike(size,size,1,Z6);
//	DiffractiveStructure *wielomian7 = new Zernike(size,size,1,Z7);
//	DiffractiveStructure *wielomian8 = new Zernike(size,size,1,Z8);
//	DiffractiveStructure *wielomian9 = new Zernike(size,size,1,Z9);

	Bitmap* mercz = new Bitmap(256,256);

	std::vector<DiffractiveStructure*> toMerge;
	toMerge.push_back(soczewka);
//	toMerge.push_back(wielomian2);
//	toMerge.push_back(wielomian3);
	toMerge.push_back(wielomian5);
/*	toMerge.push_back(wielomian6);
	toMerge.push_back(wielomian7);
	toMerge.push_back(wielomian8);
	toMerge.push_back(wielomian9);	*/
	wielomian5->returnBitmap()->generateImage("astigmatism.bmp");
	soczewka->returnBitmap()->generateImage("soczewka.bmp");
	mercz->mergeMaps(toMerge);
	mercz->generateImage("merge2.bmp");


//	wielomian0.returnBitmap()->generateImage("maps/Zer0.bmp");
/*	wielomian1.returnBitmap()->generateImage("Zer1.bmp");
	wielomian2.returnBitmap()->generateImage("Zer2.bmp");
	wielomian3.returnBitmap()->generateImage("Zer3.bmp");
	wielomian4.returnBitmap()->generateImage("Zer4.bmp");
	wielomian5.returnBitmap()->generateImage("Zer5.bmp");
	wielomian6.returnBitmap()->generateImage("Zer6.bmp");
	wielomian7.returnBitmap()->generateImage("Zer7.bmp");
	wielomian8.returnBitmap()->generateImage("Zer8.bmp");
	wielomian9.returnBitmap()->generateImage("Zer9.bmp");
	wielomian10.returnBitmap()->generateImage("Zer10.bmp");
	wielomian11.returnBitmap()->generateImage("Zer11.bmp");
	wielomian12.returnBitmap()->generateImage("Zer12.bmp");
	wielomian13.returnBitmap()->generateImage("Zer13.bmp");
	wielomian14.returnBitmap()->generateImage("Zer14.bmp");
	wielomian15.returnBitmap()->generateImage("Zer15.bmp");
	wielomian16.returnBitmap()->generateImage("Zer16.bmp");
	wielomian17.returnBitmap()->generateImage("Zer17.bmp");
	wielomian18.returnBitmap()->generateImage("Zer18.bmp");
	wielomian19.returnBitmap()->generateImage("Zer19.bmp");
	wielomian20.returnBitmap()->generateImage("Zer20.bmp");*/
}


