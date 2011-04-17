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
	static QImage process8BitImageInTemplate(QImage image, TemplateMatrix matrix, double modulus);
	static QImage mergeColorChannel(QImage red, QImage green, QImage blue);

	static int getMedian(int buffer[], int termsNumber); // sort and get the middle value
	static QImage process8BitImageInMF(QImage image,int flag);//flag indicates MF5 or MF9
	
};

#endif // IMAGEPREPROCESSOR_H
