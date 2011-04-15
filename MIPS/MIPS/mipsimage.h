#ifndef MIPSIMAGE_H
#define MIPSIMAGE_H

#include <QImage>
#include <QVector>
#include "templatematrix.h"
class MipsImage : public QImage
{
public:
    MipsImage();
    MipsImage(const QImage &image);
	QImage smoothnessGauss(QImage image, TemplateMatrix matrix, double modulus);
    enum ColorChannel {RED = 16, GREEN = 8, BLUE = 0, ALPHA = 24};
private:
    QImage singleColorChannel(QImage image, ColorChannel channel);
    QImage gauss8BitImage(QImage image, TemplateMatrix matrix, double modulus);
    QImage mergeColorChannel(QImage red, QImage green, QImage blue);
};

#endif // MIPSIMAGE_H
