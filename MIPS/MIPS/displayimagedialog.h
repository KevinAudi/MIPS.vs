#ifndef DISPLAYIMAGEDIALOG_H
#define DISPLAYIMAGEDIALOG_H

#include <QDialog>
#include <QHBoxLayout>

class DisplayImageDialog : public QDialog
{
	Q_OBJECT
public:
	explicit DisplayImageDialog(QImage image, QWidget *parent = 0);
};

#endif // DISPLAYIMAGEDIALOG_H
