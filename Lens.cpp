/*
 * Lens.cpp
 *
 *  Created on: 25.08.2017
 *      Author: Patryk Kowalski
 */

#include "Lens.h"
#include <iostream>
#include <cmath>
#include "Bitmap.h"
Lens::Lens(int max_row, int max_col, double PROBKOWANIE):DiffractiveStructure(max_row, max_col),
			probkowanie(PROBKOWANIE)
			{
	lambda = 632.8*0.000000001 * probkowanie;
	f = 1 * probkowanie;
	coeff = (double)1/(2*f*lambda);
	int MAX_ROW = bitmap->row_count;
	int MAX_COL = bitmap->col_count;
	double tmp = 0;
	for (int row = -MAX_ROW/2; row < MAX_ROW/2; row++){
		for (int col = -MAX_COL/2; col < MAX_COL/2; col++){
//Apertura kołowa dopasowana do zernike'a
            if( (pow(row,2) + pow(col,2)) > pow(MAX_ROW/2,2) ) {
            	bitmap->bmap[bitmap->index(row+MAX_ROW/2,col+MAX_COL/2)] = 0;
                continue;
            }
					// w przyblizeniu przyosiowym
// 2pi - wynik aby odwrocic kolory (minus przed fazą)
			 tmp = coeff*(pow(row,2) + pow(col,2));
			 bitmap->bmap[bitmap->index(row+MAX_ROW/2,col+MAX_COL/2)] = 1-(tmp-floor(tmp));
		}
	}
}
Lens::~Lens() {
}

