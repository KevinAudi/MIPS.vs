#include "templatematrix.h"

TemplateMatrix::TemplateMatrix(int radius)
{
	width = 1;
	power = 0;
	this->radius = radius;
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
}

TemplateMatrix::~TemplateMatrix()
{

}

int TemplateMatrix::weightAt(int xCoordinate, int yCoordinate)
{
	 return weight[(xCoordinate << power) | yCoordinate];
}

void TemplateMatrix::setWeightAt(int xCoordinate, int  yCoordinate, int value)
{
	weight[(xCoordinate << power) | yCoordinate] = value;
}

int TemplateMatrix::getRadius()
{
	return radius;
}
