#include "RGBImageStudent.h"

RGBImageStudent::RGBImageStudent() : RGBImage() {
}

RGBImageStudent::RGBImageStudent(const RGBImageStudent &other) : 
	RGBImage(other.getWidth(), other.getHeight()),
	image(new RGB[other.getWidth() * other.getHeight()])
	{
		for (int i = 0; i < getWidth(); i++) {
			image[i] = other.image[i];
		}
}


RGBImageStudent::RGBImageStudent(const int width, const int height) : 
	RGBImage(width, height),
	image(new RGB[width * height]){
}

RGBImageStudent::~RGBImageStudent() {
	delete[] image;
}

void RGBImageStudent::set(const int width, const int height) {
	RGBImage::set(width, height);
	delete[] image;
	this->image = new RGB[width, height];
}

void RGBImageStudent::set(const RGBImageStudent &other) {
	RGBImage::set(other.getWidth(), other.getHeight());
	delete[] image;
	this->image = new RGB[other.getWidth() * other.getHeight()];
}

void RGBImageStudent::setPixel(int x, int y, RGB pixel) {
	image[x*getWidth() + y] = pixel;
}

void RGBImageStudent::setPixel(int i, RGB pixel) {
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

RGB RGBImageStudent::getPixel(int x, int y) const {
	return image[y * getWidth() + x];
}

RGB RGBImageStudent::getPixel(int i) const {
	
	return image[i];
}