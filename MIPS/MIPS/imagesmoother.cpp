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

