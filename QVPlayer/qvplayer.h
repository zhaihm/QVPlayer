#ifndef QVPLAYER_H
#define QVPLAYER_H

#include <QtWidgets/QMainWindow>
#include "ui_qvplayer.h"
#include "VLCPlayer.h"

class QVPlayer : public QMainWindow
{
	Q_OBJECT

public:
	QVPlayer(QWidget *parent = 0);
	~QVPlayer();

private slots:
	void on_playBtn_clicked();
	void on_pauseBtn_clicked();
	void on_stopBtn_clicked();
	void on_durationSlider_valueChanged(int value);

private:
	Ui::QVPlayerClass ui;
	VLCPlayer _player;
};

#endif // QVPLAYER_H
