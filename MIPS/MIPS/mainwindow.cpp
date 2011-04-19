#include <QMessageBox>
#include <QHeaderView>
#include <QScrollBar>
#include <QImageReader>

#include "mainwindow.h"
#include "imagesmoother.h"
#include "imagesharpener.h"

//#include <iostream>
//using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), scaleFactor(1)
{
    setupUi(this);

    QObject::connect(actionGauss_2,SIGNAL(triggered()),this,SLOT(slotGaussInSmoother()));
	QObject::connect(actionBox_2,SIGNAL(triggered()),this,SLOT(slotBoxInSmoother()));
	QObject::connect(actionEight_2,SIGNAL(triggered()),this,SLOT(slotEightInSmoother()));
	QObject::connect(actionTen_2,SIGNAL(triggered()),this,SLOT(slotTenInSmoother()));
	QObject::connect(actionMF5,SIGNAL(triggered()),this,SLOT(slotMF5InSmoother()));
	QObject::connect(actionMF9,SIGNAL(triggered()),this,SLOT(slotMF9InSmoother()));
	QObject::connect(actionIdeal_Low_Pass_Filter,SIGNAL(triggered()),this,SLOT(slotILPFInSmoother()));
    QObject::connect(actionButter_Worth_LP_Filter,SIGNAL(triggered()),this,SLOT(slotBWLPFInSmoother()));	

	QObject::connect(actionIdeal_High_Pass_Filter,SIGNAL(triggered()),this,SLOT(slotIHPFInSharpener()));
	QObject::connect(actionButter_Worth_HP_Filter,SIGNAL(triggered()),this,SLOT(slotBWHPFInSharpener()));	

    QObject::connect(actionLaplacian,SIGNAL(triggered()),this,SLOT(slotLaplacianInSharpener()));

    dirModel = new QDirModel(this);
    dirModel->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);

    currentDirectory = new QDir();

    imageInfo = new QLabel(this);
    imageInfo->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    imageInfo->setAlignment(Qt::AlignCenter);

    mainToolBar->addWidget(imageInfo);

    treeView->setModel(dirModel);
    treeView->header()->setVisible(false);
    treeView->setColumnHidden(1,true);	// Size
    treeView->setColumnHidden(2,true);  // Type
    treeView->setColumnHidden(3,true);  // Modified Date

    foreach (QByteArray byteArray, QImageReader::supportedImageFormats())
    {
        QString extra = QString("*.") + QString(byteArray);
        supportedFormat << extra;
    }

    resize(800,600);
    currentFile = displayFiles.constBegin();  

    updateUi();
}

MainWindow::~MainWindow()
{
    delete currentDirectory;
}

void adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}

void MainWindow::scaleImage(double factor)
{
    Q_ASSERT(label->pixmap());
    scaleFactor *= factor;
    label->resize(scaleFactor * label->pixmap()->size());

    adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(scrollArea->verticalScrollBar(), factor);
}

void MainWindow::displayImage(const QString &fileName)
{
    QImage disImage(fileName);
    if (disImage.isNull()) {
        QMessageBox::information(this, tr("MIPS"),
                                 tr("Cannot load %1.").arg(fileName));
        return;
    }
    label->setPixmap(QPixmap::fromImage(disImage));
    scaleImage(1.0);
}

void MainWindow::updateUi()
{
    if(currentFile == displayFiles.constEnd())
    {
        imageInfo->setText(tr("There Are No Images! Please Click TreeView to Select Image Folder!"));
        actionForward->setEnabled(false);
        actionBack->setEnabled(false);
        actionZoomIn->setEnabled(false);
        actionZoomOut->setEnabled(false);
        actionActualSize->setEnabled(false);
        actionFitSize->setEnabled(false);
    }
    else
    {
        int i = displayFiles.indexOf(*currentFile, 0) + 1;	// non-Programmer count from 1 instead 0
        imageInfo->setText(QString(tr("%1/%2 %3 %4%")).arg(i).arg(displayFiles.size()).arg(*currentFile).arg(scaleFactor*100, 3));
        actionForward->setEnabled(true);
        actionBack->setEnabled(true);        
        actionActualSize->setEnabled(true);
        actionFitSize->setEnabled(true);
        actionZoomIn->setEnabled(scaleFactor < 3.0);
        actionZoomOut->setEnabled(scaleFactor > 0.333);       
    }
}

void MainWindow::on_actionForward_triggered()
{
    currentFile++;
    if(currentFile == displayFiles.constEnd())
        currentFile = displayFiles.constBegin();
    displayImage(currentDirectory->absoluteFilePath(*currentFile));
    updateUi();
}

void MainWindow::on_actionBack_triggered()
{
    if(currentFile == displayFiles.constBegin())
        currentFile = displayFiles.constEnd();
    currentFile--;
    displayImage(currentDirectory->absoluteFilePath(*currentFile));
    updateUi();
}

void MainWindow::on_actionZoomOut_triggered()
{
    scaleImage(0.8);
    updateUi();
}

void MainWindow::on_actionZoomIn_triggered()
{
    scaleImage(1.25);
    updateUi();
}

void MainWindow::on_actionActualSize_triggered()
{
    scaleFactor = 1.0;
    scaleImage(1.0);
    updateUi();
}

void MainWindow::on_treeView_clicked ( const QModelIndex &index )
{
    const QString path = dirModel->data(index, QDirModel::FilePathRole).toString();
    currentDirectory->setPath(path);
    displayFiles = currentDirectory->entryList(supportedFormat, QDir::Files);
    currentFile = displayFiles.constBegin();
    if(currentFile != displayFiles.constEnd())
        displayImage(currentDirectory->absoluteFilePath(*currentFile));
    updateUi();
}

void MainWindow::slotGaussInSmoother()
{
    QImage processingImage = QImage(currentDirectory->absoluteFilePath(*currentFile));
	TemplateMatrix matrix(1);
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			int w = 0;
			int res = i * i + j * j;
			switch(res)
			{
			case 0:
				w = 4;
				break;
			case 1:
				w = 2;
				break;
			case 2:
				w = 1;
				break;
			default:
				w = 0;
			}
			matrix.setWeightAt(i + 1, j + 1, w);
		}
	}

	processingImage = ImageSmoother::setTemplate(processingImage, matrix, 1.0 / 16.0);
    DisplayImageDialog *dialog = new DisplayImageDialog(processingImage,this);
    dialog->exec();
    delete dialog;
}

void  MainWindow::slotBoxInSmoother()
{
	QImage processingImage = QImage(currentDirectory->absoluteFilePath(*currentFile));
	TemplateMatrix matrix(1);
	
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{			
			matrix.setWeightAt(i + 1, j + 1, 1);
		}
	}

	processingImage = ImageSmoother::setTemplate(processingImage, matrix, 1.0 / 9.0);
	DisplayImageDialog *dialog = new DisplayImageDialog(processingImage,this);
	dialog->exec();
	delete dialog;
}

void  MainWindow::slotEightInSmoother()
{
	QImage processingImage = QImage(currentDirectory->absoluteFilePath(*currentFile));
	TemplateMatrix matrix(1);

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{			
			matrix.setWeightAt(i + 1, j + 1, 1);
		}
	}
	matrix.setWeightAt(1,1,0);

	processingImage = ImageSmoother::setTemplate(processingImage, matrix, 1.0/8.0);
	DisplayImageDialog *dialog = new DisplayImageDialog(processingImage,this);
	dialog->exec();
	delete dialog;
}

void  MainWindow::slotTenInSmoother()
{
	QImage processingImage = QImage(currentDirectory->absoluteFilePath(*currentFile));
	TemplateMatrix matrix(1);

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{			
			matrix.setWeightAt(i + 1, j + 1, 1);
		}
	}
    matrix.setWeightAt(1,1,2);

	processingImage = ImageSmoother::setTemplate(processingImage, matrix, 1.0 / 10.0);
	DisplayImageDialog *dialog = new DisplayImageDialog(processingImage,this);
	dialog->exec();
	delete dialog;
}

void MainWindow::slotMF5InSmoother()
{
	QImage processingImage = QImage(currentDirectory->absoluteFilePath(*currentFile));
	processingImage = ImageSmoother::useMedianFilter(processingImage,5);
	DisplayImageDialog *dialog = new DisplayImageDialog(processingImage,this);
	dialog->exec();
	delete dialog;
}

void MainWindow::slotMF9InSmoother()
{
	QImage processingImage = QImage(currentDirectory->absoluteFilePath(*currentFile));	
	processingImage = ImageSmoother::useMedianFilter(processingImage,9);
	DisplayImageDialog *dialog = new DisplayImageDialog(processingImage,this);
	dialog->exec();
	delete dialog;
}

void MainWindow::slotILPFInSmoother()
{
	QImage processingImage = QImage(currentDirectory->absoluteFilePath(*currentFile));	
	 int xRadius = 25;
	 int yRadius = 25;
	processingImage = ImageSmoother::useIdealLowPassFilter(processingImage,xRadius,yRadius);
	DisplayImageDialog *dialog = new DisplayImageDialog(processingImage,this);
	dialog->exec();
	delete dialog;
}

void MainWindow::slotBWLPFInSmoother()
{
	QImage processingImage = QImage(currentDirectory->absoluteFilePath(*currentFile));	
	int radius = 25;	
	processingImage = ImageSmoother::useButterWorthLowPassFilter(processingImage,radius);
	DisplayImageDialog *dialog = new DisplayImageDialog(processingImage,this);
	dialog->exec();
	delete dialog;
}

void MainWindow::slotIHPFInSharpener()
{
	QImage processingImage = QImage(currentDirectory->absoluteFilePath(*currentFile));	
	int xRadius = 5;
	int yRadius = 5;
	processingImage = ImageSharpener::useIdealHighPassFilter(processingImage,xRadius,yRadius);
	DisplayImageDialog *dialog = new DisplayImageDialog(processingImage,this);
	dialog->exec();
	delete dialog;
}

void MainWindow::slotBWHPFInSharpener()
{
	QImage processingImage = QImage(currentDirectory->absoluteFilePath(*currentFile));	
	int radius = 5;	
	processingImage = ImageSharpener::useButterWorthHighPassFilter(processingImage,radius);
	DisplayImageDialog *dialog = new DisplayImageDialog(processingImage,this);
	dialog->exec();
	delete dialog;
}

void MainWindow::slotLaplacianInSharpener()
{
	QImage processingImage = QImage(currentDirectory->absoluteFilePath(*currentFile));
	TemplateMatrix matrix(1);

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			int w = 0;
			int res = i * i + j * j;
			switch(res)
			{
			case 0:
				w = 5;
				break;
			case 1:
				w = -1;
				break;
			case 2:
				w = 0;
				break;
			default:
				w = 0;
			}
			matrix.setWeightAt(i + 1, j + 1, w);
		}
	}

	processingImage = ImageSmoother::setTemplate(processingImage, matrix, 1.0);
	DisplayImageDialog *dialog = new DisplayImageDialog(processingImage,this);
	dialog->exec();
	delete dialog;
}

const char *htmlAboutText =
        "<HTML>"
        "<p>The MIPS (Medical Image Preprocessing System) is mainly designed to enhance the medical images.</p>"
        "<p>This program is subject to the GPL license.</p>"
        "<p>Written by Kevin Chow.</p>"
        "<p>Current Version 0.9.1"
        "</HTML>";

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("About The MIPS"), htmlAboutText);
}
