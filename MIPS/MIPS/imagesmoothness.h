#ifndef IMAGESMOOTHNESS_H
#define IMAGESMOOTHNESS_H

#include <QImage>
#include "imagepreprocessing.h"

class ImageSmoothness : private ImagePreprocessing
{
public:
	ImageSmoothness(QObject *parent);
	~ImageSmoothness();

	QImage gaussTemplate(QImage image, TemplateMatrix matrix, double modulus);

private:
	
};

#endif // IMAGESMOOTHNESS_H
