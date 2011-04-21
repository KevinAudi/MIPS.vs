#include "imagesharpener.h"

ImageSharpener::ImageSharpener()
{

}

ImageSharpener::~ImageSharpener()
{

}

QImage ImageSharpener::useIdealHighPassFilter(QImage image, int xRadius, int yRadius)
{
	QImage processedImage;
	if (image.format() == QImage::Format_Indexed8 && image.depth() == 8)
	{
		processedImage = process8BitImageInIHP(image,xRadius,yRadius);
	}
	else if (image.depth() == 32)
	{
		QImage red = process8BitImageInIHP(singleColorChannel(image, RED), xRadius,yRadius);
		QImage green = process8BitImageInIHP(singleColorChannel(image, GREEN),xRadius,yRadius);
		QImage blue = process8BitImageInIHP(singleColorChannel(image, BLUE), xRadius,yRadius);
		processedImage = mergeColorChannel(red, green, blue);
	}
	else
	{
		processedImage = image;
	}
	return processedImage;
}

QImage ImageSharpener::useButterWorthHighPassFilter(QImage image, int radius)
{
	QImage processedImage;
	if (image.format() == QImage::Format_Indexed8 && image.depth() == 8)
	{
		processedImage = process8BitImageInBWHP(image,radius);
	}
	else if (image.depth() == 32)
	{
		QImage red = process8BitImageInBWHP(singleColorChannel(image, RED), radius);
		QImage green = process8BitImageInBWHP(singleColorChannel(image, GREEN),radius);
		QImage blue = process8BitImageInBWHP(singleColorChannel(image, BLUE), radius);
		processedImage = mergeColorChannel(red, green, blue);
	}
	else
	{
		processedImage = image;
	}
	return processedImage;
}

QImage ImageSharpener::setTemplateInSharpener(QImage image, TemplateMatrix matrixX,TemplateMatrix matrixY)
{
	QImage processedImage;
	if (image.format() == QImage::Format_Indexed8 && image.depth() == 8)
	{
		processedImage = process8BitImageInSharpener(image, matrixX, matrixY);
	}
	else if (image.depth() == 32)
	{
		QImage red = process8BitImageInSharpener(singleColorChannel(image, RED), matrixX, matrixY);
		QImage green = process8BitImageInSharpener(singleColorChannel(image, GREEN), matrixX, matrixY);
		QImage blue = process8BitImageInSharpener(singleColorChannel(image, BLUE), matrixX, matrixY);
		processedImage = mergeColorChannel(red, green, blue);
	}
	else
	{
		processedImage = image;
	}
	return processedImage;
}