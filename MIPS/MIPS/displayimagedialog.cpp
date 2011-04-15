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
}
