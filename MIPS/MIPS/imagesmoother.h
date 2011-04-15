#ifndef IMAGESMOOTHER_H
#define IMAGESMOOTHER_H

#include <QImage>
#include "imagepreprocessor.h"

class ImageSmoother : private ImagePreprocessor
{
public:
	ImageSmoother();
	~ImageSmoother();

	static QImage gaussTemplate(QImage image, TemplateMatrix matrix, double modulus);

private:
	
};

#endif // IMAGESMOOTHER_H
