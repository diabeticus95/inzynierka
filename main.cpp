#include <iostream>
#include "bmp/EasyBMP.h"
#include <tgmath.h>
#include <math.h>
#include "Bitmap.h"
#include "Lens.h"
#include "Zernike.h"
#include "DiffractiveStructure.h"
#include <vector>
#include <memory>
#include <chrono>

/* TO DO:
 * - dodac wersje bez przyblizenia przyosiowego
 * - probkowanie zmienia wygląd struktury???
 * - co wlasciwie oznacza wielkosc soczewki. jak dopasowywac zerniki do roznych wielkosci?
 * - jakie dane powinien podawac user - fizyczny rozmiar soczewki, rozdzielczosc, czy probkowanie?
 *  - update zernike poly - w pliku od pani ag.
 *  - fft ze strony fftw.org
 *  - czy brzegi zernike'a nie psują normalizacji PSUJĄ
 */

int main(int argc, char** argv){
        std::chrono::time_point<std::chrono::system_clock> start, end;
        std::chrono::duration<double> diff;

	int size = 2048;
	double probkowanie = pow(10,5);
        
        std::cout << "LENS...\n";
        start = std::chrono::system_clock::now();

	std::unique_ptr<DiffractiveStructure> soczewka = std::make_unique<Lens>(size,size,probkowanie);
//	DiffractiveStructure *wielomian3 = new Zernike(size,size,1,Z3);

        end = std::chrono::system_clock::now(); diff = end - start;
        std::cout << diff.count() << " seconds\nZERNIK...\n";
        start = end;

//        std::unique_ptr<DiffractiveStructure> wielomian5 = std::make_unique<Zernike>(size,size,1,Z3);
//        std::unique_ptr<DiffractiveStructure> wielomian4 = std::make_unique<Zernike>(size,size,3,Z4);
//	DiffractiveStructure *wielomian6 = new Zernike(size,size,1,Z6);
//	DiffractiveStructure *wielomian7 = new Zernike(size,size,1,Z7);
//	DiffractiveStructure *wielomian8 = new Zernike(size,size,1,Z8);
//	DiffractiveStructure *wielomian9 = new Zernike(size,size,1,Z9);

        

	Bitmap mercz(size,size);

        end = std::chrono::system_clock::now(); diff = end - start;
        std::cout << diff.count() << " seconds\nVECTORIZING...\n";
        start = end;

/*	std::vector<DiffractiveStructure*> toMerge;
	toMerge.push_back(soczewka.get());
//	toMerge.push_back(wielomian2);
	toMerge.push_back(wielomian4.get());
	toMerge.push_back(wielomian5.get());
	toMerge.push_back(wielomian6);
	toMerge.push_back(wielomian7);
	toMerge.push_back(wielomian8);
	toMerge.push_back(wielomian9);	*/

	char zernik[] = "zernik.bmp";
	char socz[] = "soczewka.bmp";
	char mer[] = "merge.bmp";

        end = std::chrono::system_clock::now(); diff = end - start;
        std::cout << diff.count() << " seconds\nIMAGING...\n";
        start = end;

//	wielomian5->returnBitmap()->generateImage(zernik);
	soczewka->returnBitmap()->generateImage(socz);
        
        end = std::chrono::system_clock::now(); diff = end - start;
        std::cout << diff.count() << " seconds\nMERGING...\n";
        start = end;

//	mercz.mergeMaps(toMerge);

        end = std::chrono::system_clock::now(); diff = end - start;
        std::cout << diff.count() << " seconds\nMERGING FINISHED\n";
//	mercz.generateImage(mer);


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


