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

protected:
    virtual bool eventFilter(QObject *watched, QEvent *event);

private slots:
	void on_playBtn_clicked();
	void on_pauseBtn_clicked();
	void on_stopBtn_clicked();
	void on_durationSlider_valueChanged(int value);
	void on_volumeSlider_valueChanged(int value);
	void on_muteBtn_clicked();
	void on_updateDurationSliderTimer_timeout();
    void on_snapshotBtn_clicked();

private:
	Ui::QVPlayerClass ui;
	VLCPlayer _player;
	QTimer *_updateDurationSliderTimer;
};

#endif // QVPLAYER_H
