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
	int byMap[256];								// 定义灰度映射表
	for (i = 0; i <= oldLow; i++)								//当灰度级小于要增强的灰度级时
	{
		newLow > 0 ? byMap[i] = newLow: byMap[i] = 0;		 
	}
	for (; i <= oldHigh; i++)
	{
		if (oldHigh != oldLow)								// 判断orahig是否等于oralow(防止母为0)
		{		 
			byMap[i] = newLow + (int) ((newHigh - newLow) * (i - oldLow) / (oldHigh - oldLow));
		}
		else
		{
			byMap[i] = newLow;							//直接赋值为newlow
		}
	}
	for (; i < newHigh; i++)
	{
		if (newHigh <= 255)								//判断d是否大于255
		{
			byMap[i] = newHigh;							//直接赋值为newhig
		}
		else
		{
			byMap[i] = 255;								//直接赋值为255
		}
	}
	for(int y = 0; y < h;y++)							//对图像的每个像素值进行变换
	{
		for(int x = 0; x < w; x++)						//每列
		{
			// 指向DIB第i行，第j个象素的指针
			//lpSrc = (unsigned char*)lpDIBBits + lmageWidth * (lmageHeight - 1 - y) + x;
			//*lpSrc = byMap[*lpSrc];						//用新的灰度替代原有的灰度
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
