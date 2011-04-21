#ifndef IMAGEPREPROCESSOR_H
#define IMAGEPREPROCESSOR_H

#include <QImage>
#include "templatematrix.h"
#include <complex>
#include <math.h>

using namespace std;

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

	static QImage process8BitImageInILP(QImage image,int filterXRadius,int filterYRadius);
	static QImage process8BitImageInBWLP(QImage image, int radius);

	static void fft2D(complex<double> * pCTData, int nWidth, int nHeight, complex<double> * pCFData);
	static void ifft2D(complex<double> * pCFData, complex<double> * pCTData, int nWidth, int nHeight);
    static void fft1D(complex<double> * pCTData, complex<double> * pCFData, int nLevel);
    static void ifft1D(complex<double> * pCFData, complex<double> * pCTData, int nLevel);

	static QImage process8BitImageInIHP(QImage image,int filterXRadius,int filterYRadius);
	static QImage process8BitImageInBWHP(QImage image, int radius);

	static QImage process8BitImageInSharpener(QImage image, TemplateMatrix matrixX,TemplateMatrix matrixY);

	//static const double PI = acos(-1.0);
private:
	static int ceilLog2(int value); 
};

#endif // IMAGEPREPROCESSOR_H
