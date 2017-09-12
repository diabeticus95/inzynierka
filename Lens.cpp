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
//usunac max bitmap value - powinno zawsze = 2pi.
#define M_PI 3.14159265358979323846
Lens::Lens(int max_row, int max_col, double PROBKOWANIE):DiffractiveStructure(max_row, max_col),
			probkowanie(PROBKOWANIE)
			{
	lambda = 632.8*0.000000001 * probkowanie;
	k = 2*M_PI/lambda;
	f = 1 * probkowanie;
	coeff = (double)k/(2*f);
	int MAX_ROW = bitmap->row_count;
	int MAX_COL = bitmap->col_count;

	for (int row = -MAX_ROW/2; row < MAX_ROW/2; row++){
		for (int col = -MAX_COL/2; col < MAX_COL/2; col++){
//Apertura kołowa dopasowana do zernike'a
            if( (pow(row,2) + pow(col,2)) > pow(MAX_ROW/2,2) ) {
            	bitmap->bmap[bitmap->index(row+MAX_ROW/2,col+MAX_COL/2)] = 0;
                continue;
            }
					// w przyblizeniu przyosiowym
// 2pi - wynik aby odwrocic kolory (minus przed fazą)
			bitmap->bmap[bitmap->index(row+MAX_ROW/2,col+MAX_COL/2)] = 2*M_PI - fmod(coeff*(pow(row,2) + pow(col,2)),2*M_PI);
		}
	}
}
Lens::~Lens() {
}

