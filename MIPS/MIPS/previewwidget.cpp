#include "previewwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStyle>

PreViewWidget::PreViewWidget(QWidget *parent) : QWidget(parent)
{

	scene = new QGraphicsScene(this);
	scene->setItemIndexMethod(QGraphicsScene::NoIndex);
	view = new QGraphicsView(scene);
	view->setDragMode(QGraphicsView::ScrollHandDrag);
	item = scene->addPixmap(QPixmap());

	int size = style()->pixelMetric(QStyle::PM_ToolBarIconSize);
	QSize iconSize(size, size);

	zoomRateSpin = new QSpinBox(this);
	zoomRateSpin->setMinimum(10);
	zoomRateSpin->setMaximum(400);
	zoomRateSpin->setSuffix(" %");
	zoomRateSpin->setButtonSymbols(QAbstractSpinBox::NoButtons);

	zoomResetBtn = new QToolButton(this);
	zoomResetBtn->setIcon(QPixmap(":/MIPS/images/zoom-100.png"));
	zoomResetBtn->setIconSize(iconSize);
	zoomFitBtn = new QToolButton(this);
	zoomFitBtn->setIcon(QPixmap(":/MIPS/images/zoom-fit.png"));
	zoomFitBtn->setIconSize(iconSize);

	zoomInBtn = new QToolButton(this);
	zoomInBtn->setAutoRepeat(true);
	zoomInBtn->setAutoRepeatInterval(33);
	zoomInBtn->setAutoRepeatDelay(0);
	zoomInBtn->setIcon(QPixmap(":/MIPS/images/zoom-in.png"));
	zoomInBtn->setIconSize(iconSize);

	zoomOutBtn = new QToolButton(this);
	zoomOutBtn->setAutoRepeat(true);
	zoomOutBtn->setAutoRepeatInterval(33);
	zoomOutBtn->setAutoRepeatDelay(0);
	zoomOutBtn->setIcon(QPixmap(":/MIPS/images/zoom-out.png"));
	zoomOutBtn->setIconSize(iconSize);


	zoomSlider = new QSlider(Qt::Horizontal, this);
	zoomSlider->setMaximum(400);
	zoomSlider->setMinimum(10);
	zoomSlider->setTickPosition(QSlider::TicksAbove);

	connect(zoomSlider, SIGNAL(valueChanged(int)), zoomRateSpin, SLOT(setValue(int)));
	connect(zoomRateSpin, SIGNAL(valueChanged(int)), zoomSlider, SLOT(setValue(int)));
	connect(zoomFitBtn, SIGNAL(clicked()), this, SLOT(zoomFit()));
	connect(zoomResetBtn, SIGNAL(clicked()), this, SLOT(zoomReset()));
	connect(zoomSlider, SIGNAL(valueChanged(int)), this, SLOT(zoomRateChange(int)));
	zoomSlider->setValue(100);

	QLayout *toolLayout = new QHBoxLayout;
	toolLayout->addWidget(zoomFitBtn);
	toolLayout->addWidget(zoomResetBtn);
	toolLayout->addWidget(zoomRateSpin);
	toolLayout->addWidget(zoomOutBtn);
	toolLayout->addWidget(zoomSlider);
	toolLayout->addWidget(zoomInBtn);


	

	QVBoxLayout *layout = new QVBoxLayout;
	layout->addLayout(toolLayout);
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

void PreViewWidget::zoomFit()
{
	zoomSlider->setValue(50);
}

void PreViewWidget::zoomReset()
{
	zoomSlider->setValue(100);
}

void PreViewWidget::zoomRateChange( int rate )
{
	qreal factor = 1.0 * rate / 100.0;
	item->setScale(factor);
	//scene->setSceneRect(item->boundingRect());
}
