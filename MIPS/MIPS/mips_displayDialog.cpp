#include "mips_displayDialog.h"

DisplayImageDialog::DisplayImageDialog(QImage image,QWidget *parent) :
QDialog(parent)
{

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
}
