#pragma once
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QSlider>
#include <QToolButton>
#include <QLabel>
#include <QSpinBox>
#include <QSizeF>

class PreViewWidget :
	public QWidget
{
	Q_OBJECT
public:
	PreViewWidget(QWidget *parent = NULL);
	~PreViewWidget();
	void setImage(QImage image);

private:
	QGraphicsScene *scene;
	QGraphicsView *view;
	QGraphicsPixmapItem *item;	
	QSlider *zoomSlider;
	QToolButton *zoomInBtn;
	QToolButton *zoomOutBtn;
	QToolButton *rotateBtn;
	QSpinBox *zoomRateSpin;
	QToolButton *zoomResetBtn;
	QToolButton *zoomFitBtn;
	QSizeF viewSizeF;

private slots:
	void zoomFit();
	void zoomReset();
	void zoomRateChange(int rate);
	void zoomRateInc();
	void zoomRateDec();
	void rotateImage();
};
