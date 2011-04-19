#ifndef IMAGESHARPENER_H
#define IMAGESHARPENER_H

#include <QImage>
#include "imagepreprocessor.h"

class ImageSharpener:private ImagePreprocessor
{
public:
	ImageSharpener();
	~ImageSharpener();

	//static QImage setTemplateInSharpener(QImage image,TemplateMatrix matrix, double modulus );

	static QImage useIdealHighPassFilter(QImage image, int xRadius, int yRadius);
	static QImage useButterWorthHighPassFilter(QImage image, int radius);

private:
	
};

#endif // IMAGESHARPENER_H
