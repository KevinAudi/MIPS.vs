#include "templatematrix.h"

TemplateMatrix::TemplateMatrix(int radius) : width(1), power(0), radius(radius)
{
	while (width < 2 * radius + 1)
	{
		width <<= 1;
		power++;
	}
	this->weights = QVector<double>(width  * (2 * radius + 1), 0);
}

TemplateMatrix::~TemplateMatrix()
{

}

void TemplateMatrix::setWeightAt(int x, int  y, double value)
{
	weights[(x << power) | y] = value;
}

int TemplateMatrix::getRadius()
{
	return radius;
}
