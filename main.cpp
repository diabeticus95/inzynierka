#include <iostream>
#include "bmp/EasyBMP.h"
#include <tgmath.h>
#include <math.h>
#include "Bitmap.h"
using namespace std;
/* TO DO:
 * - dodac wersje bez przyblizenia przyosiowego
 */

int main(int argc, char** argv){
	double probkowanie = pow(10,5);
	double lambda = 632.8*0.000000001 * probkowanie;
	double k = 2*M_PI/lambda;
	int bit_depth = 4;
	int f = 1 * probkowanie;
	double coeff = (double)k/(2*f);
	int MAX_ROW = 2048;
	int MAX_COL = 2048;
	Bitmap bitmap(MAX_ROW, MAX_COL);
	int norm = 255;
	double max_bitmap_value = 0;
	for (int row = 0; row < MAX_ROW; row++){
		for (int col = 0; col < MAX_COL; col++){
			// w przyblizeniu przyosiowym
		bitmap.bmap[bitmap.index(row,col)]	= fmod(coeff*(pow(row,2) + pow(col,2)),2*M_PI);
		if (bitmap.bmap[bitmap.index(row,col)]>max_bitmap_value) max_bitmap_value = bitmap.bmap[bitmap.index(row,col)];
		}
	}
		for (int row = 0; row < MAX_ROW; row++){
				for (int col = 0; col < MAX_COL; col++){
					bitmap.bmap[bitmap.index(row,col)] = (bitmap.bmap[bitmap.index(row,col)] * norm/max_bitmap_value);
				}
		}

	BMP AnImage;
	AnImage.SetSize(MAX_ROW,MAX_COL);
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


