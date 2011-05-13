#ifndef TEMPLATEMATRIX_H
#define TEMPLATEMATRIX_H
#include <QVector>

class TemplateMatrix 
{
	public:
	TemplateMatrix(int radius);
	~TemplateMatrix();	 
	 
	void setWeightAt(int x, int  y, double value);
	double getWeightAt(int x, int y);
	int getRadius();	

private:
	int radius;
	int width;
	int power;
	QVector<double> weights;		
};

#endif // TEMPLATEMATRIX_H
