#include "imagesmoothness.h"

ImageSmoothness::ImageSmoothness(QObject *parent)
	: QImage(parent)
{

}

ImageSmoothness::~ImageSmoothness()
{

}

QImage ImageSmoothness:: gaussTemplate(QImage image, MipsWeightMatrix matrix, double modulus)
{
	QImage  gaussedImage;
	if (image.format() == QImage::Format_Indexed8 && image.depth() == 8)
	{
		gaussedImage = process8BitImage(image, matrix, modulus);
	}
	else if (image.depth() == 32)
	{
		QImage gaussedRed = process8BitImage(singleColorChannel(image, RED), matrix, modulus);
		QImage gaussedGreen = process8BitImage(singleColorChannel(image, GREEN), matrix, modulus);
		QImage gaussedBlue = process8BitImage(singleColorChannel(image, BLUE), matrix, modulus);
		gaussedImage = mergeColorChannel(gaussedRed, gaussedGreen, gaussedBlue);
	}
	else
	{
		gaussedImage = image;
	}
	return gaussedImage;
}