#include "IntensityImageStudent.h"

IntensityImageStudent::IntensityImageStudent() : IntensityImage() {
	intensityVector.resize(0);
}

IntensityImageStudent::IntensityImageStudent(const IntensityImage &other) 
	: IntensityImage(other.getWidth(), other.getHeight()) {
	intensityVector.resize(other.getWidth() * other.getHeight());
	for (unsigned i = 0; i < intensityVector.size(); i++) {
		intensityVector.at(i) = other.getPixel(i);
	}
}

IntensityImageStudent::IntensityImageStudent(const RGBImage &RGB) 
	: IntensityImage(RGB.getWidth(), RGB.getHeight()) {
	intensityVector.resize(RGB.getWidth() * RGB.getHeight());
	for (unsigned i = 0; i < intensityVector.size(); i++) {
		intensityVector.at(i) = static_cast<unsigned char>(
			RGB.getPixel(i).r * redConversionGrade
			+ RGB.getPixel(i).g * greenConversionGrade
			+ RGB.getPixel(i).b * blueConversionGrade);
	}
}

IntensityImageStudent::IntensityImageStudent(const int width, const int height) 
	: IntensityImage(width, height) {
	intensityVector.resize(width * height);
}

IntensityImageStudent::~IntensityImageStudent() {
	intensityVector.~vector();
}

void IntensityImageStudent::set(const int width, const int height) {
	IntensityImage::set(width, height);
	intensityVector.resize(width * height);
}

void IntensityImageStudent::set(const IntensityImageStudent &other) {
	IntensityImage::set(other.getWidth(), other.getHeight());
	intensityVector.resize(other.getWidth() * other.getHeight());
	for (unsigned i = 0; i < intensityVector.size(); i++) {
		intensityVector.at(i) = other.getPixel(i);
	}
}

void IntensityImageStudent::setPixel(int x, int y, Intensity pixel) {
	intensityVector.at(y * width + x) = pixel;
}

void IntensityImageStudent::setPixel(int i, Intensity pixel) {
	intensityVector.at(i) = pixel;
}

Intensity IntensityImageStudent::getPixel(int x, int y) const {
	if (x < width && y < height) {
		return intensityVector.at(y * width + x);
	}
	return 0;
}

Intensity IntensityImageStudent::getPixel(int i) const {
	if ((unsigned int)i < intensityVector.size()){
		return intensityVector.at(i);
	}
	return 0;
}