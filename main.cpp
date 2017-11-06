#include <iostream>
#include "bmp/EasyBMP.h"
#include "Bitmap.h"
#include "Lens.h"
#include "Zernike.h"
#include "DiffractiveStructure.h"
#include <vector>
#include <memory>
#include <chrono>


/* TO DO:
 * - dodac wersje bez przyblizenia przyosiowego
*/

int main(int argc, char** argv){
//wczytaj fixy
	char fileName[] = "cropped.bmp";
	Bitmap rotb = rot90(fileName);
	Bitmap rot180b(rotb);
	rot180b.rot90();
	Bitmap rot270b(rot180b);
	rot270b.rot90();
	Bitmap rot360b(rot270b);
	rot360b.rot90();

	std::unique_ptr<DiffractiveStructure> rot90 = std::make_unique<Zernike>(rotb);
	std::unique_ptr<DiffractiveStructure> rot180 = std::make_unique<Zernike>(rot180b);
	std::unique_ptr<DiffractiveStructure> rot270 = std::make_unique<Zernike>(rot270b);
	std::unique_ptr<DiffractiveStructure> rot360 = std::make_unique<Zernike>(rot360b);

        std::chrono::time_point<std::chrono::system_clock> start, end;
        std::chrono::duration<double> diff;

	int size = 1080;
	double probkowanie = 125000; //8 mikrometrow: 1m = x * 8um
	double f = 1.17;
	double lambda = 632.8*0.000000001;

        std::cout << "LENS...\n";
        start = std::chrono::system_clock::now();

	std::unique_ptr<DiffractiveStructure> soczewka = std::make_unique<Lens>(size,size, lambda, f, probkowanie, Lens::paraxial_formula);

        end = std::chrono::system_clock::now(); diff = end - start;
        std::cout << diff.count() << " seconds\nZERNIK...\n";
        start = end;


    std::unique_ptr<DiffractiveStructure> astigmatism5 = std::make_unique<Zernike>(size,size,0.1,Zernike::Z3);
    std::unique_ptr<DiffractiveStructure> astigmatism10 = std::make_unique<Zernike>(size,size,0.2,Zernike::Z3);
    std::unique_ptr<DiffractiveStructure> astigmatism15 = std::make_unique<Zernike>(size,size,0.5,Zernike::Z3);
    std::unique_ptr<DiffractiveStructure> astigmatism1 = std::make_unique<Zernike>(size,size,1,Zernike::Z3);
    std::unique_ptr<DiffractiveStructure> astigmatism2 = std::make_unique<Zernike>(size,size,2,Zernike::Z3);


    std::unique_ptr<DiffractiveStructure> defocus5 = std::make_unique<Zernike>(size,size,0.1,Zernike::Z4);
    std::unique_ptr<DiffractiveStructure> defocus10 = std::make_unique<Zernike>(size,size,0.2,Zernike::Z4);
    std::unique_ptr<DiffractiveStructure> defocus15 = std::make_unique<Zernike>(size,size,0.5,Zernike::Z4);
    std::unique_ptr<DiffractiveStructure> defocus1 = std::make_unique<Zernike>(size,size,1,Zernike::Z4);
    std::unique_ptr<DiffractiveStructure> defocus2 = std::make_unique<Zernike>(size,size,2,Zernike::Z4);

    std::unique_ptr<DiffractiveStructure> coma5 = std::make_unique<Zernike>(size,size,0.1,Zernike::Z7);
    std::unique_ptr<DiffractiveStructure> coma10 = std::make_unique<Zernike>(size,size,0.2,Zernike::Z7);
    std::unique_ptr<DiffractiveStructure> coma15 = std::make_unique<Zernike>(size,size,0.5,Zernike::Z7);
    std::unique_ptr<DiffractiveStructure> coma1 = std::make_unique<Zernike>(size,size,1,Zernike::Z7);
    std::unique_ptr<DiffractiveStructure> coma2 = std::make_unique<Zernike>(size,size,2,Zernike::Z7);

    std::unique_ptr<DiffractiveStructure> spherical5 = std::make_unique<Zernike>(size,size,0.1,Zernike::Z12);
    std::unique_ptr<DiffractiveStructure> spherical10 = std::make_unique<Zernike>(size,size,0.2,Zernike::Z12);
    std::unique_ptr<DiffractiveStructure> spherical15 = std::make_unique<Zernike>(size,size,0.5,Zernike::Z12);
    std::unique_ptr<DiffractiveStructure> spherical1 = std::make_unique<Zernike>(size,size,1,Zernike::Z12);
    std::unique_ptr<DiffractiveStructure> spherical2 = std::make_unique<Zernike>(size,size,2,Zernike::Z12);



    std::unique_ptr<DiffractiveStructure> highOrder18 = std::make_unique<Zernike>(size,size,0.2,Zernike::Z18);
    std::unique_ptr<DiffractiveStructure> highOrder19 = std::make_unique<Zernike>(size,size,0.2,Zernike::Z19);
    std::unique_ptr<DiffractiveStructure> highOrder20 = std::make_unique<Zernike>(size,size,0.2,Zernike::Z20);



    Bitmap merczLens(size,size);
    Bitmap merczAst5(size,size);
    Bitmap merczAst10(size,size);
    Bitmap merczAst15(size,size);
    Bitmap merczAst1(size,size);
    Bitmap merczAst2(size,size);
    Bitmap merczDef5(size,size);
    Bitmap merczDef10(size,size);
    Bitmap merczDef15(size,size);
    Bitmap merczDef1(size,size);
    Bitmap merczDef2(size,size);
    Bitmap merczCom5(size,size);
    Bitmap merczCom10(size,size);
    Bitmap merczCom15(size,size);
    Bitmap merczCom1(size,size);
    Bitmap merczCom2(size,size);
    Bitmap merczSph5(size,size);
    Bitmap merczSph10(size,size);
    Bitmap merczSph15(size,size);
    Bitmap merczSph1(size,size);
    Bitmap merczSph2(size,size);
    Bitmap merczhighOrder18(size,size);
    Bitmap merczhighOrder19(size,size);
    Bitmap merczhighOrder20(size,size);
    Bitmap ADC(size, size);
    Bitmap ACS(size, size);
    Bitmap DCS(size, size);

        end = std::chrono::system_clock::now(); diff = end - start;
        std::cout << diff.count() << " seconds\nVECTORIZING...\n";
        start = end;

    std::vector<DiffractiveStructure*> toMergeLens;
	std::vector<DiffractiveStructure*> toMergeAst5;
	std::vector<DiffractiveStructure*> toMergeAst10;
	std::vector<DiffractiveStructure*> toMergeAst15;
	std::vector<DiffractiveStructure*> toMergeAst1;
	std::vector<DiffractiveStructure*> toMergeAst2;
	std::vector<DiffractiveStructure*> toMergeDef5;
	std::vector<DiffractiveStructure*> toMergeDef10;
	std::vector<DiffractiveStructure*> toMergeDef15;
	std::vector<DiffractiveStructure*> toMergeDef1;
	std::vector<DiffractiveStructure*> toMergeDef2;
	std::vector<DiffractiveStructure*> toMergeCom5;
	std::vector<DiffractiveStructure*> toMergeCom10;
	std::vector<DiffractiveStructure*> toMergeCom15;
	std::vector<DiffractiveStructure*> toMergeCom1;
	std::vector<DiffractiveStructure*> toMergeCom2;
	std::vector<DiffractiveStructure*> toMergeSph5;
	std::vector<DiffractiveStructure*> toMergeSph10;
	std::vector<DiffractiveStructure*> toMergeSph15;
	std::vector<DiffractiveStructure*> toMergeSph1;
	std::vector<DiffractiveStructure*> toMergeSph2;
	std::vector<DiffractiveStructure*> toMergeHO18;
	std::vector<DiffractiveStructure*> toMergeHO19;
	std::vector<DiffractiveStructure*> toMergeHO20;
	std::vector<DiffractiveStructure*> toMergeADC;
	std::vector<DiffractiveStructure*> toMergeACS;
	std::vector<DiffractiveStructure*> toMergeDCS;

	toMergeLens.push_back(soczewka.get());
	toMergeLens.push_back(rot360.get());

	toMergeAst5.push_back(soczewka.get());
	toMergeAst5.push_back(astigmatism5.get());
	toMergeAst5.push_back(rot360.get());

	toMergeAst10.push_back(soczewka.get());
	toMergeAst10.push_back(astigmatism10.get());
	toMergeAst10.push_back(rot360.get());

	toMergeAst15.push_back(soczewka.get());
	toMergeAst15.push_back(astigmatism15.get());
	toMergeAst15.push_back(rot360.get());

	toMergeAst1.push_back(soczewka.get());
	toMergeAst1.push_back(astigmatism1.get());
	toMergeAst1.push_back(rot360.get());

	toMergeAst2.push_back(soczewka.get());
	toMergeAst2.push_back(astigmatism2.get());
	toMergeAst2.push_back(rot360.get());

	toMergeDef5.push_back(soczewka.get());
	toMergeDef5.push_back(defocus5.get());
	toMergeDef5.push_back(rot360.get());

	toMergeDef10.push_back(soczewka.get());
	toMergeDef10.push_back(defocus10.get());
	toMergeDef10.push_back(rot360.get());

	toMergeDef15.push_back(soczewka.get());
	toMergeDef15.push_back(defocus15.get());
	toMergeDef15.push_back(rot360.get());

	toMergeDef1.push_back(soczewka.get());
	toMergeDef1.push_back(defocus1.get());
	toMergeDef1.push_back(rot360.get());

	toMergeDef2.push_back(soczewka.get());
	toMergeDef2.push_back(defocus2.get());
	toMergeDef2.push_back(rot360.get());

	toMergeCom5.push_back(soczewka.get());
	toMergeCom5.push_back(coma5.get());
	toMergeCom5.push_back(rot360.get());

	toMergeCom10.push_back(soczewka.get());
	toMergeCom10.push_back(coma10.get());
	toMergeCom10.push_back(rot360.get());

	toMergeCom15.push_back(soczewka.get());
	toMergeCom15.push_back(coma15.get());
	toMergeCom15.push_back(rot360.get());

	toMergeCom1.push_back(soczewka.get());
	toMergeCom1.push_back(coma1.get());
	toMergeCom1.push_back(rot360.get());

	toMergeCom2.push_back(soczewka.get());
	toMergeCom2.push_back(coma2.get());
	toMergeCom2.push_back(rot360.get());

	toMergeSph5.push_back(soczewka.get());
	toMergeSph5.push_back(spherical5.get());
	toMergeSph5.push_back(rot360.get());

	toMergeSph10.push_back(soczewka.get());
	toMergeSph10.push_back(spherical10.get());
	toMergeSph10.push_back(rot360.get());

	toMergeSph15.push_back(soczewka.get());
	toMergeSph15.push_back(spherical15.get());
	toMergeSph15.push_back(rot360.get());

	toMergeSph1.push_back(soczewka.get());
	toMergeSph1.push_back(spherical1.get());
	toMergeSph1.push_back(rot360.get());

	toMergeSph2.push_back(soczewka.get());
	toMergeSph2.push_back(spherical2.get());
	toMergeSph2.push_back(rot360.get());

	toMergeHO18.push_back(soczewka.get());
	toMergeHO18.push_back(highOrder18.get());
	toMergeHO18.push_back(rot360.get());

	toMergeHO19.push_back(soczewka.get());
	toMergeHO19.push_back(highOrder19.get());
	toMergeHO19.push_back(rot360.get());

	toMergeHO20.push_back(soczewka.get());
	toMergeHO20.push_back(highOrder20.get());
	toMergeHO20.push_back(rot360.get());

	toMergeADC.push_back(soczewka.get());
	toMergeADC.push_back(astigmatism10.get());
	toMergeADC.push_back(defocus10.get());
	toMergeADC.push_back(coma10.get());
	toMergeADC.push_back(rot360.get());

	toMergeACS.push_back(soczewka.get());
	toMergeACS.push_back(astigmatism10.get() );
	toMergeACS.push_back(coma10.get() );
	toMergeACS.push_back(spherical10.get() );
	toMergeACS.push_back(rot360.get());

	toMergeDCS.push_back(soczewka.get());
	toMergeDCS.push_back(defocus10.get() );
	toMergeDCS.push_back(coma10.get());
	toMergeDCS.push_back(spherical10.get() );
	toMergeDCS.push_back(rot360.get());

	char socz[] = "fix/soczewka.bmp";
	char  a5[] = "fix/a5.bmp";
	char  a10[] = "fix/a10.bmp";
	char  a15[] = "fix/a15.bmp";
	char  a1[] = "fix/a1.bmp";
	char  a2[] = "fix/a2.bmp";
	char  d5[] = "fix/d5.bmp";
	char  d10[] = "fix/d10.bmp";
	char  d15[] = "fix/d15.bmp";
	char  d1[] = "fix/d1.bmp";
	char  d2[] = "fix/d2.bmp";
	char  c5[] = "fix/c5.bmp";
	char  c10[] = "fix/c10.bmp";
	char  c15[] = "fix/c15.bmp";
	char  c1[] = "fix/c1.bmp";
	char  c2[] = "fix/c2.bmp";
	char  s5[] = "fix/s5.bmp";
	char  s10[] = "fix/s10.bmp";
	char  s15[] = "fix/s15.bmp";
	char  s1[] = "fix/s1.bmp";
	char  s2[] = "fix/s2.bmp";
	char  ho18[] = "fix/ho18.bmp";
	char  ho19[] = "fix/ho19.bmp";
	char  ho20[] = "fix/ho20.bmp";

	char soczMercz[] = "fix/soczMercz.bmp";
	char  a5Mercz[] = "fix/a5Mercz.bmp";
	char  a10Mercz[] = "fix/a10Mercz.bmp";
	char  a15Mercz[] = "fix/a15Mercz.bmp";
	char  a1Mercz[] = "fix/a1Mercz.bmp";
	char  a2Mercz[] = "fix/a2Mercz.bmp";
	char  d5Mercz[] = "fix/d5Mercz.bmp";
	char  d10Mercz[] = "fix/d10Mercz.bmp";
	char  d15Mercz[] = "fix/d15Mercz.bmp";
	char  d1Mercz[] = "fix/d1Mercz.bmp";
	char  d2Mercz[] = "fix/d2Mercz.bmp";
	char  c5Mercz[] = "fix/c5Mercz.bmp";
	char  c10Mercz[] = "fix/c10Mercz.bmp";
	char  c15Mercz[] = "fix/c15Mercz.bmp";
	char  c1Mercz[] = "fix/c1Mercz.bmp";
	char  c2Mercz[] = "fix/c2Mercz.bmp";
	char  s5Mercz[] = "fix/s5Mercz.bmp";
	char  s10Mercz[] = "fix/s10Mercz.bmp";
	char  s15Mercz[] = "fix/s15Mercz.bmp";
	char  s1Mercz[] = "fix/s1Mercz.bmp";
	char  s2Mercz[] = "fix/s2Mercz.bmp";
	char  ho18Mercz[] = "fix/ho18Mercz.bmp";
	char  ho19Mercz[] = "fix/ho19Mercz.bmp";
	char  ho20Mercz[] = "fix/ho20Mercz.bmp";
	char  adcMercz[] = "fix/ADCMercz.bmp";
	char  acsMercz[] = "fix/ACSMercz.bmp";
	char  dcsMercz[] = "fix/DCSMercz.bmp";

/*	char soczPSF[] = "fix/soczewkaPSF.bmp";
	char  a5MerczPSF[] = "fix/a5MerczPSF.bmp";
	char  a10MerczPSF[] = "fix/a10MerczPSF.bmp";
	char  a15MerczPSF[] = "fix/a15MerczPSF.bmp";
	char  a1MerczPSF[] = "fix/a1MerczPSF.bmp";
	char  a2MerczPSF[] = "fix/a2MerczPSF.bmp";
	char  d5MerczPSF[] = "fix/d5MerczPSF.bmp";
	char  d10MerczPSF[] = "fix/d10MerczPSF.bmp";
	char  d15MerczPSF[] = "fix/d15MerczPSF.bmp";
	char  d1MerczPSF[] = "fix/d1MerczPSF.bmp";
	char  d2MerczPSF[] = "fix/d2MerczPSF.bmp";
	char  c5MerczPSF[] = "fix/c5MerczPSF.bmp";
	char  c10MerczPSF[] = "fix/c10MerczPSF.bmp";
	char  c15MerczPSF[] = "fix/c15MerczPSF.bmp";
	char  c1MerczPSF[] = "fix/c1MerczPSF.bmp";
	char  c2MerczPSF[] = "fix/c2MerczPSF.bmp";
	char  s5MerczPSF[] = "fix/s5MerczPSF.bmp";
	char  s10MerczPSF[] = "fix/s10MerczPSF.bmp";
	char  s15MerczPSF[] = "fix/s15MerczPSF.bmp";
	char  s1MerczPSF[] = "fix/s1MerczPSF.bmp";
	char  s2MerczPSF[] = "fix/s2MerczPSF.bmp";
	char  ho18MerczPSF[] = "fix/ho18MerczPSF.bmp";
	char  ho19MerczPSF[] = "fix/ho19MerczPSF.bmp";
	char  ho20MerczPSF[] = "fix/ho20MerczPSF.bmp";
	char  adcMerczPSF[] = "fix/ADCMerczPSF.bmp";
	char  acsMerczPSF[] = "fix/ACSMerczPSF.bmp";
	char  dcsMerczPSF[] = "fix/DCSMerczPSF.bmp";
*/

        end = std::chrono::system_clock::now(); diff = end - start;
        std::cout << diff.count() << " seconds\nIMAGING...\n";
        start = end;

     astigmatism5->returnBitmap()->generateImage(a5);
     astigmatism10->returnBitmap()->generateImage(a10);
     astigmatism15->returnBitmap()->generateImage(a15);
     astigmatism1->returnBitmap()->generateImage(a1);
     astigmatism2->returnBitmap()->generateImage(a2);
     defocus5->returnBitmap()->generateImage(d5);
     defocus10->returnBitmap()->generateImage(d10);
     defocus15->returnBitmap()->generateImage(d15);
     defocus1->returnBitmap()->generateImage(d1);
     defocus2->returnBitmap()->generateImage(d2);
     coma5->returnBitmap()->generateImage(c5);
     coma10->returnBitmap()->generateImage(c10);
     coma15->returnBitmap()->generateImage(c15);
     coma1->returnBitmap()->generateImage(c1);
     coma2->returnBitmap()->generateImage(c2);
     spherical5->returnBitmap()->generateImage(s5);
     spherical10->returnBitmap()->generateImage(s10);
     spherical15->returnBitmap()->generateImage(s15);
     spherical1->returnBitmap()->generateImage(s1);
     spherical2->returnBitmap()->generateImage(s2);
     highOrder18->returnBitmap()->generateImage(ho18);
     highOrder19->returnBitmap()->generateImage(ho19);
     highOrder20->returnBitmap()->generateImage(ho20);

	soczewka->returnBitmap()->generateImage(socz);

		end = std::chrono::system_clock::now(); diff = end - start;
        std::cout << diff.count() << " seconds\nMERGING...\n";
        start = end;

     merczLens.mergeMaps(toMergeLens);
	 merczAst5.mergeMaps(toMergeAst5);
	 merczAst10.mergeMaps(toMergeAst10);
	 merczAst15.mergeMaps(toMergeAst15);
	 merczAst1.mergeMaps(toMergeAst1);
	 merczAst2.mergeMaps(toMergeAst2);
	 merczDef5.mergeMaps(toMergeDef5);
	 merczDef10.mergeMaps(toMergeDef10);
	 merczDef15.mergeMaps(toMergeDef15);
	 merczDef1.mergeMaps(toMergeDef1);
	 merczDef2.mergeMaps(toMergeDef2);
	 merczCom5.mergeMaps(toMergeCom5);
	 merczCom10.mergeMaps(toMergeCom10);
	 merczCom15.mergeMaps(toMergeCom15);
	 merczCom1.mergeMaps(toMergeCom1);
	 merczCom2.mergeMaps(toMergeCom2);
	 merczSph5.mergeMaps(toMergeSph5);
	 merczSph10.mergeMaps(toMergeSph10);
	 merczSph15.mergeMaps(toMergeSph15);
	 merczSph1.mergeMaps(toMergeSph1);
	 merczSph2.mergeMaps(toMergeSph2);
	 merczhighOrder18.mergeMaps(toMergeHO18);
	 merczhighOrder19.mergeMaps(toMergeHO19);
	 merczhighOrder20.mergeMaps(toMergeHO20);
	 ADC.mergeMaps(toMergeADC);
	 ACS.mergeMaps(toMergeACS);
	 DCS.mergeMaps(toMergeDCS);

        end = std::chrono::system_clock::now(); diff = end - start;
        std::cout << diff.count() << " seconds\nMERGING FINISHED\n";
        start = end;


     merczLens.generateImage(soczMercz);
   	 merczAst5.generateImage(a5Mercz);
   	 merczAst10.generateImage(a10Mercz);
   	 merczAst15.generateImage(a15Mercz);
   	merczAst1.generateImage(a1Mercz);
   	merczAst2.generateImage(a2Mercz);
   	 merczDef5.generateImage(d5Mercz);
   	 merczDef10.generateImage(d10Mercz);
   	 merczDef15.generateImage(d15Mercz);
   	 merczDef1.generateImage(d1Mercz);
   	 merczDef2.generateImage(d2Mercz);
   	 merczCom5.generateImage(c5Mercz);
   	 merczCom10.generateImage(c10Mercz);
   	 merczCom15.generateImage(c15Mercz);
   	merczCom1.generateImage(c1Mercz);
   	merczCom2.generateImage(c2Mercz);
   	 merczSph5.generateImage(s5Mercz);
   	 merczSph10.generateImage(s10Mercz);
   	 merczSph15.generateImage(s15Mercz);
   	merczSph1.generateImage(s1Mercz);
   	merczSph2.generateImage(s2Mercz);
   	 merczhighOrder18.generateImage(ho18Mercz);
   	 merczhighOrder19.generateImage(ho19Mercz);
   	 merczhighOrder20.generateImage(ho20Mercz);
   	 ADC.generateImage(adcMercz);
   	 ACS.generateImage(acsMercz);
   	 DCS.generateImage(dcsMercz);

     	 end = std::chrono::system_clock::now(); diff = end - start;
     	 std::cout << diff.count() << " seconds\nPSFing...\n";
     	 start = end;

 /*   Bitmap lensPSF = fft(*(soczewka->returnBitmap()));
	lensPSF.generateImage(soczPSF);
    Bitmap merczAst5PSF = fft(merczAst5);
    Bitmap merczAst10PSF = fft(merczAst10);
    Bitmap merczAst15PSF = fft(merczAst15);
    Bitmap merczAst2PSF = fft(merczAst1);
    Bitmap merczAst1PSF = fft(merczAst2);
    Bitmap merczDef5PSF = fft(merczDef5);
    Bitmap merczDef10PSF = fft(merczDef10);
    Bitmap merczDef15PSF = fft(merczDef15);
    Bitmap merczDef1PSF = fft(merczDef1);
    Bitmap merczDef2PSF = fft(merczDef2);
    Bitmap merczCom5PSF = fft(merczCom5);
    Bitmap merczCom10PSF = fft(merczCom10);
    Bitmap merczCom15PSF = fft(merczCom15);
    Bitmap merczCom1PSF = fft(merczCom1);
    Bitmap merczCom2PSF = fft(merczCom2);
    Bitmap merczSph5PSF = fft(merczSph5);
    Bitmap merczSph10PSF = fft(merczSph10);
    Bitmap merczSph15PSF = fft(merczSph15);
    Bitmap merczSph1PSF = fft(merczSph1);
    Bitmap merczSph2PSF = fft(merczSph2);
    Bitmap merczhighOrder18PSF = fft(merczhighOrder18);
    Bitmap merczhighOrder19PSF = fft(merczhighOrder19);
    Bitmap merczhighOrder20PSF = fft(merczhighOrder20);
    Bitmap ADCPSF = fft(ADC);
    Bitmap ACSPSF = fft(ACS);
    Bitmap DCSPSF = fft(DCS);


  	 merczAst5PSF.generateImage(a5MerczPSF);
  	 merczAst10PSF.generateImage(a10MerczPSF);
  	 merczAst15PSF.generateImage(a15MerczPSF);
  	 merczAst1PSF.generateImage(a1MerczPSF);
  	 merczAst2PSF.generateImage(a2MerczPSF);
  	 merczDef5PSF.generateImage(d5MerczPSF);
  	 merczDef10PSF.generateImage(d10MerczPSF);
  	 merczDef15PSF.generateImage(d15MerczPSF);
  	merczDef1PSF.generateImage(d1MerczPSF);
  	merczDef2PSF.generateImage(d2MerczPSF);
  	 merczCom5PSF.generateImage(c5MerczPSF);
  	 merczCom10PSF.generateImage(c10MerczPSF);
  	 merczCom15PSF.generateImage(c15MerczPSF);
  	merczCom1PSF.generateImage(c1MerczPSF);
  	merczCom2PSF.generateImage(c2MerczPSF);
  	 merczSph5PSF.generateImage(s5MerczPSF);
  	 merczSph10PSF.generateImage(s10MerczPSF);
  	 merczSph15PSF.generateImage(s15MerczPSF);
  	merczSph1PSF.generateImage(s1MerczPSF);
  	merczSph2PSF.generateImage(s2MerczPSF);
  	 merczhighOrder18PSF.generateImage(ho18MerczPSF);
  	 merczhighOrder19PSF.generateImage(ho19MerczPSF);
  	 merczhighOrder20PSF.generateImage(ho20MerczPSF);
  	 ADCPSF.generateImage(adcMerczPSF);
  	 ACSPSF.generateImage(acsMerczPSF);
  	 DCSPSF.generateImage(dcsMerczPSF);
  	 */
/*
	 end = std::chrono::system_clock::now(); diff = end - start;
	 std::cout << diff.count() << " seconds\ndone\n";
*/
}


