#ifndef IMAGESMOOTHER_H
#define IMAGESMOOTHER_H

#include <QImage>
#include "imagepreprocessor.h"

class ImageSmoother : private ImagePreprocessor
{
public:
	ImageSmoother();
	~ImageSmoother();

	static QImage setTemplate(QImage image, TemplateMatrix matrix, double modulus);	

    static QImage useMedianFilter(QImage image,int flag);

	static QImage useIdealLowPassFilter(QImage image, int xRadius, int yRadius);
	static QImage useButterWorthLowPassFilter(QImage image, int radius);
	

private:
	
};

#endif // IMAGESMOOTHER_H
