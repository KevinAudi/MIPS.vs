#ifndef TEMPLATEMATRIX_H
#define TEMPLATEMATRIX_H
#include <QVector>

class TemplateMatrix
{
public:
	TemplateMatrix(int radius);
	~TemplateMatrix();	 

	inline int TemplateMatrix::weightAt(int x, int y)
	{
		return weights[(x << power) | y];
	}	
	void setWeightAt(int x, int  y, double value);
	int getRadius();	

private:
	int radius;
	int width;
	int power;
	QVector<double> weights;	
};

#endif // TEMPLATEMATRIX_H
