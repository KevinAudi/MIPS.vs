#include "imageedgedetector.h"

ImageEdgeDetector::ImageEdgeDetector()
{

}

ImageEdgeDetector::~ImageEdgeDetector()
{

}

QImage ImageEdgeDetector::process8BitImageInED(QImage image, char flag, double scaleFactor)
{
	QImage eightBitImage = image;
	int h = image.height();
	int w = image.width();	
	int tempA;
	int tempB;
	uint px;

	for (int x = 0; x < w - 1; x++)
	{
		for (int y = 0; y < h - 1; y++)
		{
			 if ( flag == 'R'|| flag == 'r')
			 {
				 tempA = abs(image.pixelIndex(x,y) - image.pixelIndex(x + 1,y + 1));
				 tempB = abs(image.pixelIndex(x + 1,y) - image.pixelIndex(x ,y + 1));
                 px = tempA + tempB;
			 }
			 else
			 {
				 tempA = abs(image.pixelIndex(x,y) - image.pixelIndex(x ,y + 1));
				 tempB = abs(image.pixelIndex(x,y) - image.pixelIndex(x + 1 ,y));
				 switch(flag)
				 {
				 case 'M':
				 case 'm':px = tempA + tempB; break;
				 case 'H':
				 case 'h': px  = tempA; break;
				 case 'V':
				 case 'v': px  = tempB; break;
				 default: break;
				 }
			 }

			 px  *=  scaleFactor;		
			if(px < 0)
				px = 0;
			if(px > 255)
				px = 255;			
			eightBitImage.setPixel( x, y, px);					
		}
	}	
	return eightBitImage;
}

QImage ImageEdgeDetector::process8BitImageInSobel(QImage image, TemplateMatrix matrixX,TemplateMatrix matrixY,char flag, double scaleFactor)
{
	QImage eightBitImage = image;
	int h = image.height();
	int w = image.width();
	int radius = matrixX.getRadius();	

	double pxX = 0;
	double pxY = 0;
	double tempPixelValue;

	for (int x = radius; x <= w - radius - 1; ++x)
	{
		for (int y = radius; y <= h - radius - 1; ++y)
		{
			for (int i = -radius; i <= radius; i++)
			{
				for (int j = -radius; j <= radius; j++)
				{
					pxX += image.pixelIndex(x + i, y + j) * matrixX.weightAt(i + radius, j + radius);
					pxY += image.pixelIndex(x + i, y + j) * matrixY.weightAt(i + radius, j + radius);				
				}
			}
			pxX = abs(pxX);
			pxY = abs(pxY);

			switch(flag)
			{
			case 'M':
			case 'm': 
				      pxX > pxY ? tempPixelValue = pxX:tempPixelValue = pxY; break;
			case 'H':
			case 'h':
				         tempPixelValue = pxX; break;
			case 'V':
			case 'v':
				         tempPixelValue = pxY; break;
			default: break;
			}

			tempPixelValue /= scaleFactor;
			uint px  = (uint)tempPixelValue;
			if(px < 0)
				px = 0;
			if(px > 255)
				px = 255;			
			eightBitImage.setPixel( x, y, px);					
		}
	}	
	return eightBitImage;
}

QImage ImageEdgeDetector::useGradiant(QImage image,char flag,double scaleFactor)
{
	QImage processedImage;
	if (image.format() == QImage::Format_Indexed8 && image.depth() == 8)
	{
		processedImage = process8BitImageInED(image, flag,scaleFactor);
	}
	else if (image.depth() == 32)
	{
		QImage red = process8BitImageInED(singleColorChannel(image, RED), flag,scaleFactor);
		QImage green = process8BitImageInED(singleColorChannel(image, GREEN), flag,scaleFactor);
		QImage blue = process8BitImageInED(singleColorChannel(image, BLUE), flag,scaleFactor);
		processedImage = mergeColorChannel(red, green, blue);
	}
	else
	{
		processedImage = image;
	}
	return processedImage;
}

QImage ImageEdgeDetector::useSobel(QImage image,TemplateMatrix matrixX, TemplateMatrix matrixY,char flag,double scaleFactor)
{
	QImage processedImage;
	if (image.format() == QImage::Format_Indexed8 && image.depth() == 8)
	{
		processedImage = process8BitImageInSobel(image, matrixX,matrixY,flag,scaleFactor);
	}
	else if (image.depth() == 32)
	{
		QImage red = process8BitImageInSobel(singleColorChannel(image, RED), matrixX,matrixY,flag,scaleFactor);
		QImage green = process8BitImageInSobel(singleColorChannel(image, GREEN),matrixX,matrixY, flag,scaleFactor);
		QImage blue = process8BitImageInSobel(singleColorChannel(image, BLUE), matrixX,matrixY,flag,scaleFactor);
		processedImage = mergeColorChannel(red, green, blue);
	}
	else
	{
		processedImage = image;
	}
	return processedImage;
}