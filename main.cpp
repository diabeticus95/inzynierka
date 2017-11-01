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
        std::chrono::time_point<std::chrono::system_clock> start, end;
        std::chrono::duration<double> diff;

	int size = 1080;
	double probkowanie = 125000; //8 mikrometrow: 1m = x * 8um
	double f = 1.3;

        std::cout << "LENS...\n";
        start = std::chrono::system_clock::now();

	std::unique_ptr<DiffractiveStructure> soczewka = std::make_unique<Lens>(size,size, f, probkowanie, Lens::paraxial_formula);

        end = std::chrono::system_clock::now(); diff = end - start;
        std::cout << diff.count() << " seconds\nZERNIK...\n";
        start = end;


    std::unique_ptr<DiffractiveStructure> astigmatism5 = std::make_unique<Zernike>(size,size,5,Zernike::Z3);
    std::unique_ptr<DiffractiveStructure> astigmatism10 = std::make_unique<Zernike>(size,size,10,Zernike::Z3);
    std::unique_ptr<DiffractiveStructure> astigmatism15 = std::make_unique<Zernike>(size,size,15,Zernike::Z3);

    std::unique_ptr<DiffractiveStructure> defocus5 = std::make_unique<Zernike>(size,size,5,Zernike::Z4);
    std::unique_ptr<DiffractiveStructure> defocus10 = std::make_unique<Zernike>(size,size,10,Zernike::Z4);
    std::unique_ptr<DiffractiveStructure> defocus15 = std::make_unique<Zernike>(size,size,15,Zernike::Z4);

    std::unique_ptr<DiffractiveStructure> coma5 = std::make_unique<Zernike>(size,size,5,Zernike::Z7);
    std::unique_ptr<DiffractiveStructure> coma10 = std::make_unique<Zernike>(size,size,10,Zernike::Z7);
    std::unique_ptr<DiffractiveStructure> coma15 = std::make_unique<Zernike>(size,size,15,Zernike::Z7);

    std::unique_ptr<DiffractiveStructure> spherical5 = std::make_unique<Zernike>(size,size,5,Zernike::Z12);
    std::unique_ptr<DiffractiveStructure> spherical10 = std::make_unique<Zernike>(size,size,10,Zernike::Z12);
    std::unique_ptr<DiffractiveStructure> spherical15 = std::make_unique<Zernike>(size,size,15,Zernike::Z12);



    std::unique_ptr<DiffractiveStructure> highOrder18 = std::make_unique<Zernike>(size,size,10,Zernike::Z18);
    std::unique_ptr<DiffractiveStructure> highOrder19 = std::make_unique<Zernike>(size,size,10,Zernike::Z19);
    std::unique_ptr<DiffractiveStructure> highOrder20 = std::make_unique<Zernike>(size,size,10,Zernike::Z20);


        
    Bitmap merczAst5(size,size);
    Bitmap merczAst10(size,size);
    Bitmap merczAst15(size,size);
    Bitmap merczDef5(size,size);
    Bitmap merczDef10(size,size);
    Bitmap merczDef15(size,size);
    Bitmap merczCom5(size,size);
    Bitmap merczCom10(size,size);
    Bitmap merczCom15(size,size);
    Bitmap merczSph5(size,size);
    Bitmap merczSph10(size,size);
    Bitmap merczSph15(size,size);
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
	std::vector<DiffractiveStructure*> toMergeDef5;
	std::vector<DiffractiveStructure*> toMergeDef10;
	std::vector<DiffractiveStructure*> toMergeDef15;
	std::vector<DiffractiveStructure*> toMergeCom5;
	std::vector<DiffractiveStructure*> toMergeCom10;
	std::vector<DiffractiveStructure*> toMergeCom15;
	std::vector<DiffractiveStructure*> toMergeSph5;
	std::vector<DiffractiveStructure*> toMergeSph10;
	std::vector<DiffractiveStructure*> toMergeSph15;
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

	toMergeDef5.push_back(soczewka.get());
	toMergeDef5.push_back(defocus5.get());

	toMergeDef10.push_back(soczewka.get());
	toMergeDef10.push_back(defocus10.get());

	toMergeDef15.push_back(soczewka.get());
	toMergeDef15.push_back(defocus15.get());

	toMergeCom5.push_back(soczewka.get());
	toMergeCom5.push_back(coma5.get());

	toMergeCom10.push_back(soczewka.get());
	toMergeCom10.push_back(coma10.get());

	toMergeCom15.push_back(soczewka.get());
	toMergeCom15.push_back(coma15.get());

	toMergeSph5.push_back(soczewka.get());
	toMergeSph5.push_back(spherical5.get());

	toMergeSph10.push_back(soczewka.get());
	toMergeSph10.push_back(spherical10.get());

	toMergeSph15.push_back(soczewka.get());
	toMergeSph15.push_back(spherical15.get());

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
	char  d5[] = " d5.bmp";
	char  d10[] = " d10.bmp";
	char  d15[] = " d15.bmp";
	char  c5[] = " c5.bmp";
	char  c10[] = " c10.bmp";
	char  c15[] = " c15.bmp";
	char  s5[] = " s5.bmp";
	char  s10[] = " s10.bmp";
	char  s15[] = " s15.bmp";
	char  ho18[] = " ho18.bmp";
	char  ho19[] = " ho19.bmp";
	char  ho20[] = " ho20.bmp";

	char  a5Mercz[] = "a5Mercz.bmp";
	char  a10Mercz[] = "a10Mercz.bmp";
	char  a15Mercz[] = "a15Mercz.bmp";
	char  d5Mercz[] = " d5Mercz.bmp";
	char  d10Mercz[] = " d10Mercz.bmp";
	char  d15Mercz[] = " d15Mercz.bmp";
	char  c5Mercz[] = " c5Mercz.bmp";
	char  c10Mercz[] = " c10Mercz.bmp";
	char  c15Mercz[] = " c15Mercz.bmp";
	char  s5Mercz[] = " s5Mercz.bmp";
	char  s10Mercz[] = " s10Mercz.bmp";
	char  s15Mercz[] = " s15Mercz.bmp";
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
	char  d5MerczPSF[] = " d5MerczPSF.bmp";
	char  d10MerczPSF[] = " d10MerczPSF.bmp";
	char  d15MerczPSF[] = " d15MerczPSF.bmp";
	char  c5MerczPSF[] = " c5MerczPSF.bmp";
	char  c10MerczPSF[] = " c10MerczPSF.bmp";
	char  c15MerczPSF[] = " c15MerczPSF.bmp";
	char  s5MerczPSF[] = " s5MerczPSF.bmp";
	char  s10MerczPSF[] = " s10MerczPSF.bmp";
	char  s15MerczPSF[] = " s15MerczPSF.bmp";
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
     defocus5->returnBitmap()->generateImage(d5);
     defocus10->returnBitmap()->generateImage(d10);
     defocus15->returnBitmap()->generateImage(d15);
     coma5->returnBitmap()->generateImage(c5);
     coma10->returnBitmap()->generateImage(c10);
     coma15->returnBitmap()->generateImage(c15);
     spherical5->returnBitmap()->generateImage(s5);
     spherical10->returnBitmap()->generateImage(s10);
     spherical15->returnBitmap()->generateImage(s15);
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
	 merczDef5.mergeMaps(toMergeDef5);
	 merczDef10.mergeMaps(toMergeDef10);
	 merczDef15.mergeMaps(toMergeDef15);
	 merczCom5.mergeMaps(toMergeCom5);
	 merczCom10.mergeMaps(toMergeCom10);
	 merczCom15.mergeMaps(toMergeCom15);
	 merczSph5.mergeMaps(toMergeSph5);
	 merczSph10.mergeMaps(toMergeSph10);
	 merczSph15.mergeMaps(toMergeSph15);
	 merczhighOrder18.mergeMaps(toMergeHO18);
	 merczhighOrder19.mergeMaps(toMergeHO19);
	 merczhighOrder20.mergeMaps(toMergeHO20);
	 ADC.mergeMaps(toMergeADC);
	 ACS.mergeMaps(toMergeACS);
	 DCS.mergeMaps(toMergeDCS);

        end = std::chrono::system_clock::now(); diff = end - start;
        std::cout << diff.count() << " seconds\nMERGING FINISHED\n";


   	 merczAst5.generateImage(a5Mercz);
   	 merczAst10.generateImage(a10Mercz);
   	 merczAst15.generateImage(a15Mercz);
   	 merczDef5.generateImage(d5Mercz);
   	 merczDef10.generateImage(d10Mercz);
   	 merczDef15.generateImage(d15Mercz);
   	 merczCom5.generateImage(c5Mercz);
   	 merczCom10.generateImage(c10Mercz);
   	 merczCom15.generateImage(c15Mercz);
   	 merczSph5.generateImage(s5Mercz);
   	 merczSph10.generateImage(s10Mercz);
   	 merczSph15.generateImage(s15Mercz);
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
    Bitmap merczDef5PSF = fft(merczDef5);
    Bitmap merczDef10PSF = fft(merczDef10);
    Bitmap merczDef15PSF = fft(merczDef15);
    Bitmap merczCom5PSF = fft(merczCom5);
    Bitmap merczCom10PSF = fft(merczCom10);
    Bitmap merczCom15PSF = fft(merczCom15);
    Bitmap merczSph5PSF = fft(merczSph5);
    Bitmap merczSph10PSF = fft(merczSph10);
    Bitmap merczSph15PSF = fft(merczSph15);
    Bitmap merczhighOrder18PSF = fft(merczhighOrder18);
    Bitmap merczhighOrder19PSF = fft(merczhighOrder19);
    Bitmap merczhighOrder20PSF = fft(merczhighOrder20);
    Bitmap ADCPSF = fft(ADC);
    Bitmap ACSPSF = fft(ACS);
    Bitmap DCSPSF = fft(DCS);

  	 merczAst5PSF.generateImage(a5MerczPSF);
  	 merczAst10PSF.generateImage(a10MerczPSF);
  	 merczAst15PSF.generateImage(a15MerczPSF);
  	 merczDef5PSF.generateImage(d5MerczPSF);
  	 merczDef10PSF.generateImage(d10MerczPSF);
  	 merczDef15PSF.generateImage(d15MerczPSF);
  	 merczCom5PSF.generateImage(c5MerczPSF);
  	 merczCom10PSF.generateImage(c10MerczPSF);
  	 merczCom15PSF.generateImage(c15MerczPSF);
  	 merczSph5PSF.generateImage(s5MerczPSF);
  	 merczSph10PSF.generateImage(s10MerczPSF);
  	 merczSph15PSF.generateImage(s15MerczPSF);
  	 merczhighOrder18PSF.generateImage(ho18MerczPSF);
  	 merczhighOrder19PSF.generateImage(ho19MerczPSF);
  	 merczhighOrder20PSF.generateImage(ho20MerczPSF);
  	 ADCPSF.generateImage(adcMerczPSF);
  	 ACSPSF.generateImage(acsMerczPSF);
  	 DCSPSF.generateImage(dcsMerczPSF);


/*	Bitmap merczPSF = fft(mercz);
	merczPSF.generateImage(mergePSF);
	Bitmap lensPSF = fft(*(soczewka->returnBitmap()));
	lensPSF.generateImage("lensPSF.bmp");*/

	 end = std::chrono::system_clock::now(); diff = end - start;
	 std::cout << diff.count() << " seconds\ndone\n";

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


