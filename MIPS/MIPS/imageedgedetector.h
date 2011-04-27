#ifndef IMAGEEDGEDETECTOR_H
#define IMAGEEDGEDETECTOR_H

#include <QImage>
#include <math.h>
#include "imagepreprocessor.h"

class ImageEdgeDetector:private ImagePreprocessor
{
public:
	ImageEdgeDetector();
	~ImageEdgeDetector();

	static QImage useGradiant(QImage image,char flag,double scaleFactor);
	static QImage useSobel(QImage image,TemplateMatrix matrixX,TemplateMatrix matrixY,char flag,double scaleFactor);

	static QImage process8BitImageInED(QImage image, char flag,double scaleFactor);
	static QImage process8BitImageInSobel(QImage image, TemplateMatrix matrixX, TemplateMatrix matrixY,char flag,double scaleFactor);

private:
	
};

#endif // IMAGEEDGEDETECTOR_H
