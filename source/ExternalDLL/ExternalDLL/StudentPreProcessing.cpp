#include "StudentPreProcessing.h"
#include "basetimer.h"

// Laplacian filter
const int Laplacian[9][9] =
{
	{ 0, 0, 0,1,1,1,0,0,0 },
	{ 0, 0, 0, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 1, 1, 1, 0, 0, 0 },

	{ 1, 1, 1, -4, -4, -4, 1, 1, 1 },
	{ 1, 1, 1, -4, -4, -4, 1, 1, 1 },
	{ 1, 1, 1, -4, -4, -4, 1, 1, 1 },

	{ 0, 0, 0, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 1, 1, 1, 0, 0, 0 }

};
/**
* Functie voor het converteren van een afbeedling van rgb naar grijswaarde.
*
* @param const	RGBImage &image
*
* @return		output
*/

IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &image) const {
	// Maak een basetimer aan. De basetimer wordt gebruikt om de tijd bij te houden
	// die de implementatie gebruikt.
	BaseTimer basetimer;
	// Start de basetimer.
	basetimer.start();
	// Maak de output voor de afeelding aan.
	IntensityImageStudent * output = new IntensityImageStudent();
	// Set de hoogte en breedte van de output.
	output->set(image.getWidth(), image.getHeight());
	// Loop elke pixel van de afbeelding door.
	for (int i = 0; i < image.getWidth(); i++)
	{
		for (int ii = 0; ii < image.getHeight(); ii++)
		{
			// Maak pixel object aan.
			Intensity pixel;
			// Maak rgb object aan met de rgb waarde van de orginele afbeelding.
			RGB rgb = image.getPixel(i, ii);
			// Luma / Luminance formule voor omzetten van rbg naar grijswaarde.
			pixel = ((0.3f * rgb.r) + (0.59f*  rgb.g) + (0.11 * rgb.b));
			// Averaging formule voor omzetten van rbg naar grijswaarde.
			//pixel = ((rgb.r + rgb.g + rgb.b) / 3);
			// Luster formule voor omzetten van rbg naar grijswaarde.
			//pixel = ((std::min({ rgb.b, rgb.g, rgb.r })) + (std::max({ rgb.b, rgb.g, rgb.r })) / 2);
			// Set de outputpixel aan de nieuwe waarde.
			output->setPixel(i, ii, pixel);
		}
	}
	// Stop de timer
	basetimer.stop();
	// Schrijf de tijd dat nodig is geweest naar een output file.
	std::ofstream myfile;
	myfile.open("tijd.txt", std::ofstream::ate);
	myfile << "Luma convert tijd in s: " << basetimer.elapsedSeconds() << " tijd ms:"
		<< basetimer.elapsedMilliSeconds() << " tijd us" << basetimer.elapsedMicroSeconds();
	myfile.close();
	return output;
}

IntensityImage * StudentPreProcessing::stepScaleImage(const IntensityImage &image) const {
	return stepScaleImageFirstOrder(image);
}

/**
* Functie voor het scale van een afbeedling via zero order.
*
* @param const	RGBImage &image
*
* @return		product
*/

IntensityImage * StudentPreProcessing::stepScaleImageZeroOrder(const IntensityImage &image) const {
	// Maak basetimer aan om tijd bij te houden dat het proces kost.
	BaseTimer basetimer;
	// Start de timer.
	basetimer.start();
	double scale;
	// Bereken de schaal voor de nieuwe afbeelding.
	if (image.getHeight() * image.getWidth() > 200 * 200)
	{
		scale = sqrt(200 * 200 / static_cast<double> (image.getWidth() * image.getHeight()));
	}
	else
	{
		scale = sqrt(image.getWidth() * image.getHeight() / static_cast<double>(image.getWidth() * image.getHeight()));
	}
	// Maak de nieuwe afbeelding aan in verhouding met de schaal die hiervoor berekent is.
	IntensityImage* product = new IntensityImageStudent(image.getWidth() * scale, image.getWidth() * scale);
	// Set elke pixel van de nieuwe afbeelding volgens zero order.
	for (auto Xcord = 0; Xcord < image.getWidth() *scale; ++Xcord)
	{
		for (auto Ycord = 0; Ycord < image.getWidth()*scale; ++Ycord)
		{
			Intensity pixel = image.getPixel(std::round(scale* Xcord), std::round(scale* Ycord));
			product->setPixel(Xcord, Ycord, pixel);
		}
	}
	// Stop de timer.
	basetimer.stop();
	// Schrijf de gegevens van de timer in de betreffende tekstfile.
	std::ofstream myfile;
	myfile.open("tijdZeroOrderScale.txt", std::ofstream::ate);
	myfile << "Zero Order Scale convert tijd in s: " << basetimer.elapsedSeconds() << " tijd ms:" << basetimer.elapsedMilliSeconds() << " tijd us" << basetimer.elapsedMicroSeconds();
	myfile.close();
	// Return de nieuwe afbeelding.
	return product;
}

/**
* Functie voor het detecteren van edge in een afbeelding
*
* @param const	RGBImage &image
*
* @return		output
*/

IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const {
	// Maak een basetimer aan. De basetimer wordt gebruikt om de tijd bij te houden
	// die de implementatie gebruikt.
	BaseTimer basetimer;
	// Start de basetimer.
	basetimer.start();
	// Maak een object aan om de nieuwe afbeelding in op te slaan.
	IntensityImage * output = new IntensityImageStudent();
	// Set grootte en breedte van de nieuwe afbeelding.
	output->set(image.getWidth(), image.getHeight());
	// Pas op elke pixel het kernel toe. De randen van de afbeelding worden vermeden.
	for (int Xcord = 4; Xcord < image.getWidth() - 4; Xcord++)
	{
		for (int Ycord = 4; Ycord < image.getHeight() - 4; Ycord++)
		{
			// Variabele voor het opslaan van de pixel waarde.
			int weight = 0;
			// Doorloop het hele kernel.
			for (int i = -4; i < 5; i++)
			{
				for (int j = -4; j < 5; j++)
				{
					// Sla de pixelwaarde op.
					int pixelvalue = static_cast<int>(image.getPixel(i + Xcord, j + Ycord));
					// Sla de Laplacian waarde op.
					int laplacianvalue = Laplacian[i + 4][j + 4];
					// Bereken het nieuwe gewicht van de pixel door de pixelwaarde en laplacianwaarde
					// te vermenigvuldige en deze bij de weight op te tellen.
					weight = weight + (pixelvalue * laplacianvalue);
				}
			}
			// Wanneer de val grootte is dan bepaalde waardes pas deze aan. Dit verkomt
			// dat er meerdere verschillende soorten waardes ontstaan.
			int val = weight;
			if (val<0)
			{
				val = 0;
			}
			if (val>255) {
				val = 221;
			}
			// Set de pixel waarde in de nieuwe afbeelding.
			output->setPixel(Xcord - 4, Ycord - 4, val);
		}
	}
	// Stop de timer
	basetimer.stop();
	// Schrijf de tijd dat nodig is geweest naar een output file.
	std::ofstream myfile;
	myfile.open("tijdedge.txt", std::ofstream::ate);
	myfile << "EdgeDetectionStudent convert tijd in s: " << basetimer.elapsedSeconds() << " tijd ms:"
		<< basetimer.elapsedMilliSeconds() << " tijd us" << basetimer.elapsedMicroSeconds();
	myfile.close();
	// return de gemaakte afbeelding.
	return output;
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	// Maak een basetimer aan. De basetimer wordt gebruikt om de tijd bij te houden
	// die de implementatie gebruikt.
	BaseTimer basetimer;
	// Start de basetimer.
	basetimer.start();
	// Maak afbeelding aan voor het opslaan van de binaire afbeelding.
	IntensityImage *product = new IntensityImageStudent(image.getWidth(), image.getHeight());
	int index = 0;
	unsigned char lowest = 0;
	unsigned char highest = 0;
	unsigned char compare = 0;
	// Zoek naar de laagste pixel waarde.
	for (auto Xcord = 0; Xcord < image.getWidth(); ++Xcord)
	{
		for (auto Ycord = 0; Ycord < image.getHeight(); ++Ycord)
		{
			// Vergelijk of de pixel waarde lager is dan de lowest waarde.
			// Kleiner zet lowest gelijk aan de pixelwaarde.
			if (image.getPixel(Xcord, Ycord) < lowest)
			{
				lowest = image.getPixel(Xcord, Ycord);
			}
		}
	}
	// Zoek naar de hoogste pixel waarde.
	for (auto Xcord = 0; Xcord < image.getWidth(); ++Xcord)
	{
		for (auto Ycord = 0; Ycord < image.getHeight(); ++Ycord)
		{
			// Vergelijk of de pixel waarde groter is dan de highest waarde.
			// Groter zet highest gelijk aan de pixelwaarde.
			if (image.getPixel(Xcord, Ycord) > highest)
			{
				highest = image.getPixel(Xcord, Ycord);
			}
		}
	}

	compare = (lowest + highest) / 2;
	// Zet de pixel op zwart of wit.
	// Doorloop alle pixels in de afbeelding.
	for (auto Xcord = 0; Xcord < image.getWidth(); ++Xcord)
	{
		for (auto Ycord = 0; Ycord < image.getHeight(); ++Ycord)
		{
			// Vergelijk of de pixel waarde groter is dan de compare waarde.
			// Groter zet pixel op 0 anders op 255.
			if (image.getPixel(Xcord, Ycord) > compare)
			{
				product->setPixel(Xcord, Ycord, 0);
			}
			else
			{
				product->setPixel(Xcord, Ycord, 255);
			}
		}
	}
	// Stop de timer
	basetimer.stop();
	// Schrijf de tijd dat nodig is geweest naar een output file.
	std::ofstream myfile;
	myfile.open("tijdtresholding.txt", std::ofstream::ate);
	myfile << "ThresholdingStudent convert tijd in s: " << basetimer.elapsedSeconds() << " tijd ms:"
		<< basetimer.elapsedMilliSeconds() << " tijd us" << basetimer.elapsedMicroSeconds();
	myfile.close();
	// Return de binaire afbeelding.
	return product;
}

/**
* Functie voor het scale van een afbeedling via first order.
*
* @param const	RGBImage &image
*
* @return		product
*/

IntensityImage * StudentPreProcessing::stepScaleImageFirstOrder(const IntensityImage &image) const {
	// Maak timer aan voor het bijhouden van de procestijd.
	BaseTimer basetimer;
	// Start de timer.
	basetimer.start();
	double scale;
	// Bereken de schaal voor de nieuwe afbeelding.
	if (image.getHeight()*image.getWidth() > 200 * 200)
	{
		scale = sqrt(200 * 200 / static_cast<double>(image.getWidth() * image.getHeight()));
	}
	else
	{
		scale = sqrt(image.getWidth() * image.getHeight() / static_cast<double>(image.getWidth() * image.getHeight()));
	}
	// Maak nieuwe afbeelding aan met de betreffende schaal die hierboven berekent is.
	IntensityImage* product = new IntensityImageStudent(image.getWidth()*scale, image.getHeight()*scale);
	// Set elke pixel in de afbeelding volgens first order principe.
	for (auto Xcord = 0; Xcord < product->getWidth(); ++Xcord)
	{
		for (auto Ycord = 0; Ycord < product->getHeight(); ++Ycord)
		{
			Intensity pixel1 = image.getPixel(std::floor(Xcord * (1 / scale)), std::floor(Ycord * (1 / scale)));
			Intensity pixel2 = image.getPixel(std::floor(Xcord * (1 / scale)), std::ceil(Ycord * (1 / scale)));
			Intensity pixel3 = image.getPixel(std::ceil(Xcord * (1 / scale)), std::floor(Ycord * (1 / scale)));
			Intensity pixel4 = image.getPixel(std::ceil(Xcord * (1 / scale)), std::ceil(Ycord * (1 / scale)));
			Intensity pixel = (pixel1 + pixel2 + pixel3 + pixel4) / 4;
			product->setPixel(Xcord, Ycord, pixel);
		}
	}
	// Stop de timer.
	basetimer.stop();
	// Schrijf de uitkomst tijd van de timer in de betreffende tekstfile.
	std::ofstream myfile;
	myfile.open("tijdFirstOrderScale.txt", std::ofstream::ate);
	myfile << "First Order Scale convert tijd in s: " << basetimer.elapsedSeconds() << " tijd ms:" << basetimer.elapsedMilliSeconds() << " tijd us" << basetimer.elapsedMicroSeconds();
	myfile.close();
	// Return de output afbeelding.
	return product;
}

