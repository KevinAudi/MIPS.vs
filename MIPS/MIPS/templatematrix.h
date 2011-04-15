#ifndef TEMPLATEMATRIX_H
#define TEMPLATEMATRIX_H
#include <QVector>

class TemplateMatrix
{
public:
	TemplateMatrix(int radius);
	~TemplateMatrix();	 
<<<<<<< HEAD

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
=======
	 
	int weightAt(int x, int y);	// x and y are both coordinates
	void setWeightAt(int x, int  y, int value);
	int getRadius();	

private:
		int radius;
		int width;
		int power;
		QVector<int> weights;	
>>>>>>> 781706b6060b05aca9fb685b913b727724d14f59
};

#endif // TEMPLATEMATRIX_H
