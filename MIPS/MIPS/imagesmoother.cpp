#include "imagesmoother.h"

ImageSmoother::ImageSmoother()
	: ImagePreprocessor()
{

}

ImageSmoother::~ImageSmoother()
{

}

QImage ImageSmoother:: setTemplate(QImage image, TemplateMatrix matrix, double modulus)
{
	QImage processedImage;
	if (image.format() == QImage::Format_Indexed8 && image.depth() == 8)
	{
		processedImage = process8BitImageInTemplate(image, matrix, modulus);
	}
	else if (image.depth() == 32)
	{
		QImage red = process8BitImageInTemplate(singleColorChannel(image, RED), matrix, modulus);
		QImage green = process8BitImageInTemplate(singleColorChannel(image, GREEN), matrix, modulus);
		QImage blue = process8BitImageInTemplate(singleColorChannel(image, BLUE), matrix, modulus);
		processedImage = mergeColorChannel(red, green, blue);
	}
	else
	{
		processedImage = image;
	}
	return processedImage;
}

QImage ImageSmoother::useMedianFilter(QImage image,int flag)
{
	QImage processedImage;
	if (image.format() == QImage::Format_Indexed8 && image.depth() == 8)
	{
		processedImage = process8BitImageInMF(image,flag);
	}
	else if (image.depth() == 32)
	{
		QImage red = process8BitImageInMF(singleColorChannel(image, RED), flag);
		QImage green = process8BitImageInMF(singleColorChannel(image, GREEN),flag);
		QImage blue = process8BitImageInMF(singleColorChannel(image, BLUE), flag);
		processedImage = mergeColorChannel(red, green, blue);
	}
	else
	{
		processedImage = image;
	}
	return processedImage;
}

QImage ImageSmoother::useIdealLowPassFilter(QImage image, int xRadius, int yRadius)
{
	QImage processedImage;
	if (image.format() == QImage::Format_Indexed8 && image.depth() == 8)
	{
		processedImage = process8BitImageInILP(image,xRadius,yRadius);
	}
	else if (image.depth() == 32)
	{
		QImage red = process8BitImageInILP(singleColorChannel(image, RED), xRadius,yRadius);
		QImage green = process8BitImageInILP(singleColorChannel(image, GREEN),xRadius,yRadius);
		QImage blue = process8BitImageInILP(singleColorChannel(image, BLUE), xRadius,yRadius);
		processedImage = mergeColorChannel(red, green, blue);
	}
	else
	{
		processedImage = image;
	}
	return processedImage;
}

QImage ImageSmoother::useButterWorthLowPassFilter(QImage image, int radius)
{
	QImage processedImage;
	if (image.format() == QImage::Format_Indexed8 && image.depth() == 8)
	{
		processedImage = process8BitImageInBWLP(image,radius);
	}
	else if (image.depth() == 32)
	{
		QImage red = process8BitImageInBWLP(singleColorChannel(image, RED), radius);
		QImage green = process8BitImageInBWLP(singleColorChannel(image, GREEN),radius);
		QImage blue = process8BitImageInBWLP(singleColorChannel(image, BLUE), radius);
		processedImage = mergeColorChannel(red, green, blue);
	}
	else
	{
		processedImage = image;
	}
	return processedImage;
}