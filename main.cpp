#include <iostream>
#include "bmp/EasyBMP.h"
#include <tgmath.h>
#include <math.h>
#include "Bitmap.h"
#include "Lens.h"
#include "Zernike.h"
using namespace std;
/* TO DO:
 * - dodac wersje bez przyblizenia przyosiowego
 * - zainteresuj sie biblioteka goptical
 * - skminic probkowanie w Zernike
 */

int main(int argc, char** argv){
//	Zernike wielomian0(256,256,100,Z0);
//	Zernike wielomian1(256,256,Z1);
//	Zernike wielomian2(256,256,Z2);
	Zernike wielomian3(256,256,1,Z3);
/*	Zernike wielomian4(256,256,Z4);
	Zernike wielomian5(256,256,Z5);
	Zernike wielomian6(256,256,Z6);
	Zernike wielomian7(256,256,Z7);
	Zernike wielomian8(256,256,Z8);
	Zernike wielomian9(256,256,Z9);
	Zernike wielomian10(256,256,Z10);
	Zernike wielomian11(256,256,Z11);
	Zernike wielomian12(256,256,Z12);
	Zernike wielomian13(256,256,Z13);
	Zernike wielomian14(256,256,Z14);
	Zernike wielomian15(256,256,Z15);
	Zernike wielomian16(256,256,Z16);
	Zernike wielomian17(256,256,Z17);
	Zernike wielomian18(256,256,Z18);
	Zernike wielomian19(256,256,Z19);
	Zernike wielomian20(256,256,Z20);
*/

	Lens soczewka(256,256);
//	Bitmap* mercz = new Bitmap(2048, 2048);
//	mercz = mergeMaps(wielomian.returnBitmap(), wielomian2.returnBitmap());
//	mercz->printMap();
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

//	soczewka.returnBitmap()->generateImage("testLens.bmp");
//	mercz->generateImage("merge.bmp");
//	(wielomian.returnBitmap())->printMap("debug.txt");

}


