/*
* Copyright (c) 2015 DottedEye Designs, Alexander Hustinx, NeoTech Software, Rolf Smit - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
*/

#pragma once



struct RGB {

	RGB(unsigned char r = 0, unsigned char g = 0, unsigned char b = 0)
		:r(r), g(g), b(b){
	}

	unsigned char b;
	unsigned char g;
	unsigned char r;

	unsigned char getSmallest() {
		unsigned char min = r;
		if (g < min) {
			min = g;
		}
		if (b < min) {
			min = b;
		}
		return min;
	}

	// is het de bedoeling dat ik deze file ook edit? zo niet, have a free pun :P

	unsigned char getBiggest() {//Gheghe, biggus (dickus)
		unsigned char max = r;
		if (g > max) {
			max = g;
		}
		if (b > max) {
			max = b;
		}
		return max;
	}
};

typedef unsigned char Intensity;