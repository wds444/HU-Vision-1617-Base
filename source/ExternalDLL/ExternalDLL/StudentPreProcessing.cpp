#include "StudentPreProcessing.h"
#include "IntensityImageStudent.h"
#include "ImageFactory.h"


IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &image) const {
	//create an instance of my version of the intensity image (same size as the rgb version)
	IntensityImageStudent *greyScaleImage = new IntensityImageStudent(image.getWidth(), image.getHeight());

	//instanciate a pixel
	RGB RGBpixel = {0,0,0};

	//loop trough pixels
	for (int y = 0; y < image.getHeight(); y++) {//loop height 
		for (int x = 0; x < image.getWidth(); x++) {//loop width 
			RGBpixel = image.getPixel(y, x);




		
			// average method
			//greyScaleImage->setPixel(x, y, (RGBpixel.b + RGBpixel.g + RGBpixel.r) / 3);
		

		/* //deze is niet geschikt voor gezichtsdetectie
			// lightness method takes the highest R, G, or B value and adds this with the lowest value. 
			unsigned char maxColorValue = RGBpixel.getBiggest();
			unsigned char minColorValue = RGBpixel.getSmallest();
			greyScaleImage->setPixel(x, y, (maxColorValue + minColorValue) / 2);
		*/

		
			//luma / luminance
			Intensity luminanceValue = (RGBpixel.b * 0.11) + (RGBpixel.g * 0.59) + (RGBpixel.r * 0.3);
			greyScaleImage->setPixel(x, y, luminanceValue);
		


		}
	}

return greyScaleImage;

}

IntensityImage * StudentPreProcessing::stepScaleImage(const IntensityImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	return nullptr;
}