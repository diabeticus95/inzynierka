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
	Zernike wielomian;
//	Zernike wielomian2;
	Lens soczewka;
	Bitmap* mercz = new Bitmap(2048, 2048);
	mercz = mergeMaps(wielomian.returnBitmap(), soczewka.returnBitmap());
//	mercz->printMap();
	wielomian.returnBitmap()->generateImage("testZer.bmp");
	soczewka.returnBitmap()->generateImage("testLens.bmp");
	mercz->generateImage("merge.bmp");
//	(wielomian.returnBitmap())->printMap();
//	(wielomian.returnBitmap())->generateImage("test.bmp");

/*	BMP AnImage;
	AnImage.ReadFromFile("merge.bmp");
	for(int x = 0; x<1024; x++){
	cout << "(" << (int) AnImage(x,x)->Red << ","
	<< (int) AnImage(x,x)->Green << ","
	<< (int) AnImage(x,x)->Blue << ","
	<< (int) AnImage(x,x)->Alpha << ")" << endl;
	}
*/
}


