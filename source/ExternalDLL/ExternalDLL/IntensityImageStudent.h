/*
* Copyright (c) 2015 DottedEye Designs, Alexander Hustinx, NeoTech Software, Rolf Smit - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
*/

#pragma once
#include "IntensityImage.h"
#include "RGBImageStudent.h"
#include <vector>

//! Student implementation of a class representing an IntensityImage
/*!
 *	\author Nicky van Steensel van der Aa
 */
class IntensityImageStudent : public IntensityImage {
public:
	IntensityImageStudent();
	~IntensityImageStudent();

	IntensityImageStudent(const IntensityImage &other);
	IntensityImageStudent(const RGBImage &RGB);
	IntensityImageStudent(const int width, const int height);

	void set(const int width, const int height);
	void set(const IntensityImageStudent &other);

	void setPixel(int x, int y, Intensity pixel);
	void setPixel(int i, Intensity pixel);

	Intensity getPixel(int x, int y) const;
	Intensity getPixel(int i) const;
private:
	std::vector<Intensity> intensityVector;

	//Bron van waardes in implementatieplan
	const float redConversionGrade = 0.3000f;
	const float greenConversionGrade = 0.5900f;
	const float blueConversionGrade = 1.0f - redConversionGrade - greenConversionGrade;
};