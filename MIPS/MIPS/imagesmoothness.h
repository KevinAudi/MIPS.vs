#ifndef IMAGESMOOTHNESS_H
#define IMAGESMOOTHNESS_H

#include <QImage>
#include "imagepreprocessing.h"

class ImageSmoothness : public QImage,private ImagePreprocessing
{
	Q_OBJECT

public:
	ImageSmoothness(QObject *parent);
	~ImageSmoothness();

	QImage gaussTemplate(QImage image, MipsWeightMatrix matrix, double modulus);

private:
	
};

#endif // IMAGESMOOTHNESS_H
