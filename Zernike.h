/*
 * Zernike.h
 *
 *  Created on: 25.08.2017
 *      Author: Patryk Kowalski
 */

#ifndef ZERNIKE_H_
#define ZERNIKE_H_

class Zernike {
public:

	Zernike();
	virtual ~Zernike();
private:
	double probkowanie;
	int MAX_ROW;
	int MAX_COL;
	int bit_depth;
};

#endif /* ZERNIKE_H_ */
