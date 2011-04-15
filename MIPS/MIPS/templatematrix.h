#ifndef TEMPLATEMATRIX_H
#define TEMPLATEMATRIX_H
#include <QVector>

class TemplateMatrix
{
public:
	TemplateMatrix(int radius);
	~TemplateMatrix();	 
	 
	int weightAt(int x, int y);	// x and y are both coordinates
	void setWeightAt(int x, int  y, int value);
	int getRadius();	

private:
		int radius;
		int width;
		int power;
		QVector<int> weights;	
};

#endif // TEMPLATEMATRIX_H
