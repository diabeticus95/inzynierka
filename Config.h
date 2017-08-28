/*
 * Config.h
 *
 *  Created on: 28.08.2017
 *      Author: Patryk Kowalski
 */

#ifndef CONFIG_H_
#define CONFIG_H_

class Config {
public:
	Config();
	double probkowanie;
	int bit_depth;
	double lambda;
	double k;
	int f;
	double coeff;
	int MAX_ROW;
	int MAX_COL;
};

#endif /* CONFIG_H_ */
