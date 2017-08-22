#include <iostream>
#include "bmp/EasyBMP.h"
#include <tgmath.h>
#include <math.h>
#include "Bitmap.h"
using namespace std;

int main(int argc, char** argv){
	double lambda = 632.8*0.000000001;
	double k = 2*M_PI/lambda;
	int bit_depth = 8;
	int f = 5;
	double coeff = (double)k/(2*f);
	int MAX_ROW = 512;
	int MAX_COL = 512;
	Bitmap bitmap(MAX_ROW, MAX_COL);
	int norm = 255;
	double max_bitmap_value = 0;
	//https://stackoverfl	ow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new

	for (int row = 0; row < MAX_ROW; row++){
		for (int col = 0; col < MAX_COL; col++){
//		bitmap.bmap[bitmap.index(row,col)] = fmod(- ((-k)/(2*f)) * (pow(row,2)) + pow(col,2), 2*M_PI);
		bitmap.bmap[bitmap.index(row,col)]	= fmod(coeff*(pow(row,2) + pow(col,2)),10000000000*2*M_PI);
//		cout<<"wartosc  "<<bitmap.bmap[bitmap.index(row,col)]<<"  ";
		if (bitmap.bmap[bitmap.index(row,col)]>max_bitmap_value) max_bitmap_value = bitmap.bmap[bitmap.index(row,col)];
//		cout<<"max  "<<max_bitmap_value<<endl;
		}
	}
	//	cout << "max = "<< max_bitmap_value<<endl;
		for (int row = 0; row < MAX_ROW; row++){
				for (int col = 0; col < MAX_COL; col++){
					bitmap.bmap[bitmap.index(row,col)] = (bitmap.bmap[bitmap.index(row,col)] * norm/max_bitmap_value);
		//			cout<<bitmap.bmap[bitmap.index(row,col)]<<endl;
				}
		}

	//przyosiowe t(x,y) = exp( - (i*k)/(2*f) * (x^2 + y^2))
	BMP AnImage;
	AnImage.SetSize(MAX_ROW,MAX_COL);
	// Set its color depth to 8-bits
	AnImage.SetBitDepth(bit_depth);
	for (int row = 0; row < MAX_ROW; row++){
			for (int col = 0; col < MAX_COL; col++){
				AnImage(row,col)-> Green = bitmap.bmap[bitmap.index(row,col)];
				AnImage(row,col)-> Red = bitmap.bmap[bitmap.index(row,col)];
				AnImage(row,col)-> Blue = bitmap.bmap[bitmap.index(row,col)];
		 }
	}
//	cout << "(" << (int) AnImage(14,18)->Red << ","
//	<< (int) AnImage(14,18)->Green << ","
//	<< (int) AnImage(14,18)->Blue << ","
//	<< (int) AnImage(14,18)->Alpha << ")" << endl;
	AnImage.WriteToFile("sample.bmp");
}


