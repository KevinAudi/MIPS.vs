#ifndef IMAGEPREPROCESSOR_H
#define IMAGEPREPROCESSOR_H

#include <QImage>
#include "templatematrix.h"

class ImagePreprocessor : public QImage
{
public:
	explicit ImagePreprocessor(QWidget *parent = 0);	

	enum ColorChannel {RED = 16, GREEN = 8, BLUE = 0, ALPHA = 24};
 
	static QImage singleColorChannel(QImage image, ColorChannel channel);
	static QImage process8BitImage(QImage image, TemplateMatrix matrix, double modulus);
	static QImage mergeColorChannel(QImage red, QImage green, QImage blue);

	/*QImage processingImage;
	QImage processedImage;*/
	
};

#endif // IMAGEPREPROCESSOR_H
