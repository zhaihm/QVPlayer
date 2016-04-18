#include "qvplayer.h"
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>

QVPlayer::QVPlayer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	_player.init((HWND)ui.videoWnd->winId());
}

QVPlayer::~QVPlayer()
{
}

void QVPlayer::on_playBtn_clicked()
{
	qDebug() << "Play button clicked";

	QFileDialog fileDlg;
	if (!fileDlg.exec())
		return;
	
	QString movieFile = fileDlg.selectedFiles()[0];
	qDebug() << "moviefile: " << movieFile.toStdString().c_str();

	_player.play(movieFile.replace('/', '\\').toStdString().c_str()); // vlc only accept '\' as directory seperator
}

void QVPlayer::on_exitBtn_clicked()
{
	exit(0);
}

void QVPlayer::on_durationSlider_valueChanged(int value)
{
	qDebug() << "Duration slider value changed, new value" << value;
	_player.setDuration(_player.length() * value / ui.durationSlider->maximum());
}
