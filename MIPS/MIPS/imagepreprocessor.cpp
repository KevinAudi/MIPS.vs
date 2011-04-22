#include "imagepreprocessor.h"
#include <QDebug>
#include <algorithm>
#define  PI acos(-1.0)

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
	for (int x = 0; x < w; ++x)
	{
		for (int y = 0; y < h; ++y)
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
	QImage eightBitImage = image;
	int h = image.height();
	int w = image.width();
	int radius = matrix.getRadius();
	double tempPixelValue;

	 
		for (int x = radius; x <= w - radius - 1; ++x)
		{
			for (int y = radius; y <= h - radius - 1; ++y)
			{				              
				tempPixelValue = 0;
				for (int i = -radius; i <= radius; i++)
				{
					for (int j = -radius; j <= radius; j++)
					{
						tempPixelValue += image.pixelIndex(x + i, y + j) * matrix.weightAt(i + radius, j + radius);
					}
				}
				tempPixelValue *= modulus;
				uint px  = (uint)tempPixelValue;
				if(px < 0)
					px = 0;
				if(px > 255)
					px = 255;			
				//eightBitImage.setPixel( x, h - 1- y, px);	
				eightBitImage.setPixel(x, y, px);
				//image.setPixel(x, y, px * modulus);
			}
		}
	
	return eightBitImage;
	//return image;
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
		for (int x = 0; x < w; ++x)
		{
			for (int y = 0; y < h; ++y)
			{
				mergedImage.setPixel(x, y, qRgb(red.pixel(x, y), green.pixel(x, y), blue.pixel(x, y)));
			}
		}
	}
	return mergedImage;
}

int ImagePreprocessor::getMedian(int buffer[], int termsNumber)
{
	sort(buffer, buffer + termsNumber);
	return(buffer[termsNumber / 2]);
}

QImage ImagePreprocessor::process8BitImageInMF(QImage image,int flag)
{
	QImage eightBitImage = image;
	int buffer[9] = {0};
	int h = image.height();
	int w = image.width();
	int pixelValue;
	 
	if((image.format() == QImage::Format_Indexed8) && (image.depth() == 8))
	{
		for (int x = 1; x < w - 1; ++x)
		{
			for (int y= 1; y < h - 1; ++y)
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

void ImagePreprocessor::fft2D(complex<double> * pCTData, int nWidth, int nHeight, complex<double> * pCFData)
{
	int nXLev = ceilLog2(nWidth);// x��y�����У������ϵĵ�������
	int nYLev = ceilLog2(nHeight);

	int nTransWidth = (1 << nXLev);
	int nTransHeight = (1 << nYLev);


	for(int y = 0; y < nTransHeight; ++y)
	{
		// x������п��ٸ���Ҷ�任
		fft1D(&pCTData[nTransWidth * y], &pCFData[nTransWidth * y], nXLev);
	}

	// pCFData��Ŀǰ�洢��pCTData�����б任�Ľ��
	// Ϊ��ֱ������FFT_1D����Ҫ��pCFData�Ķ�ά����ת�ã���һ������FFT_1D����
	// ����Ҷ�б任��ʵ�����൱�ڶ��н��и���Ҷ�任��
	for(int y = 0; y < nTransHeight; ++y)
	{
		for(int x = 0; x < nTransWidth; ++x)
		{
			pCTData[nTransHeight * x + y] = pCFData[nTransWidth * y + x];
		}
	}

	for(int x = 0; x < nTransWidth; ++x)
	{
		// ��x������п��ٸ���Ҷ�任��ʵ�����൱�ڶ�ԭ����ͼ�����ݽ����з����
		// ����Ҷ�任
		fft1D(&pCTData[x * nTransHeight], &pCFData[x * nTransHeight], nYLev);
	}

	// pCFData��Ŀǰ�洢��pCTData������ά����Ҷ�任�Ľ��������Ϊ�˷����з���
	// �ĸ���Ҷ�任�����������ת�ã����ڰѽ��ת�û���
	for(int y = 0; y < nTransHeight; ++y)
	{
		for(int x = 0; x < nTransWidth; ++x)
		{
			pCTData[nTransWidth * y + x] = pCFData[nTransHeight * x + y];
		}
	}

	memcpy(pCTData, pCFData, sizeof(complex<double>) * nTransHeight * nTransWidth );
}

void  ImagePreprocessor::ifft2D(complex<double> * pCFData, complex<double> * pCTData, int nWidth, int nHeight)
{	
	int   nTransWidth = (1 << ceilLog2(nWidth));
	int   nTransHeight = (1 << ceilLog2(nHeight));

	// ���乤����Ҫ���ڴ�ռ�
	complex<double> *pCWork= new complex<double>[nTransWidth * nTransHeight];
	complex<double> *pCTmp ;

	// Ϊ�����ø���Ҷ���任,���԰Ѹ���ҶƵ�������ȡ����
	// Ȼ��ֱ���������任�����������Ǹ���Ҷ���任����Ĺ���
	for(int y = 0; y < nTransHeight; ++y)
	{
		for(int x = 0; x < nTransWidth; ++x)
		{
			pCTmp = &pCFData[nTransWidth * y + x] ;
			pCWork[nTransWidth * y + x] = complex<double>( pCTmp->real() , -pCTmp->imag() );
		}
	}

	// ���ø���Ҷ���任
	fft2D(pCWork, nWidth, nHeight, pCTData) ;

	// ��ʱ���Ĺ��������ս��
	// ���ݸ���Ҷ�任ԭ�����������ķ�����õĽ����ʵ�ʵ�ʱ������
	// ���һ��ϵ��
	for(int y = 0; y < nTransHeight; ++y)
	{
		for(int x = 0; x < nTransWidth; ++x)
		{
			pCTmp = &pCTData[nTransWidth * y + x] ;
			pCTData[nTransWidth * y + x] = 
				complex<double>( pCTmp->real()/(nTransWidth*nTransHeight),
				-pCTmp->imag()/(nTransWidth*nTransHeight) );
		}
	}
	delete pCWork ;
	pCWork = NULL ;
}

void ImagePreprocessor::fft1D(complex<double> * pCTData, complex<double> * pCFData, int nLevel)
{
	// ����Ҷ�任���� // ���㸵��Ҷ�任����
	int	nCount = (1 << nLevel) ;

	// �����ڴ棬�洢����Ҷ�仯��Ҫ��ϵ����
	complex<double> *pCW = new complex<double>[nCount / 2];

	// ���㸵��Ҷ�任��ϵ��
	for(int i = 0; i < nCount / 2; i++)
	{
		// �任ϵ���ĽǶ� ��2 * PI * i / nCount
		double dAngle = -2 * PI * i / nCount;
		pCW[i] = complex<double> ( cos(dAngle), sin(dAngle) );
	}

	// ���乤���ռ�
	complex<double> *pCWork1 = new complex<double>[nCount];
	complex<double> *pCWork2 = new complex<double>[nCount];


	// ��ʱ����
	complex<double> *pCTmp;

	// ��ʼ����д������
	memcpy(pCWork1, pCTData, sizeof(complex<double>) * nCount);

	// �����㷨���п��ٸ���Ҷ�任
	for(int k = 0; k < nLevel; ++k)
	{
		for(int j = 0; j < (1 << k); ++j)
		{
			//���㳤��
			int nBtFlyLen =  (1 << (nLevel-k));

			//�������ţ���Ȩ����
			for(int i = 0; i < nBtFlyLen / 2; ++i)
			{
				int nInter = j * nBtFlyLen;
				pCWork2[i + nInter] = pCWork1[i + nInter] + pCWork1[i + nInter + nBtFlyLen / 2];
				pCWork2[i + nInter + nBtFlyLen / 2] =
					(pCWork1[i + nInter] - pCWork1[i + nInter + nBtFlyLen / 2]) 
					* pCW[i * (1 << k)];
			}
		}

		// ���� pCWork1��pCWork2������
		pCTmp   = pCWork1	;
		pCWork1 = pCWork2	;
		pCWork2 = pCTmp		;
	}

	// ��������
	for(int j = 0; j < nCount; ++j)
	{
		int nInter = 0;
		for(int i = 0; i < nLevel; ++i)
		{
			if ( j & (1 << i) )
			{
				nInter += (1 << (nLevel - i - 1));
			}
		}
		pCFData[j] = pCWork1[nInter];
	}

	// �ͷ��ڴ�ռ�
	delete pCW;
	delete pCWork1;
	delete pCWork2;
}

void ImagePreprocessor::ifft1D(complex<double> * pCFData, complex<double> * pCTData, int nLevel)
{

	// ����Ҷ���任���� // ���㸵��Ҷ�任����
	int nCount = (1 << nLevel) ;

	// �任��Ҫ�Ĺ����ռ�
	complex<double> *pCWork = new complex<double>[nCount];	

	// ���乤���ռ�
	//pCWork = new complex<double>[nCount];

	// ����Ҫ���任������д�빤���ռ�pCWork
	memcpy(pCWork, pCFData, sizeof(complex<double>) * nCount);

	// Ϊ�����ø���Ҷ���任,���԰Ѹ���ҶƵ�������ȡ����
	// Ȼ��ֱ���������任�����������Ǹ���Ҷ���任����Ĺ���
	for(int i = 0; i < nCount; i++)
	{
		pCWork[i] = complex<double> (pCWork[i].real(), -pCWork[i].imag());
	}

	// ���ÿ��ٸ���Ҷ�任ʵ�ַ��任������洢��pCTData��
	fft1D(pCWork, pCTData, nLevel);

	// ��ʱ���Ĺ��������ս��
	// ���ݸ���Ҷ�任ԭ�����������ķ�����õĽ����ʵ�ʵ�ʱ������
	// ���һ��ϵ��nCount
	for(int i = 0; i < nCount; i++)
	{
		pCTData[i] = 
			complex<double> (pCTData[i].real() / nCount, -pCTData[i].imag() / nCount);
	}

	delete pCWork;
}

QImage ImagePreprocessor::process8BitImageInILP(QImage image,int filterXRadius,int filterYRadius)
{
	QImage eightBitImage = image;

	int h = image.height();
	int w = image.width();

    int transWidth = (1 << ceilLog2(w));
	int transHeight = (1 << ceilLog2(h));

	int transArea = transWidth * transHeight;


	complex<double> * pCTData = new complex<double>[transArea];
	complex<double> * pCFData = new complex<double>[transArea];

	for (int y = 0; y < transHeight; ++y)
	{
		for (int x = 0; x < transWidth; ++x)
		{			
			pCTData[y * transWidth + x] = complex<double>(0, 0);
		}
	}

	for (int y = 0; y < h; ++y)   //��DIBͼ�����ݴ���pcTData
	{
		for (int x = 0; x < w; ++x)
		{
			int tempPixelValue = eightBitImage.pixelIndex(x, h - 1 - y);			
			pCTData[y * transWidth + x] = complex<double>(tempPixelValue, 0);
		}
	}
    
	fft2D(pCTData, w, h, pCFData); // ����Ҷ���任

	for(int x = 0; x < transWidth; ++x)
	{
		for (int y = filterYRadius; y < transHeight - filterYRadius; ++y)
		{
			pCFData[x * transHeight + y] = complex<double>(0, 0);
		}
	}

	for (int x = filterXRadius; x < transWidth - filterXRadius; ++x)
	{
		for (int y = 0; y < transHeight; ++y)
		{
			pCFData[x * transHeight + y]  = complex<double>(0, 0);
		}
	}
    
	ifft2D(pCFData, pCTData, h, w); //����Ҷ���任

	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{	
			int tempPixelValue = static_cast<int>(pCTData[y*transWidth + x].real());
			tempPixelValue  = (tempPixelValue < 0) ? 0 : tempPixelValue;
			tempPixelValue = (tempPixelValue > 255) ? 255 : tempPixelValue;
			eightBitImage.setPixel(x, h - 1 - y, tempPixelValue);			
		}
	}
	delete pCTData;
	delete pCFData;
	return eightBitImage;
}

int ImagePreprocessor::ceilLog2( int value )
{
	int power = 0;
	while ((1 << power) < value)
	{
		++power;
	}
	return power;
}


QImage ImagePreprocessor::process8BitImageInBWLP(QImage image, int radius)
{
	QImage eightBitImage = image;

	int x;
	int y;	 	
	int h = image.height();
	int w = image.width();

	double tempPixelValue;		
	double dTmpOne = log((double)w) / log(2.0);
	double dTmpTwo = ceil(dTmpOne)	;
	dTmpTwo = pow(2,dTmpTwo);
	int nTransWidth = (int) dTmpTwo;	

	dTmpOne = log((double)h) / log(2.0);
	dTmpTwo = ceil(dTmpOne)	;
	dTmpTwo = pow(2,dTmpTwo);
	int nTransHeight = (int) dTmpTwo;	

	complex<double> * pCTData = pCTData=new complex<double>[nTransWidth * nTransHeight]; 
	complex<double> * pCFData = pCFData=new complex<double>[nTransWidth * nTransHeight]; 

	for(y=0; y<nTransHeight; y++)
	{
		for( x=0; x<nTransWidth; x++)
		{
			pCTData[y*nTransWidth + x]=complex<double>(0,0);	// ����
		}
	}

	for(y=0; y<h; y++)							// ��ͼ�����ݴ���pCTData
	{
		for(x=0; x<w; x++)	
		{			 
			tempPixelValue = eightBitImage.pixelIndex(x, h - 1 - y);			
			pCTData[y * nTransWidth + x] = complex<double>(tempPixelValue,0);
		}
	}	

	fft2D(pCTData, w, h, pCFData) ;			// ����Ҷ���任

	for(y = 0; y < nTransHeight; y++)						// ��ʼʵʩButterWorth��ͨ�˲�
	{
		for(x = 0; x < nTransWidth; x++)
		{
			double BWModulus = (double)(y*y+x*x) ; 
			BWModulus = BWModulus / (radius * radius); 
			BWModulus = 1.0 / (1.0+BWModulus)  ;							 
			pCFData[y*nTransWidth + x]=complex<double>(pCFData[y*nTransWidth + x].real()*BWModulus, 
				pCFData[y*nTransWidth + x].imag()*BWModulus);
		}
	}
	// ����ButterWorth��ͨ�˲���ͼ����з��任
	ifft2D(pCFData, pCTData, w, h);

	for(y = 0; y < h; y++)							// ���任�����ݴ���lpDIBBits
	{
		for(x = 0; x < w; x++)
		{
			double dReal = pCTData[y*nTransWidth + x].real() ;
			double dImaginary = pCTData[y*nTransWidth + x].imag() ;
			tempPixelValue = max(0.0,min(255.0,sqrt(dReal*dReal+dImaginary*dImaginary) ));

			uint v;
			if(tempPixelValue < 0)
				v = 0;
			else if(tempPixelValue > 255)
				v = 255;
			else
				v = ((uint)tempPixelValue) & 255;
			eightBitImage.setPixel( x, h - 1- y, v);	
		}
	}
	delete pCTData;									 
	delete pCFData;								 
	pCTData = NULL;
	pCFData = NULL;
	return eightBitImage;	
}

QImage ImagePreprocessor::process8BitImageInIHP(QImage image,int filterXRadius,int filterYRadius)
{
	QImage eightBitImage = image;

	int x;
	int y;	 	
	int h = image.height();
	int w = image.width();

	double tempPixelValue;		
	double dTmpOne = log((double)w) / log(2.0);
	double dTmpTwo = ceil(dTmpOne)	;
	dTmpTwo = pow(2,dTmpTwo);
	int nTransWidth = (int) dTmpTwo;	

	dTmpOne = log((double)h) / log(2.0);
	dTmpTwo = ceil(dTmpOne)	;
	dTmpTwo = pow(2,dTmpTwo);
	int nTransHeight = (int) dTmpTwo;	

	complex<double> * pCTData = pCTData=new complex<double>[nTransWidth * nTransHeight]; 
	complex<double> * pCFData = pCFData=new complex<double>[nTransWidth * nTransHeight]; 

	for(y = 0; y < nTransHeight; y++)
	{
		for( x = 0; x < nTransWidth; x++)
		{
			pCTData[y*nTransWidth + x] = complex<double>(0,0);	// ����
		}
	}

	for(y = 0; y < h; y++)							// ��ͼ�����ݴ���pCTData
	{
		for(x = 0; x < w; x++)	
		{			 
			tempPixelValue = eightBitImage.pixelIndex(x, h - 1 - y);			
			pCTData[y * nTransWidth + x] = complex<double>(tempPixelValue,0);
		}
	}	

	fft2D(pCTData, w, h, pCFData) ;			// ����Ҷ���任

	for(x = 0; x < nTransWidth; x++)						// ��ʼʵʩ����ĸ�ͨ�˲�
	{
		for(y = 0; y < filterYRadius; y++)
		{
			pCFData[x * nTransHeight + y] = complex<double>(0,0);
		}
		for (y = nTransHeight  - filterYRadius;y < nTransHeight;y++)
		{
			pCFData[x * nTransHeight + y] = complex<double>(0,0);
		}
	}

	for (x = 0; x < filterXRadius; x++)
	{
		for (y = 0; y < nTransHeight; y++)
		{
			pCFData[x * nTransHeight + y] = complex<double>(0,0);
		}
	}

	for (x = nTransWidth - filterXRadius; x < nTransWidth; x++)
	{
		for (y = 0; y < nTransHeight; y++)
		{
			pCFData[x * nTransHeight + y] = complex<double>(0,0);
		}
	}

	ifft2D(pCFData, pCTData, w, h);

	for(y=0; y<h; y++)							// ���任�����ݴ���lpDIBBits
	{
		for(x=0; x<w; x++)
		{
			double dReal = pCTData[y*nTransWidth + x].real() ;
			double dImaginary = pCTData[y*nTransWidth + x].imag() ;
			tempPixelValue = dReal;

			uint v;
			if(tempPixelValue < 0)
				v = 0;
			else if(tempPixelValue > 255)
				v = 255;
			else
				v = ((uint)tempPixelValue) & 255;
			eightBitImage.setPixel( x, h - 1- y, v);	
		}
	}
	delete pCTData;									 
	delete pCFData;								 
	pCTData = NULL;
	pCFData = NULL;
	return eightBitImage;	
}

QImage ImagePreprocessor::process8BitImageInBWHP(QImage image, int radius)
{
	QImage eightBitImage = image;
	int x;
	int y;	 	
	int h = image.height();
	int w = image.width();

	double tempPixelValue;		
	double dTmpOne = log((double)w) / log(2.0);
	double dTmpTwo = ceil(dTmpOne)	;
	dTmpTwo = pow(2,dTmpTwo);
	int nTransWidth = (int) dTmpTwo;	

	dTmpOne = log((double)h) / log(2.0);
	dTmpTwo = ceil(dTmpOne)	;
	dTmpTwo = pow(2,dTmpTwo);
	int nTransHeight = (int) dTmpTwo;	

	complex<double> * pCTData = pCTData=new complex<double>[nTransWidth * nTransHeight]; 
	complex<double> * pCFData = pCFData=new complex<double>[nTransWidth * nTransHeight]; 

	for(y=0; y<nTransHeight; y++)
	{
		for( x=0; x<nTransWidth; x++)
		{
			pCTData[y*nTransWidth + x]=complex<double>(0,0);	// ����
		}
	}

	for(y=0; y<h; y++)							// ��ͼ�����ݴ���pCTData
	{
		for(x=0; x<w; x++)	
		{			 
			tempPixelValue = eightBitImage.pixelIndex(x, h - 1 - y);			
			pCTData[y * nTransWidth + x] = complex<double>(tempPixelValue,0);
		}
	}	

	fft2D(pCTData, w, h, pCFData) ;			// ����Ҷ���任

	for(y = 0; y < nTransHeight; y++)						// ��ʼʵʩButterWorth��ͨ�˲�
	{
		for(x = 0; x < nTransWidth; x++)
		{
			double BWModulus = (double)(y*y+x*x) ; 
			BWModulus = (radius * radius) / BWModulus; 
			BWModulus = 1.0 / (1.0+BWModulus)  ;							 
			pCFData[y*nTransWidth + x]=complex<double>(BWModulus*(pCFData[y*nTransWidth + x].real()), 
				BWModulus*(pCFData[y*nTransWidth + x].imag()));
		}
	}
	// ����ButterWorth��ͨ�˲���ͼ����з��任
	ifft2D(pCFData, pCTData, w, h);

	for(y = 0; y < h; y++)							// ���任�����ݴ���lpDIBBits
	{
		for(x = 0; x < w; x++)
		{
			double dReal = pCTData[y*nTransWidth + x].real() ;
			double dImaginary = pCTData[y*nTransWidth + x].imag() ;
			tempPixelValue = max(0.0,min(255.0,sqrt(dReal*dReal+dImaginary*dImaginary)  + 100));

			uint px  = (uint)tempPixelValue;
			if(px < 0)
				px = 0;
			if(px > 255)
				px = 255;			
			eightBitImage.setPixel( x, h - 1- y, px);	
		}
	}
	delete pCTData;									 
	delete pCFData;								 
	pCTData = NULL;
	pCFData = NULL;
	return eightBitImage;	
}

QImage ImagePreprocessor::process8BitImageInSharpener(QImage image, TemplateMatrix matrixX,TemplateMatrix matrixY)
{
    QImage eightBitImage = image;
	int h = image.height();
	int w = image.width();
	int radius = matrixX.getRadius();	

		for (int x = radius; x <= w - radius - 1; ++x)
		{
			for (int y = radius; y <= h - radius - 1; ++y)
			{
				double pxX = 0;
				double pxY = 0;
                double tempPixelValue;

				for (int i = -radius; i <= radius; i++)
				{
					for (int j = -radius; j <= radius; j++)
					{
						pxX += image.pixelIndex(x + i, y + j) * matrixX.weightAt(i + radius, j + radius);
						pxY += image.pixelIndex(x + i, y + j) * matrixY.weightAt(i + radius, j + radius);
                        tempPixelValue = sqrt(pxX * pxX + pxY * pxY);
					}
				}
				uint px  = (uint)tempPixelValue;
				if(px < 0)
					px = 0;
				if(px > 255)
					px = 255;			
				eightBitImage.setPixel( x, y, px);					
			}
		}	
	return eightBitImage;
	//return image;
}