#include "qvplayer.h"
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QTimer>
#include <QMouseEvent>

#define MAX_VOLUME	100

QVPlayer::QVPlayer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.pauseBtn->hide();
    ui.durationSlider->installEventFilter(this);
    ui.volumeSlider->installEventFilter(this);

	_player.init((HWND)ui.videoWnd->winId());

	_updateDurationSliderTimer = new QTimer;
	connect(_updateDurationSliderTimer, SIGNAL(timeout()), SLOT(on_updateDurationSliderTimer_timeout()));
	_updateDurationSliderTimer->start(300);
}

QVPlayer::~QVPlayer()
{
}

bool QVPlayer::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui.durationSlider && event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *e = (QMouseEvent *)event;
        ui.durationSlider->setValue(ui.durationSlider->maximum() * e->pos().x() / ui.durationSlider->width());
        _player.setDuration(_player.length() * e->pos().x() / ui.durationSlider->width());
    }
    else if (watched == ui.volumeSlider && event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *e = (QMouseEvent *)event;
        ui.volumeSlider->setValue(ui.volumeSlider->maximum() * e->pos().x() / ui.volumeSlider->width());
        _player.setVolume(ui.volumeSlider->maximum() * e->pos().x() / ui.volumeSlider->width());
    }
    return QMainWindow::eventFilter(watched, event);
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

		// vlc only accept '\' as directory seperator under Windows
		movieFile.replace('/', '\\');
		strncpy(path, movieFile.toStdString().c_str(), movieFile.length());
	}
	_player.play(strlen(path)==0 ? NULL : path);
	ui.volumeSlider->setValue(_player.volume() * ui.volumeSlider->maximum() / MAX_VOLUME);
	
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
	ui.durationSlider->setValue(0);
}

void QVPlayer::on_durationSlider_valueChanged(int value)
{
	qDebug() << "Duration slider value changed, new value" << value;
	_player.setDuration(_player.length() * value / ui.durationSlider->maximum());
}

void QVPlayer::on_volumeSlider_valueChanged(int value)
{
	qDebug() << "Volume slider value changed, new value" << value;
	_player.setVolume(MAX_VOLUME * value / ui.volumeSlider->maximum());
}

void QVPlayer::on_muteBtn_clicked()
{
	if (!_player.isMute()) {
		_player.setMute(true);
		ui.muteBtn->setText("Unmute");
	} else {
		_player.setMute(false);
		ui.muteBtn->setText("Mute");
	}
}

void QVPlayer::on_updateDurationSliderTimer_timeout()
{
    if (_player.length() == 0)
        return;

	qDebug() << "updateDurationSliderTimer timeout";
	ui.durationSlider->setSliderPosition(ui.durationSlider->maximum() * _player.duration() / _player.length());
}

void QVPlayer::on_snapshotBtn_clicked()
{
    _player.takeSnapshot();
}
