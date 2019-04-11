#include "RGBImageStudent.h"

RGBImageStudent::RGBImageStudent() : RGBImage() {
	imageVector.resize(0);
}

RGBImageStudent::RGBImageStudent(const RGBImageStudent &other) : RGBImage(other.getWidth(), other.getHeight()) {
	imageVector.resize(other.getWidth() * other.getHeight());
	for (unsigned i = 0; i < imageVector.size(); i++) {
		imageVector.at(i) = other.getPixel(i);
	}
}

RGBImageStudent::RGBImageStudent(const int width, const int height) : RGBImage(width, height) {
	imageVector.resize(width * height);
}

RGBImageStudent::~RGBImageStudent() {
	imageVector.~vector();
}

void RGBImageStudent::set(const int width, const int height) {
	RGBImage::set(width, height);
	imageVector.resize(width * height);
}

void RGBImageStudent::set(const RGBImageStudent &other) {
	RGBImage::set(other.getWidth(), other.getHeight());
	imageVector.resize(other.getWidth() * other.getHeight());
	for (unsigned i = 0; i < imageVector.size(); i++) {
		imageVector.at(i) = other.getPixel(i);
	}
}

void RGBImageStudent::setPixel(int x, int y, RGB pixel) {
	imageVector.at(y * width + x) = pixel;
}

void RGBImageStudent::setPixel(int i, RGB pixel) {
	imageVector.at(i) = pixel;
}

RGB RGBImageStudent::getPixel(int x, int y) const {
	if (x <= width && y <= height) {
		return imageVector.at(y * width + x);
	}
	return 0;
}

RGB RGBImageStudent::getPixel(int i) const {
	if ((unsigned int)i < imageVector.size()){
		return imageVector.at(i);
	}
	return 0;
}