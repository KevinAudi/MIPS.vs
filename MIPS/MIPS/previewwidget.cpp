#include "previewwidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStyle>
#include <QDebug>

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
    
    rotateBtn = new QToolButton(this);
//	rotateBtn->setAutoRepeat(true);
//	rotateBtn->setAutoRepeatInterval(33);
//	rotateBtn->setAutoRepeatDelay(0);
	rotateBtn->setIcon(QPixmap(":/MIPS/images/rotate.png"));
	rotateBtn->setIconSize(iconSize);

	zoomSlider = new QSlider(Qt::Horizontal, this);
	zoomSlider->setMaximum(400);
	zoomSlider->setMinimum(10);
	zoomSlider->setTickPosition(QSlider::TicksAbove);

	connect(zoomSlider, SIGNAL(valueChanged(int)), zoomRateSpin, SLOT(setValue(int)));
	connect(zoomRateSpin, SIGNAL(valueChanged(int)), zoomSlider, SLOT(setValue(int)));
	connect(zoomFitBtn, SIGNAL(clicked()), this, SLOT(zoomFit()));
	connect(zoomResetBtn, SIGNAL(clicked()), this, SLOT(zoomReset()));
	connect(zoomSlider, SIGNAL(valueChanged(int)), this, SLOT(zoomRateChange(int)));
	connect(zoomInBtn, SIGNAL(clicked()), this, SLOT(zoomRateInc()));
	connect(zoomOutBtn, SIGNAL(clicked()), this, SLOT(zoomRateDec()));
	connect(rotateBtn, SIGNAL(clicked()), this, SLOT(rotateImage()));
	zoomSlider->setValue(100);

	QLayout *toolLayout = new QHBoxLayout;
	toolLayout->addWidget(zoomFitBtn);
	toolLayout->addWidget(zoomResetBtn);
	toolLayout->addWidget(zoomRateSpin);
	toolLayout->addWidget(zoomOutBtn);
	toolLayout->addWidget(zoomSlider);
	toolLayout->addWidget(zoomInBtn);
	toolLayout->addWidget(rotateBtn);

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
	viewSizeF = item->boundingRect().size();
	zoomSlider->setValue(100);
	zoomRateChange(100);
}

void PreViewWidget::zoomFit()
{
	QSizeF currentViewSize = view->size();
	double factor = currentViewSize.width() / viewSizeF.width();
	if (viewSizeF.height() * factor > currentViewSize.height())
	{
		factor = currentViewSize.height() / viewSizeF.height();
	}
	if (factor < 0.1)
	{
		factor = 0.1;
	}
	if (factor > 4)
	{
		factor = 4;
	}
	zoomSlider->setValue(100 * factor);
}

void PreViewWidget::zoomReset()
{
	zoomSlider->setValue(100);
}

void PreViewWidget::zoomRateChange( int rate )
{
	qreal factor = 1.0 * rate / 100.0;
	item->setScale(factor);
	view->setSceneRect(QRectF(QPointF(0, 0), viewSizeF * factor));
}

void PreViewWidget::zoomRateInc()
{
	zoomSlider->setValue(zoomSlider->value() + 1);
}

void PreViewWidget::zoomRateDec()
{
	zoomSlider->setValue(zoomSlider->value() - 1);
}

void PreViewWidget::rotateImage()
{
	view->rotate(90);
}