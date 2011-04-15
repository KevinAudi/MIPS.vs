#include "templatematrix.h"

TemplateMatrix::TemplateMatrix(int radius) : width(1), power(0), radius(radius)
{
	while (width < 2 * radius + 1)
	{
		width <<= 1;
		power++;
	}
	this->weights = QVector<int>(width  * (2 * radius + 1));
	for (int i = 0; i < width * (2 * radius + 1); i++)
	{
		weights[i] = 0;
	}
}

TemplateMatrix::~TemplateMatrix()
{

}

void TemplateMatrix::setWeightAt(int x, int  y, int value)
{
	weights[(x << power) | y] = value;
}

int TemplateMatrix::getRadius()
{
	return radius;
}
