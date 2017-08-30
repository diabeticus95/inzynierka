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
//	Lens soczewka;
//	Bitmap mercz(2048, 2048);
//	mercz = mergeMaps(wielomian.returnBitmap(), soczewka.returnBitmap());
//	mercz.generateImage();
//	(example.returnBitmap())->printMap();
	(wielomian.returnBitmap())->generateImage();
}


