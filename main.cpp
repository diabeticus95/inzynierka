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
/*        std::chrono::time_point<std::chrono::system_clock> start, end;
        std::chrono::duration<double> diff;

	int size = 1080;
	double probkowanie = 125000; //8 mikrometrow: 1m = x * 8um
	double f = 1.33;
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
	toMergeAst5.push_back(soczewka.get());
	toMergeAst5.push_back(astigmatism5.get());

	toMergeAst10.push_back(soczewka.get());
	toMergeAst10.push_back(astigmatism10.get());

	toMergeAst15.push_back(soczewka.get());
	toMergeAst15.push_back(astigmatism15.get());

	toMergeAst1.push_back(soczewka.get());
	toMergeAst1.push_back(astigmatism1.get());

	toMergeAst2.push_back(soczewka.get());
	toMergeAst2.push_back(astigmatism2.get());

	toMergeDef5.push_back(soczewka.get());
	toMergeDef5.push_back(defocus5.get());

	toMergeDef10.push_back(soczewka.get());
	toMergeDef10.push_back(defocus10.get());

	toMergeDef15.push_back(soczewka.get());
	toMergeDef15.push_back(defocus15.get());

	toMergeDef1.push_back(soczewka.get());
	toMergeDef1.push_back(defocus1.get());

	toMergeDef2.push_back(soczewka.get());
	toMergeDef2.push_back(defocus2.get());

	toMergeCom5.push_back(soczewka.get());
	toMergeCom5.push_back(coma5.get());

	toMergeCom10.push_back(soczewka.get());
	toMergeCom10.push_back(coma10.get());

	toMergeCom15.push_back(soczewka.get());
	toMergeCom15.push_back(coma15.get());

	toMergeCom1.push_back(soczewka.get());
	toMergeCom1.push_back(coma1.get());

	toMergeCom2.push_back(soczewka.get());
	toMergeCom2.push_back(coma2.get());

	toMergeSph5.push_back(soczewka.get());
	toMergeSph5.push_back(spherical5.get());

	toMergeSph10.push_back(soczewka.get());
	toMergeSph10.push_back(spherical10.get());

	toMergeSph15.push_back(soczewka.get());
	toMergeSph15.push_back(spherical15.get());

	toMergeSph1.push_back(soczewka.get());
	toMergeSph1.push_back(spherical1.get());

	toMergeSph2.push_back(soczewka.get());
	toMergeSph2.push_back(spherical2.get());

	toMergeHO18.push_back(soczewka.get());
	toMergeHO18.push_back(highOrder18.get());

	toMergeHO19.push_back(soczewka.get());
	toMergeHO19.push_back(highOrder19.get());

	toMergeHO20.push_back(soczewka.get());
	toMergeHO20.push_back(highOrder20.get());

	toMergeADC.push_back(soczewka.get());
	toMergeADC.push_back(astigmatism10.get());
	toMergeADC.push_back(defocus10.get());
	toMergeADC.push_back(coma10.get());

	toMergeACS.push_back(soczewka.get());
	toMergeACS.push_back(astigmatism10.get() );
	toMergeACS.push_back(coma10.get() );
	toMergeACS.push_back(spherical10.get() );

	toMergeDCS.push_back(soczewka.get());
	toMergeDCS.push_back(defocus10.get() );
	toMergeDCS.push_back(coma10.get());
	toMergeDCS.push_back(spherical10.get() );

	char socz[] = "soczewka.bmp";
	char  a5[] = "a5.bmp";
	char  a10[] = "a10.bmp";
	char  a15[] = "a15.bmp";
	char  a1[] = "a1.bmp";
	char  a2[] = "a2.bmp";
	char  d5[] = " d5.bmp";
	char  d10[] = " d10.bmp";
	char  d15[] = " d15.bmp";
	char  d1[] = " d1.bmp";
	char  d2[] = " d2.bmp";
	char  c5[] = " c5.bmp";
	char  c10[] = " c10.bmp";
	char  c15[] = " c15.bmp";
	char  c1[] = " c1.bmp";
	char  c2[] = " c2.bmp";
	char  s5[] = " s5.bmp";
	char  s10[] = " s10.bmp";
	char  s15[] = " s15.bmp";
	char  s1[] = " s1.bmp";
	char  s2[] = " s2.bmp";
	char  ho18[] = " ho18.bmp";
	char  ho19[] = " ho19.bmp";
	char  ho20[] = " ho20.bmp";

	char  a5Mercz[] = "a5Mercz.bmp";
	char  a10Mercz[] = "a10Mercz.bmp";
	char  a15Mercz[] = "a15Mercz.bmp";
	char  a1Mercz[] = "a1Mercz.bmp";
	char  a2Mercz[] = "a2Mercz.bmp";
	char  d5Mercz[] = " d5Mercz.bmp";
	char  d10Mercz[] = " d10Mercz.bmp";
	char  d15Mercz[] = " d15Mercz.bmp";
	char  d1Mercz[] = " d1Mercz.bmp";
	char  d2Mercz[] = " d2Mercz.bmp";
	char  c5Mercz[] = " c5Mercz.bmp";
	char  c10Mercz[] = " c10Mercz.bmp";
	char  c15Mercz[] = " c15Mercz.bmp";
	char  c1Mercz[] = " c1Mercz.bmp";
	char  c2Mercz[] = " c2Mercz.bmp";
	char  s5Mercz[] = " s5Mercz.bmp";
	char  s10Mercz[] = " s10Mercz.bmp";
	char  s15Mercz[] = " s15Mercz.bmp";
	char  s1Mercz[] = " s1Mercz.bmp";
	char  s2Mercz[] = " s2Mercz.bmp";
	char  ho18Mercz[] = " ho18Mercz.bmp";
	char  ho19Mercz[] = " ho19Mercz.bmp";
	char  ho20Mercz[] = " ho20Mercz.bmp";
	char  adcMercz[] = " ADCMercz.bmp";
	char  acsMercz[] = " ACSMercz.bmp";
	char  dcsMercz[] = " DCSMercz.bmp";

	char soczPSF[] = "soczewkaPSF.bmp";
	char  a5MerczPSF[] = "a5MerczPSF.bmp";
	char  a10MerczPSF[] = "a10MerczPSF.bmp";
	char  a15MerczPSF[] = "a15MerczPSF.bmp";
	char  a1MerczPSF[] = "a1MerczPSF.bmp";
	char  a2MerczPSF[] = "a2MerczPSF.bmp";
	char  d5MerczPSF[] = " d5MerczPSF.bmp";
	char  d10MerczPSF[] = " d10MerczPSF.bmp";
	char  d15MerczPSF[] = " d15MerczPSF.bmp";
	char  d1MerczPSF[] = " d1MerczPSF.bmp";
	char  d2MerczPSF[] = " d2MerczPSF.bmp";
	char  c5MerczPSF[] = " c5MerczPSF.bmp";
	char  c10MerczPSF[] = " c10MerczPSF.bmp";
	char  c15MerczPSF[] = " c15MerczPSF.bmp";
	char  c1MerczPSF[] = " c1MerczPSF.bmp";
	char  c2MerczPSF[] = " c2MerczPSF.bmp";
	char  s5MerczPSF[] = " s5MerczPSF.bmp";
	char  s10MerczPSF[] = " s10MerczPSF.bmp";
	char  s15MerczPSF[] = " s15MerczPSF.bmp";
	char  s1MerczPSF[] = " s1MerczPSF.bmp";
	char  s2MerczPSF[] = " s2MerczPSF.bmp";
	char  ho18MerczPSF[] = " ho18MerczPSF.bmp";
	char  ho19MerczPSF[] = " ho19MerczPSF.bmp";
	char  ho20MerczPSF[] = " ho20MerczPSF.bmp";
	char  adcMerczPSF[] = " ADCMerczPSF.bmp";
	char  acsMerczPSF[] = " ACSMerczPSF.bmp";
	char  dcsMerczPSF[] = " DCSMerczPSF.bmp";


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


 //   Bitmap transform = fft(*(wielomian5->returnBitmap()));


//	transform.generateImage(psf);
	//transform.printMap();

        end = std::chrono::system_clock::now(); diff = end - start;
        std::cout << diff.count() << " seconds\nMERGING...\n";
        start = end;
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

    Bitmap lensPSF = fft(*(soczewka->returnBitmap()));
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

	 end = std::chrono::system_clock::now(); diff = end - start;
	 std::cout << diff.count() << " seconds\ndone\n";

*/
	char fileName[] = "cropped.bmp";
	Bitmap rot = rot90(fileName);
	Bitmap rot180(rot);
	rot180.rot90();
	rot180.generateImage("rot180.bmp");
}


