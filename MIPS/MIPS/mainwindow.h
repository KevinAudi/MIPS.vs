#include <QDirModel>
#include <QTreeWidgetItem>
#include <QMessageBox>
#include <QHeaderView>
#include <QImageReader>
#include <QFileDialog>

#include <math.h>

#include "ui_MainWindow.h"
/*#include "displaymatrix.h"*/
#include "previewwidget.h"

#include "imagepreprocessor.h"
#include "imagesmoother.h"
#include "imagesharpener.h"
#include "imageedgedetector.h"
#include "imagegrayleveltransformator.h"

class MainWindow : public QMainWindow,private Ui::MainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void on_actionForward_triggered();
	void on_actionBack_triggered();	
	void on_actionAbout_triggered();  
	void on_actionSave_triggered();
	void on_treeView_clicked(const QModelIndex & index);


	void slotGaussInSmoother();
	void slotBoxInSmoother();
	void slotEightInSmoother();
	void slotTenInSmoother();

    void slotMF5InSmoother();
	void slotMF9InSmoother();

	void slotILPFInSmoother();
	void slotBWLPFInSmoother();

	void slotIHPFInSharpener();
	void slotBWHPFInSharpener();

	void slotLaplacian4InSharpener();
	void slotLaplacian8InSharpener();

	void slotSobelInSharpener();
	void slotPrewittInSharpener();
	void slotIsotropicInSharpener();

	void slotGradiantInEdgeDetector();
	void slotRobertsInEdgeDetector();
	void slotSobelInEdgeDetector();
	void slotLaplacian8InEdgeDetector();

	void slotLinearityInTransformator();

private:	
	void connectSignalsAndSlots();
    void addTreeView();
	void displayImage();
	void updateUi();
	QImage compareImage(QImage imageB, QImage imageA);

	QDirModel *dirModel;	
	QDir *currentDirectory;
	QStringList supportedFormat;
	QStringList displayFiles;
	QStringList::const_iterator currentFile;
	QWidget *displayWidget;
	QImage imageBeforeProcessing;
	QImage imageAfterProcessing;
	QImage imageInDistinction;
	QString originFileName;

	PreViewWidget *previewBefore;
	PreViewWidget *previewAfter;
	PreViewWidget *comparison;
	double scaleFactor;
};
