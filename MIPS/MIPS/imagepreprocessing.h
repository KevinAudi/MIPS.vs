#ifndef IMAGEPREPROCESSING_H
#define IMAGEPREPROCESSING_H

#include <QImage>
#include "templatematrix.h"

class ImagePreprocessing : public QImage
{
public:
	explicit ImagePreprocessing(QWidget *parent = 0);	

	enum ColorChannel {RED = 16, GREEN = 8, BLUE = 0, ALPHA = 24};
 
	static QImage singleColorChannel(QImage image, ColorChannel channel);
	static QImage process8BitImage(QImage image, TemplateMatrix matrix, double modulus);
	static QImage mergeColorChannel(QImage red, QImage green, QImage blue);
	
};

#endif // IMAGEPREPROCESSING_H
