#include "templatematrix.h"

TemplateMatrix::TemplateMatrix(QObject *parent)
	: QMatrix(parent)
{

}

TemplateMatrix::~TemplateMatrix()
{

}

void TemplateMatrix:: MipsWeightMatrix(int radius)
{
	width = 1;
	power = 0;
	while (width < 2 * radius + 1)
	{
		width <<= 1;
		power++;
	}
	this->weight = QVector<int>(width  * (2 * radius + 1));
	for (int i = 0; i < width * (2 * radius + 1); i++)
	{
		weight[i] = 0;
	}
	this->radius = radius;
}

int TemplateMatrix::weightAt(int x_coordinate, int y_coordinate)
{
	 return weight[(x_coordinate << power) | y_coordinate];
}

void TemplateMatrix::setWeightAt(int x_coordinate, int  y_coordinate, int value)
{
	weight[(x_coordinate << power) | y_coordinate] = value;
}

int TemplateMatrix::getRadius()
{
	return radius;
}
