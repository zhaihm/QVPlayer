#ifndef QVPLAYER_H
#define QVPLAYER_H

#include <QtWidgets/QMainWindow>
#include "ui_qvplayer.h"

class QVPlayer : public QMainWindow
{
	Q_OBJECT

public:
	QVPlayer(QWidget *parent = 0);
	~QVPlayer();

private slots:
	void on_playBtn_clicked();
	void on_exitBtn_clicked();

private:
	Ui::QVPlayerClass ui;
};

#endif // QVPLAYER_H
