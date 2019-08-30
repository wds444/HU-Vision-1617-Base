#include "IntensityImageStudent.h"

IntensityImageStudent::IntensityImageStudent() : IntensityImage() {
}

IntensityImageStudent::IntensityImageStudent(const IntensityImageStudent &other) : 
	IntensityImage(other.getWidth(), other.getHeight()),
	image(new Intensity[other.getWidth() * other.getHeight()]) {
		for (int i = 0; i < getWidth(); i++) {
			image[i] = other.image[i];
		}
	}

IntensityImageStudent::IntensityImageStudent(const int width, const int height) :
	IntensityImage(width, height),
	image(new Intensity[width * height]){
	}

IntensityImageStudent::~IntensityImageStudent() {
	delete[] image;
}

void IntensityImageStudent::set(const int width, const int height) {
	IntensityImage::set(width, height);
	delete[] image;
	this->image = new Intensity[width * height];
	//TODO: resize or create a new pixel storage (Don't forget to delete the old storage)
}

void IntensityImageStudent::set(const IntensityImageStudent &other) {
	IntensityImage::set(other.getWidth(), other.getHeight());
	delete[] image;
	this->image = new Intensity[other.getWidth() * other.getHeight()];
	//TODO: resize or create a new pixel storage and copy the object (Don't forget to delete the old storage)
}

void IntensityImageStudent::setPixel(int x, int y, Intensity pixel) {
	image[x*getWidth() + y] = pixel;
	//TODO: no comment needed :)
}

void IntensityImageStudent::setPixel(int i, Intensity pixel) {
	image[i] = pixel;
	/*
	* TODO: set pixel i in "Row-Major Order"
	*
	*
	* Original 2d image (values):
	* 9 1 2
	* 4 3 5
	* 8 7 8
	*
	* 1d representation (i, value):
	* i		value
	* 0		9
	* 1		1
	* 2		2
	* 3		4
	* 4		3
	* 5		5
	* 6		8
	* 7		7
	* 8		8
	*/
}

Intensity IntensityImageStudent::getPixel(int x, int y) const {
	return image[y * getWidth() + x];
}

Intensity IntensityImageStudent::getPixel(int i) const {
	return image[i];
}