#include "imagepreprocessor.h"

ImagePreprocessor::ImagePreprocessor(QWidget *parent) :
QImage()
{   

}

QImage ImagePreprocessor::singleColorChannel(QImage image, ColorChannel channel)
{
	QImage singleChannelImage(image.size(), QImage::Format_Indexed8);
	QVector<QRgb> colors(256);
	for (int i = 0; i < 256; i++)
	{
		colors[i] = qRgb(i, i, i);
	}
	singleChannelImage.setColorTable(colors);
	int w = image.width();
	int h = image.height();
	for (int x = 0; x < w; x++)
	{
		for (int y = 0; y < h; y++)
		{
			QRgb px = image.pixel(x, y);
#ifdef USE_QT_RGB
			if (channel == ImagePreprocessing::RED)
			{
				singleChannelImage.setPixel(x, y, qRed(px));
			}
			else if (channel == ImagePreprocessing::GREEN)
			{
				singleChannelImage.setPixel(x, y, qGreen(px));
			}
			else if (channel == ImagePreprocessing::BLUE)
			{
				singleChannelImage.setPixel(x, y, qBlue(px));
			}
#else
			singleChannelImage.setPixel(x, y, ((px >> channel) & 0xff));
#endif
		}
	}
	return singleChannelImage;
}

QImage ImagePreprocessor::process8BitImageInTemplate(QImage image, TemplateMatrix matrix, double modulus)
{
	//QImage eightBitImage = image;
	int h = image.height();
	int w = image.width();
	int radius = matrix.getRadius();
	if((image.format()==QImage::Format_Indexed8)&&(image.depth()==8))
	{
		for (int x = radius; x <= w - radius - 1; x++)
		{
			for (int y = radius; y <= h - radius - 1; y++)
			{
				unsigned int px = 0;
				for (int i = -radius; i <= radius; i++)
				{
					for (int j = -radius; j <= radius; j++)
					{
						px += image.pixelIndex(x + i, y + j) * matrix.weightAt(i + radius, j + radius);
					}
				}
				//eightBitImage.setPixel(x, y, px * modulus);
                  image.setPixel(x, y, px * modulus);
			}
		}
	}
	//return eightBitImage;
	return image;
}

QImage ImagePreprocessor::mergeColorChannel(QImage red, QImage green, QImage blue)
{
	QImage mergedImage;
	if (red.size() == green.size() && red.size() == blue.size())
	{
		QSize size = red.size();
		mergedImage = QImage(size, Format_RGB32);
		int w = mergedImage.width();
		int h = mergedImage.height();
		for (int x = 0; x < w; x++)
		{
			for (int y = 0; y < h; y++)
			{
				mergedImage.setPixel(x, y, qRgb(red.pixel(x, y), green.pixel(x, y), blue.pixel(x, y)));
			}
		}
	}
	return mergedImage;
}

int ImagePreprocessor::getMedian(int buffer[], int termsNumber)
{
	int i,j,temp,flag;
	for (i = 1; i < termsNumber; i++)
	{
		for (j = termsNumber - 1,flag = 0; j >=i; j--)
		{
			if (buffer[j] > buffer[j +1])
			{
				temp  = buffer[j];
				buffer[j] = buffer[j+1];
				buffer[j+1] = temp;
				flag = 1;
			}
		}
		if (flag == 0)
			break;       
	}
	return(buffer[termsNumber / 2]);
}

QImage ImagePreprocessor::process8BitImageInMF(QImage image,int flag)
{
	QImage eightBitImage = image;
	//int number = 9;
	/*QVector <int> buffer;*/
	int buffer[9] = {0};
	int h = image.height();
	int w = image.width();
	int pixelValue;
	 
	if((image.format() == QImage::Format_Indexed8) && (image.depth() == 8))
	{
		for (int x = 1; x < w - 1; x++)
		{
			for (int y= 1; y < h - 1; y++)
			{
				 buffer[0] = image.pixelIndex(x - 1,y);
				 buffer[1] = image.pixelIndex(x,y);
				 buffer[2] = image.pixelIndex(x + 1,y);
				 buffer[3] = image.pixelIndex(x,y - 1);
				 buffer[4] = image.pixelIndex(x,y +1);
				 if (flag == 9)
				 {
					 buffer[5] = image.pixelIndex(x - 1,y - 1);
					 buffer[6] = image.pixelIndex(x - 1,y +1);
					 buffer[7] = image.pixelIndex(x + 1,y - 1);
					 buffer[8] = image.pixelIndex(x + 1,y +1);
				 }
                 pixelValue = getMedian(buffer,flag);
				 if (pixelValue > 255)
				    pixelValue = 255;
				 if(pixelValue < 0)
					 pixelValue = 0;
				 eightBitImage.setPixel(x, y, pixelValue);
			}
		}
	}
	return eightBitImage;
}