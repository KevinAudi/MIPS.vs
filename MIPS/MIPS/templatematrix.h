#ifndef TEMPLATEMATRIX_H
#define TEMPLATEMATRIX_H
#include <QVector>

class TemplateMatrix
{
public:
	TemplateMatrix(int radius);
	~TemplateMatrix();	 

	inline int TemplateMatrix::weightAt(int xCoordinate, int yCoordinate)
	{
		return weights[(xCoordinate << power) | yCoordinate];
	}	
	void setWeightAt(int xCoordinate, int  yCoordinate, int value);
	int getRadius();	

private:
	int radius;
	int width;
	int power;
	QVector<int> weights;	
};

#endif // TEMPLATEMATRIX_H
