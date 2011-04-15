#include "displayimagedialog.h"
#include "previewwidget.h"

DisplayImageDialog::DisplayImageDialog(QImage image,QWidget *parent) :
QDialog(parent)
{
	PreViewWidget *preView = new PreViewWidget(this);
	preView->setImage(image);
	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(preView);
	this->setLayout(layout);
	/*
	displayScrollArea = new QScrollArea(this);
	displayScrollArea->setWidgetResizable(true);
	scrollAreaWidgetContents = new QWidget();
	horizontalLayout = new QHBoxLayout(scrollAreaWidgetContents);
	displayLabel = new QLabel(scrollAreaWidgetContents);
	displayLabel->setPixmap(QPixmap::fromImage(image));
	horizontalLayout->addWidget(displayLabel);
	displayScrollArea->setWidget(scrollAreaWidgetContents);
	hboxLayout = new QHBoxLayout;
	this->setLayout(hboxLayout);
	hboxLayout->addWidget(displayScrollArea);
	*/
}
