#include "imagegrayleveltransformator.h"

ImageGrayLevelTransformator::ImageGrayLevelTransformator()
{

}

ImageGrayLevelTransformator::~ImageGrayLevelTransformator()
{

}

QImage ImageGrayLevelTransformator::transformGrayLevelInLinearity(QImage image,int oldLow,int oldHigh,int newLow,int newHigh)
{
	QImage processedImage;
	if (image.format() == QImage::Format_Indexed8 && image.depth() == 8)
	{
		processedImage = process8BitImageInGLT(image,oldLow,oldHigh,newLow,newHigh);
	}
	else if (image.depth() == 32)
	{
		QImage red = process8BitImageInGLT(singleColorChannel(image, RED), oldLow,oldHigh,newLow,newHigh);
		QImage green = process8BitImageInGLT(singleColorChannel(image, GREEN), oldLow,oldHigh,newLow,newHigh);
		QImage blue = process8BitImageInGLT(singleColorChannel(image, BLUE), oldLow,oldHigh,newLow,newHigh);
		processedImage = mergeColorChannel(red, green, blue);
	}
	else
	{
		processedImage = image;
	}
	return processedImage;
}

QImage ImageGrayLevelTransformator::process8BitImageInGLT(QImage image,int oldLow,int oldHigh,int newLow,int newHigh)
{
	QImage eightBitImage = image;

	int w = image.width();
	int h = image.height();
	 
	int i;												 
	int j;											 
	int byMap[256];								// ����Ҷ�ӳ���
	for (i = 0; i <= oldLow; i++)								//���Ҷȼ�С��Ҫ��ǿ�ĻҶȼ�ʱ
	{
		newLow > 0 ? byMap[i] = newLow: byMap[i] = 0;		 
	}
	for (; i <= oldHigh; i++)
	{
		if (oldHigh != oldLow)								// �ж�orahig�Ƿ����oralow(��ֹĸΪ0)
		{		 
			byMap[i] = newLow + (int) ((newHigh - newLow) * (i - oldLow) / (oldHigh - oldLow));
		}
		else
		{
			byMap[i] = newLow;							//ֱ�Ӹ�ֵΪnewlow
		}
	}
	for (; i < newHigh; i++)
	{
		if (newHigh <= 255)								//�ж�d�Ƿ����255
		{
			byMap[i] = newHigh;							//ֱ�Ӹ�ֵΪnewhig
		}
		else
		{
			byMap[i] = 255;								//ֱ�Ӹ�ֵΪ255
		}
	}
	for(int y = 0; y < h;y++)							//��ͼ���ÿ������ֵ���б任
	{
		for(int x = 0; x < w; x++)						//ÿ��
		{
			// ָ��DIB��i�У���j�����ص�ָ��
			//lpSrc = (unsigned char*)lpDIBBits + lmageWidth * (lmageHeight - 1 - y) + x;
			//*lpSrc = byMap[*lpSrc];						//���µĻҶ����ԭ�еĻҶ�
			uint v  = byMap[eightBitImage.pixelIndex(x, h - 1- y)];            		
			if(v < 0)
				v = 0;
			 if(v > 255)
				v = 255;			 
			eightBitImage.setPixel( x, h - 1- y, v);	
		}
	}
	return eightBitImage;	
}
