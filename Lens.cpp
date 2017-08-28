/*
 * Lens.cpp
 *
 *  Created on: 25.08.2017
 *      Author: Patryk Kowalski
 */

#include "Lens.h"
#include <iostream>
#include "bmp/EasyBMP.h"
#include <tgmath.h>
#include <math.h>
#include "Bitmap.h"
Lens::Lens() {
	probkowanie = pow(10,5);
	lambda = 632.8*0.000000001 * probkowanie;
	k = 2*M_PI/lambda;
	bit_depth = 24;
	f = 1 * probkowanie;
	coeff = (double)k/(2*f);
	MAX_ROW = 2048;
	MAX_COL = 2048;
	bitmap = new Bitmap(MAX_ROW, MAX_COL);
	norm = 255;
	max_bitmap_value = 0;

	for (int row = 0; row < MAX_ROW; row++){
			for (int col = 0; col < MAX_COL; col++){
				// w przyblizeniu przyosiowym
			bitmap->bmap[bitmap->index(row,col)]	= fmod(coeff*(pow(row,2) + pow(col,2)),2*M_PI);
			if (bitmap->bmap[bitmap->index(row,col)]>max_bitmap_value) max_bitmap_value = bitmap->bmap[bitmap->index(row,col)];
			}
		}
			for (int row = 0; row < MAX_ROW; row++){
					for (int col = 0; col < MAX_COL; col++){
						bitmap->bmap[bitmap->index(row,col)] = (bitmap->bmap[bitmap->index(row,col)] * norm/max_bitmap_value);
					}
			}

		BMP AnImage;
		AnImage.SetSize(MAX_ROW,MAX_COL);
		AnImage.SetBitDepth(bit_depth);
		for (int row = 0; row < MAX_ROW; row++){
				for (int col = 0; col < MAX_COL; col++){
					AnImage(row,col)-> Green = bitmap->bmap[bitmap->index(row,col)];
					AnImage(row,col)-> Red = bitmap->bmap[bitmap->index(row,col)];
					AnImage(row,col)-> Blue = bitmap->bmap[bitmap->index(row,col)];
			 }
		}
	//	cout << "(" << (int) AnImage(14,18)->Red << ","
	//	<< (int) AnImage(14,18)->Green << ","
	//	<< (int) AnImage(14,18)->Blue << ","
	//	<< (int) AnImage(14,18)->Alpha << ")" << endl;
		AnImage.WriteToFile("example.bmp");
}

Lens::~Lens() {
	// TODO Auto-generated destructor stub
}

