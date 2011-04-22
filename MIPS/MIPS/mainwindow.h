#include <QDirModel>
#include <QTreeWidgetItem>
#include <QLabel>
#include <QScrollArea>
#include <math.h>

#include "ui_MainWindow.h"
#include "imagepreprocessor.h"
#include "displayimagedialog.h"
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
	void on_actionZoomOut_triggered();
	void on_actionZoomIn_triggered();
	void on_actionActualSize_triggered();
	void on_actionAbout_triggered();
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
	void displayImage(const QString &fileName);
	void scaleImage(double factor);
	void updateUi();

	QDirModel *dirModel;
	QLabel *imageInfo;
	QDir *currentDirectory;
	QStringList supportedFormat;
	QStringList displayFiles;
	QStringList::const_iterator currentFile;

	double scaleFactor;
};
