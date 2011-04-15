#ifndef TEMPLATEMATRIX_H
#define TEMPLATEMATRIX_H
#include <QVector>

class TemplateMatrix
{
public:
	TemplateMatrix(int radius);
	~TemplateMatrix();	 
	 
	//void MipsWeightMatrix(int radius);
	int weightAt(int x_coordinate, int y_coordinate);	
	void setWeightAt(int x_coordinate, int  y_coordinate, int value);
	int getRadius();	

private:
		int radius;
		int width;
		int power;
		QVector<int> weight;	
};

#endif // TEMPLATEMATRIX_H
