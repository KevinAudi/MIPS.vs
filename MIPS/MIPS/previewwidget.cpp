#include "previewwidget.h"
#include <QVBoxLayout>

PreViewWidget::PreViewWidget(QWidget *parent) : QWidget(parent)
{
	scene = new QGraphicsScene(this);
	scene->setItemIndexMethod(QGraphicsScene::NoIndex);
	//scene->setSceneRect(0, 0, 1000, 1000);
	view = new QGraphicsView(scene);
	view->setDragMode(QGraphicsView::ScrollHandDrag);
	item = scene->addPixmap(QPixmap());

	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(view);
	this->setLayout(layout);
}

PreViewWidget::~PreViewWidget(void)
{
}

void PreViewWidget::setImage( QImage image )
{
	item->setPixmap(QPixmap::fromImage(image));
}
