#include "qvplayer.h"
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>

QVPlayer::QVPlayer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.pauseBtn->hide();
	_player.init((HWND)ui.videoWnd->winId());
}

QVPlayer::~QVPlayer()
{
}

void QVPlayer::on_playBtn_clicked()
{
	qDebug() << "Play button clicked";

	char path[512] = {0};
	if (!_player.isPaused() && !_player.isStopped()) {
		QFileDialog fileDlg;
		if (!fileDlg.exec())
			return;

		QString movieFile = fileDlg.selectedFiles()[0];
		qDebug() << "moviefile: " << movieFile.toStdString().c_str();

		// vlc only accept '\' as directory seperator
		strncpy(path, movieFile.replace('/', '\\').toStdString().c_str(), movieFile.replace('/', '\\').toStdString().length());
	}
	_player.play(strlen(path)==0 ? NULL : path);
	
	ui.playBtn->hide();
	ui.pauseBtn->show();
}

void QVPlayer::on_pauseBtn_clicked()
{
	_player.pause();
	ui.pauseBtn->hide();
	ui.playBtn->show();
}

void QVPlayer::on_stopBtn_clicked()
{
	_player.stop();
	ui.pauseBtn->hide();
	ui.playBtn->show();
}

void QVPlayer::on_durationSlider_valueChanged(int value)
{
	qDebug() << "Duration slider value changed, new value" << value;
	_player.setDuration(_player.length() * value / ui.durationSlider->maximum());
}
