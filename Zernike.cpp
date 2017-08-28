/*
 * Zernike.cpp
 *
 *  Created on: 25.08.2017
 *      Author: Patryk Kowalski
 */
//TO DO Wypisac wszystkie zerniki w funkcje zeby nie hardcodowac modulo.
#include "Zernike.h"
#include <iostream>
#include "bmp/EasyBMP.h"
#include <tgmath.h>
#include <math.h>
#include "Bitmap.h"
Zernike::Zernike() {
	probkowanie = pow(10,5);
	MAX_ROW = 2048;
	MAX_COL = 2048;
	bit_depth = 24;
	Bitmap bitmap(MAX_ROW, MAX_COL);
	int norm = 255;
	double max_bitmap_value = 0;
	for (int row = -MAX_ROW/2; row < MAX_ROW/2; row++){
			for (int col = -MAX_COL/2; col < MAX_COL/2; col++){
			bitmap.bmap[bitmap.index(row+MAX_COL/2,col+MAX_COL/2)]	= fmod(2*row*col,2*2048*2048);
			if (bitmap.bmap[bitmap.index(row+MAX_COL/2,col+MAX_COL/2)]>max_bitmap_value) max_bitmap_value = bitmap.bmap[bitmap.index(row+MAX_COL/2,col+MAX_COL/2)];
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
		AnImage.WriteToFile("zernike32.bmp");
}

Zernike::~Zernike() {
	// TODO Auto-generated destructor stub
}

