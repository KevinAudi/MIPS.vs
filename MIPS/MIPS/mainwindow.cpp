#include <QMessageBox>
#include <QHeaderView>
#include <QScrollBar>
#include <QImageReader>

#include "mainwindow.h"


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
    QObject::connect(actionL4,SIGNAL(triggered()),this,SLOT(slotLaplacian4InSharpener()));
	QObject::connect(actionL8,SIGNAL(triggered()),this,SLOT(slotLaplacian8InSharpener()));
	QObject::connect(actionSobel,SIGNAL(triggered()),this,SLOT(slotSobelInSharpener()));
	QObject::connect(actionIsotropic,SIGNAL(triggered()),this,SLOT(slotIsotropicInSharpener()));
	QObject::connect(actionPrewitt,SIGNAL(triggered()),this,SLOT(slotPrewittInSharpener())); 
    
	QObject::connect(actionGradiant,SIGNAL(triggered()),this,SLOT(slotGradiantInEdgeDetector())); 
	QObject::connect(actionRoberts,SIGNAL(triggered()),this,SLOT(slotRobertsInEdgeDetector())); 
	QObject::connect(actionSobel_In_ED,SIGNAL(triggered()),this,SLOT(slotRobertsInEdgeDetector())); 
	QObject::connect(actionLaplace8,SIGNAL(triggered()),this,SLOT(slotLaplacian8InEdgeDetector())); 
	
	QObject::connect(actionLinearity,SIGNAL(triggered()),this,SLOT(slotLinearityInTransformator()));
    

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
//	processingImage.save("D:/gauss.bmp");
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
//	processingImage.save("D:/box.bmp");
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
//	processingImage.save("D:/eight.bmp");
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
	//processingImage.save("D:/ten.bmp");
	DisplayImageDialog *dialog = new DisplayImageDialog(processingImage,this);
	dialog->exec();
	delete dialog;
}

void MainWindow::slotMF5InSmoother()
{
	QImage processingImage = QImage(currentDirectory->absoluteFilePath(*currentFile));
	processingImage = ImageSmoother::useMedianFilter(processingImage,5);
	//processingImage.save("D:/MF5.bmp");
	DisplayImageDialog *dialog = new DisplayImageDialog(processingImage,this);
	dialog->exec();
	delete dialog;
}

void MainWindow::slotMF9InSmoother()
{
	QImage processingImage = QImage(currentDirectory->absoluteFilePath(*currentFile));	
	processingImage = ImageSmoother::useMedianFilter(processingImage,9);
	//processingImage.save("D:/MF9.bmp");
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

void MainWindow::slotLaplacian4InSharpener()
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

void MainWindow::slotLaplacian8InSharpener()
{
	QImage processingImage = QImage(currentDirectory->absoluteFilePath(*currentFile));
	TemplateMatrix matrix(1);
	int i,j;

	for ( i = -1; i <= 1; i++)
	{
		for ( j = -1; j <= 1; j++)
		{
			matrix.setWeightAt(i + 1, j + 1, -1);
		}
	}
    matrix.setWeightAt(1, 1, 8);
	processingImage = ImageSmoother::setTemplate(processingImage, matrix, 1.0);
	DisplayImageDialog *dialog = new DisplayImageDialog(processingImage,this);
	dialog->exec();
	delete dialog;
}

void MainWindow::slotSobelInSharpener()
{
	QImage processingImage = QImage(currentDirectory->absoluteFilePath(*currentFile));
	TemplateMatrix matrixX(1);   //3X3
	TemplateMatrix matrixY(1);   //3X3
	
	matrixX.setWeightAt(0, 0, 1);
	matrixX.setWeightAt(0, 1, 0);
	matrixX.setWeightAt(0, 2,-1);
	matrixX.setWeightAt(1, 0, 2);
	matrixX.setWeightAt(1, 1, 0);
	matrixX.setWeightAt(1, 2, -2);
	matrixX.setWeightAt(2, 0, 1);
	matrixX.setWeightAt(2, 1, 0);
	matrixX.setWeightAt(2, 2, -1);

	matrixY.setWeightAt(0, 0, -1);
	matrixY.setWeightAt(0, 1, -2);
	matrixY.setWeightAt(0, 2,-1);
	matrixY.setWeightAt(1, 0, 0);
	matrixY.setWeightAt(1, 1, 0);
	matrixY.setWeightAt(1, 2, 0);
	matrixY.setWeightAt(2, 0, 1);
	matrixY.setWeightAt(2, 1, 2);
	matrixY.setWeightAt(2, 2, 1);
		
	processingImage = ImageSharpener::setTemplateInSharpener(processingImage, matrixX,matrixY);

	DisplayImageDialog *dialog = new DisplayImageDialog(processingImage,this);
	dialog->exec();
	delete dialog;
}

void MainWindow::slotIsotropicInSharpener()
{
	QImage processingImage = QImage(currentDirectory->absoluteFilePath(*currentFile));
	TemplateMatrix matrixX(1);   //3X3
	TemplateMatrix matrixY(1);   //3X3

	matrixX.setWeightAt(0, 0, 1);
	matrixX.setWeightAt(0, 1, 0);
	matrixX.setWeightAt(0, 2,-1);
	matrixX.setWeightAt(1, 0, sqrt(2.0));
	matrixX.setWeightAt(1, 1, 0);
	matrixX.setWeightAt(1, 2, -sqrt(2.0));
	matrixX.setWeightAt(2, 0, 1);
	matrixX.setWeightAt(2, 1, 0);
	matrixX.setWeightAt(2, 2, -1);

	matrixY.setWeightAt(0, 0, -1);
	matrixY.setWeightAt(0, 1, -sqrt(2.0));
	matrixY.setWeightAt(0, 2,-1);
	matrixY.setWeightAt(1, 0, 0);
	matrixY.setWeightAt(1, 1, 0);
	matrixY.setWeightAt(1, 2, 0);
	matrixY.setWeightAt(2, 0, 1);
	matrixY.setWeightAt(2, 1, sqrt(2.0));
	matrixY.setWeightAt(2, 2, 1);

	processingImage = ImageSharpener::setTemplateInSharpener(processingImage, matrixX,matrixY);

	DisplayImageDialog *dialog = new DisplayImageDialog(processingImage,this);
	dialog->exec();
	delete dialog;
}


void MainWindow::slotPrewittInSharpener()
{
	QImage processingImage = QImage(currentDirectory->absoluteFilePath(*currentFile));
	TemplateMatrix matrixX(1);   //3X3
	TemplateMatrix matrixY(1);   //3X3

	matrixX.setWeightAt(0, 0, 1);
	matrixX.setWeightAt(0, 1, 0);
	matrixX.setWeightAt(0, 2,-1);
	matrixX.setWeightAt(1, 0, 1);
	matrixX.setWeightAt(1, 1, 0);
	matrixX.setWeightAt(1, 2, -1);
	matrixX.setWeightAt(2, 0, 1);
	matrixX.setWeightAt(2, 1, 0);
	matrixX.setWeightAt(2, 2, -1);

	matrixY.setWeightAt(0, 0, -1);
	matrixY.setWeightAt(0, 1, -1);
	matrixY.setWeightAt(0, 2,-1);
	matrixY.setWeightAt(1, 0, 0);
	matrixY.setWeightAt(1, 1, 0);
	matrixY.setWeightAt(1, 2, 0);
	matrixY.setWeightAt(2, 0, 1);
	matrixY.setWeightAt(2, 1, 1);
	matrixY.setWeightAt(2, 2, 1);

	processingImage = ImageSharpener::setTemplateInSharpener(processingImage, matrixX,matrixY);

	DisplayImageDialog *dialog = new DisplayImageDialog(processingImage,this);
	dialog->exec();
	delete dialog;
}

void MainWindow::slotGradiantInEdgeDetector()
{
     QImage processingImage = QImage(currentDirectory->absoluteFilePath(*currentFile));
	 char flag = 'M';
	 double scaleFactor = 2.0;
	 processingImage = ImageEdgeDetector::useGradiant(processingImage, 'M',2.0);

	 DisplayImageDialog *dialog = new DisplayImageDialog(processingImage,this);
	 dialog->exec();
	 delete dialog;
}

void MainWindow::slotRobertsInEdgeDetector()
{
	QImage processingImage = QImage(currentDirectory->absoluteFilePath(*currentFile));
	char flag = 'R';
	double scaleFactor = 2.0;
	processingImage = ImageEdgeDetector::useGradiant(processingImage, 'R',2.0);

	DisplayImageDialog *dialog = new DisplayImageDialog(processingImage,this);
	dialog->exec();
	delete dialog;
}

void MainWindow::slotSobelInEdgeDetector()
{
	QImage processingImage = QImage(currentDirectory->absoluteFilePath(*currentFile));
	char flag = 'm';
	double scaleFactor = 4.0;

	TemplateMatrix matrixX(1);   //3X3
	TemplateMatrix matrixY(1);   //3X3

	matrixX.setWeightAt(0, 0, -1);
	matrixX.setWeightAt(0, 1, -2);
	matrixX.setWeightAt(0, 2,-1);
	matrixX.setWeightAt(1, 0, 0);
	matrixX.setWeightAt(1, 1, 0);
	matrixX.setWeightAt(1, 2, 0);
	matrixX.setWeightAt(2, 0, 1);
	matrixX.setWeightAt(2, 1, 2);
	matrixX.setWeightAt(2, 2, 1);

	matrixY.setWeightAt(0, 0, -1);
	matrixY.setWeightAt(0, 1, 0);
	matrixY.setWeightAt(0, 2,1);
	matrixY.setWeightAt(1, 0, -2);
	matrixY.setWeightAt(1, 1, 0);
	matrixY.setWeightAt(1, 2, 2);
	matrixY.setWeightAt(2, 0, -1);
	matrixY.setWeightAt(2, 1, 0);
	matrixY.setWeightAt(2, 2, 1);

	processingImage = ImageEdgeDetector::useSobel(processingImage, matrixX,matrixY,'R',2.0);

	DisplayImageDialog *dialog = new DisplayImageDialog(processingImage,this);
	dialog->exec();
	delete dialog;
}

void MainWindow::slotLaplacian8InEdgeDetector()
{
	QImage processingImage = QImage(currentDirectory->absoluteFilePath(*currentFile));
	TemplateMatrix matrix(1);
	int i,j;

	for ( i = -1; i <= 1; i++)
	{
		for ( j = -1; j <= 1; j++)
		{
			matrix.setWeightAt(i + 1, j + 1, 1);
		}
	}
	matrix.setWeightAt(1, 1, -8);
	processingImage = ImageSmoother::setTemplate(processingImage, matrix, 1.0);
	DisplayImageDialog *dialog = new DisplayImageDialog(processingImage,this);
	dialog->exec();
	delete dialog;
}

void MainWindow::slotLinearityInTransformator()
{
    QImage processingImage = QImage(currentDirectory->absoluteFilePath(*currentFile));
    int oldLow = 70;
	int oldHigh = 210;
	int newLow = 0;
	int newHigh = 255;

	processingImage = ImageGrayLevelTransformator::transformGrayLevelInLinearity(processingImage,oldLow,oldHigh,newLow,newHigh);
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
