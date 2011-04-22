#ifndef IMAGEGRAYLEVELTRANSFORMATOR_H
#define IMAGEGRAYLEVELTRANSFORMATOR_H

#include <QImage>
#include <math.h>
#include "imagepreprocessor.h"

class ImageGrayLevelTransformator:private ImagePreprocessor
{
public:
	ImageGrayLevelTransformator();
	~ImageGrayLevelTransformator();

	static QImage transformGrayLevelInLinearity(QImage image,int oldLow,int oldHigh,int newLow,int newHigh);
    static QImage process8BitImageInGLT(QImage image,int oldLow,int oldHigh,int newLow,int newHigh);
private:
	
};

#endif // IMAGEGRAYLEVELTRANSFORMATOR_H
