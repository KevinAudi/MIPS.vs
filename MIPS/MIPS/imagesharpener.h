#ifndef IMAGESHARPENER_H
#define IMAGESHARPENER_H

#include <QImage>
#include "imagepreprocessor.h"

class ImageSharpener:private ImagePreprocessor
{
public:
	ImageSharpener();
	~ImageSharpener();
	
	static QImage useIdealHighPassFilter(QImage image, int xRadius, int yRadius);
	static QImage useButterWorthHighPassFilter(QImage image, int radius);
	static QImage setTemplateInSharpener(QImage image, TemplateMatrix matrixX,TemplateMatrix matrixY);

private:
	
};

#endif // IMAGESHARPENER_H
