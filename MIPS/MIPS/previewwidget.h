#pragma once
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QImage>

class PreViewWidget :
	public QWidget
{
public:
	PreViewWidget(QWidget *parent = NULL);
	~PreViewWidget();
	void setImage(QImage image);
private:
	QGraphicsScene *scene;
	QGraphicsView *view;
	QGraphicsPixmapItem *item;
};
