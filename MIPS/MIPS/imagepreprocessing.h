#ifndef IMAGEPREPROCESSING_H
#define IMAGEPREPROCESSING_H

#include <QImage>
#include "templatematrix.h"

class ImagePreprocessing : public QImage
{
public:
	explicit ImagePreprocessing(QWidget *parent = 0);	

	enum ColorChannel {RED = 16, GREEN = 8, BLUE = 0, ALPHA = 24};
 
	QImage singleColorChannel(QImage image, ColorChannel channel);
	QImage process8BitImage(QImage image, TemplateMatrix matrix, double modulus);
	QImage mergeColorChannel(QImage red, QImage green, QImage blue);

	QImage processingImage;
	QImage processedImage;
	
};

#endif // IMAGEPREPROCESSING_H
