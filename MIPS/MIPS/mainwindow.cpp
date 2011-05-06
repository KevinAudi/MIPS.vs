#include "mainwindow.h"

//#include <iostream>
//using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), scaleFactor(1)
{
    setupUi(this);
	connectSignalsAndSlots();    
    addTreeView();    

	previewBefore = new PreViewWidget();
	previewAfter = new PreViewWidget();
	tabWidget->addTab(previewBefore,"&Before");
	tabWidget->addTab(previewAfter,"&After");
    
    foreach (QByteArray byteArray, QImageReader::supportedImageFormats())
    {
        QString extra = QString("*.") + QString(byteArray);
        supportedFormat << extra;
    }

	currentDirectory = new QDir(); 
    currentFile = displayFiles.constBegin();  

  resize(800,600);
   updateUi();
}

MainWindow::~MainWindow()
{
    delete currentDirectory;
}

void MainWindow::addTreeView()
{
	dirModel = new QDirModel(this);
	dirModel->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);

	treeView->setModel(dirModel);
	treeView->header()->setVisible(false);
	treeView->setColumnHidden(1,true);	// Size
	treeView->setColumnHidden(2,true);  // Type
	treeView->setColumnHidden(3,true);  // Modified Date   
}

void MainWindow::connectSignalsAndSlots()
{
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
}

void MainWindow::updateUi()
{
    if(currentFile == displayFiles.constEnd())
    {
        imageInfo->setText(tr("There Are No Images! Please Click TreeView to Select Image Folder!"));
        actionForward->setEnabled(false);
        actionBack->setEnabled(false);        
    }
    else
    {
        int i = displayFiles.indexOf(*currentFile, 0) + 1;	// non-Programmer count from 1 instead 0
        imageInfo->setText(QString(tr("%1/%2 %3 %4%")).arg(i).arg(displayFiles.size()).arg(*currentFile).arg(scaleFactor*100, 3));
        actionForward->setEnabled(true);
        actionBack->setEnabled(true);         
    }
}

void MainWindow::on_actionForward_triggered()
{
    currentFile++;
    if(currentFile == displayFiles.constEnd())
        currentFile = displayFiles.constBegin();
    displayImage();
    updateUi();
}

void MainWindow::on_actionBack_triggered()
{
   if(currentFile == displayFiles.constBegin())
        currentFile = displayFiles.constEnd();
    currentFile--;
    displayImage();
    updateUi();
}

void MainWindow::on_actionSave_triggered()
{
	QString savedFileName = QFileDialog::getSaveFileName(this,tr("Save Image"), ".",
		tr("Images (*.bmp *.png *.pbm *.jpg *.jpeg *.tiff);;Text files (*.txt);;XML files (*.xml)"));
	imageAfterProcessing.save(savedFileName);	
}

void MainWindow::on_treeView_clicked ( const QModelIndex &index )
{
    const QString path = dirModel->data(index, QDirModel::FilePathRole).toString();
    currentDirectory->setPath(path);
    displayFiles = currentDirectory->entryList(supportedFormat, QDir::Files);
    currentFile = displayFiles.constBegin();
    if(currentFile != displayFiles.constEnd())			
		displayImage();	
    updateUi();
}

void MainWindow::displayImage()
{
	QString  fileName = currentDirectory->absoluteFilePath(*currentFile);
	QImage disImage(fileName);
	if (disImage.isNull())
	{ 
		QMessageBox::information(this, tr("MIPS"),tr("Cannot load %1.").arg(fileName));
		return;
	}
	previewBefore->setImage(disImage);		
}


void MainWindow::slotGaussInSmoother()
{
    imageAfterProcessing = QImage(currentDirectory->absoluteFilePath(*currentFile));
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

	imageAfterProcessing = ImageSmoother::setTemplate(imageAfterProcessing, matrix, 1.0 / 16.0);   
     previewAfter->setImage(imageAfterProcessing);		     
}

void  MainWindow::slotBoxInSmoother()
{
	imageAfterProcessing = QImage(currentDirectory->absoluteFilePath(*currentFile));
	TemplateMatrix matrix(1);
	
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{			
			matrix.setWeightAt(i + 1, j + 1, 1);
		}
	}

	imageAfterProcessing = ImageSmoother::setTemplate(imageAfterProcessing, matrix, 1.0 / 9.0);
    previewAfter->setImage(imageAfterProcessing);	
}

void  MainWindow::slotEightInSmoother()
{
	imageAfterProcessing = QImage(currentDirectory->absoluteFilePath(*currentFile));
	TemplateMatrix matrix(1);

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{			
			matrix.setWeightAt(i + 1, j + 1, 1);
		}
	}
	matrix.setWeightAt(1,1,0);

	imageAfterProcessing = ImageSmoother::setTemplate(imageAfterProcessing, matrix, 1.0/8.0);
    previewAfter->setImage(imageAfterProcessing);	
}

void  MainWindow::slotTenInSmoother()
{
	imageAfterProcessing = QImage(currentDirectory->absoluteFilePath(*currentFile));
	TemplateMatrix matrix(1);

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{			
			matrix.setWeightAt(i + 1, j + 1, 1);
		}
	}
    matrix.setWeightAt(1,1,2);

	imageAfterProcessing = ImageSmoother::setTemplate(imageAfterProcessing, matrix, 1.0 / 10.0);
	previewAfter->setImage(imageAfterProcessing);	
}

void MainWindow::slotMF5InSmoother()
{
	imageAfterProcessing = QImage(currentDirectory->absoluteFilePath(*currentFile));
	imageAfterProcessing = ImageSmoother::useMedianFilter(imageAfterProcessing,5);
	previewAfter->setImage(imageAfterProcessing);	
}

void MainWindow::slotMF9InSmoother()
{
	imageAfterProcessing = QImage(currentDirectory->absoluteFilePath(*currentFile));	
	imageAfterProcessing = ImageSmoother::useMedianFilter(imageAfterProcessing,9);
	previewAfter->setImage(imageAfterProcessing);	
}

void MainWindow::slotILPFInSmoother()
{
	imageAfterProcessing = QImage(currentDirectory->absoluteFilePath(*currentFile));	
	 int xRadius = 25;
	 int yRadius = 25;
	imageAfterProcessing = ImageSmoother::useIdealLowPassFilter(imageAfterProcessing,xRadius,yRadius);
	previewAfter->setImage(imageAfterProcessing);	
}

void MainWindow::slotBWLPFInSmoother()
{
	imageAfterProcessing = QImage(currentDirectory->absoluteFilePath(*currentFile));	
	int radius = 25;	
	imageAfterProcessing = ImageSmoother::useButterWorthLowPassFilter(imageAfterProcessing,radius);
	previewAfter->setImage(imageAfterProcessing);	
}

void MainWindow::slotIHPFInSharpener()
{
	imageAfterProcessing = QImage(currentDirectory->absoluteFilePath(*currentFile));	
	int xRadius = 5;
	int yRadius = 5;
	imageAfterProcessing = ImageSharpener::useIdealHighPassFilter(imageAfterProcessing,xRadius,yRadius);
	previewAfter->setImage(imageAfterProcessing);	
}

void MainWindow::slotBWHPFInSharpener()
{
	imageAfterProcessing = QImage(currentDirectory->absoluteFilePath(*currentFile));	
	int radius = 5;	
	imageAfterProcessing = ImageSharpener::useButterWorthHighPassFilter(imageAfterProcessing,radius);
	previewAfter->setImage(imageAfterProcessing);	
}

void MainWindow::slotLaplacian4InSharpener()
{
	imageAfterProcessing = QImage(currentDirectory->absoluteFilePath(*currentFile));
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

	imageAfterProcessing = ImageSmoother::setTemplate(imageAfterProcessing, matrix, 1.0);
	previewAfter->setImage(imageAfterProcessing);	
}

void MainWindow::slotLaplacian8InSharpener()
{
	imageAfterProcessing = QImage(currentDirectory->absoluteFilePath(*currentFile));
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
	imageAfterProcessing = ImageSmoother::setTemplate(imageAfterProcessing, matrix, 1.0);
	previewAfter->setImage(imageAfterProcessing);	
}

void MainWindow::slotSobelInSharpener()
{
	imageAfterProcessing = QImage(currentDirectory->absoluteFilePath(*currentFile));
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
		
	imageAfterProcessing = ImageSharpener::setTemplateInSharpener(imageAfterProcessing, matrixX,matrixY);
    previewAfter->setImage(imageAfterProcessing);	
}

void MainWindow::slotIsotropicInSharpener()
{
	imageAfterProcessing = QImage(currentDirectory->absoluteFilePath(*currentFile));
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

	imageAfterProcessing = ImageSharpener::setTemplateInSharpener(imageAfterProcessing, matrixX,matrixY);
    previewAfter->setImage(imageAfterProcessing);	
}

void MainWindow::slotPrewittInSharpener()
{
	imageAfterProcessing = QImage(currentDirectory->absoluteFilePath(*currentFile));
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

	imageAfterProcessing = ImageSharpener::setTemplateInSharpener(imageAfterProcessing, matrixX,matrixY);
   previewAfter->setImage(imageAfterProcessing);	
}

void MainWindow::slotGradiantInEdgeDetector()
{
     imageAfterProcessing = QImage(currentDirectory->absoluteFilePath(*currentFile));
	 char flag = 'M';
	 double scaleFactor = 2.0;
	 imageAfterProcessing = ImageEdgeDetector::useGradiant(imageAfterProcessing, 'M',2.0);
     previewAfter->setImage(imageAfterProcessing);	
}

void MainWindow::slotRobertsInEdgeDetector()
{
	imageAfterProcessing = QImage(currentDirectory->absoluteFilePath(*currentFile));
	char flag = 'R';
	double scaleFactor = 2.0;
	imageAfterProcessing = ImageEdgeDetector::useGradiant(imageAfterProcessing, 'R',2.0);
    previewAfter->setImage(imageAfterProcessing);	
}

void MainWindow::slotSobelInEdgeDetector()
{
	imageAfterProcessing = QImage(currentDirectory->absoluteFilePath(*currentFile));
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

	imageAfterProcessing = ImageEdgeDetector::useSobel(imageAfterProcessing, matrixX,matrixY,'R',2.0);
    previewAfter->setImage(imageAfterProcessing);	
}

void MainWindow::slotLaplacian8InEdgeDetector()
{
	imageAfterProcessing = QImage(currentDirectory->absoluteFilePath(*currentFile));
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
	imageAfterProcessing = ImageSmoother::setTemplate(imageAfterProcessing, matrix, 1.0);
	previewAfter->setImage(imageAfterProcessing);	
}

void MainWindow::slotLinearityInTransformator()
{
    imageAfterProcessing = QImage(currentDirectory->absoluteFilePath(*currentFile));
    int oldLow = 70;
	int oldHigh = 210;
	int newLow = 0;
	int newHigh = 255;

	imageAfterProcessing = ImageGrayLevelTransformator::transformGrayLevelInLinearity(imageAfterProcessing,oldLow,oldHigh,newLow,newHigh);
	previewAfter->setImage(imageAfterProcessing);	
}

const char *htmlAboutText =
        "<HTML>"
        "<p>The MIPS (Medical Image Preprocessing System) is mainly designed to enhance the medical images.</p>"
        "<p>This program is subject to the GPL license.</p>"
        "<p>Powered by Kevin Chow.</p>"
        "<p>Current Version 0.9.1"
        "</HTML>";

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("About The MIPS"), htmlAboutText);
}
