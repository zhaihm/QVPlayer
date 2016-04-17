#include "qvplayer.h"
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <vlc/vlc.h>

QVPlayer::QVPlayer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

QVPlayer::~QVPlayer()
{

}

void QVPlayer::on_playBtn_clicked()
{
	qDebug() << "Play button clicked";

	libvlc_instance_t		*pInstance;
	libvlc_media_player_t	*pMediaPlayer;
	libvlc_media_t			*pMedia;
	QString movieFile;

	
	QFileDialog fileDlg;
	if (!fileDlg.exec())
		return;
	
	movieFile = fileDlg.selectedFiles()[0];
	qDebug() << "moviefile: " << movieFile.toStdString().c_str();

	if (NULL == (pInstance = libvlc_new(0, NULL))) {
		qDebug() << "libvlc_new failed: " << libvlc_errmsg();
		return;
	}
	if (NULL == (pMediaPlayer = libvlc_media_player_new(pInstance))) {
		qDebug() << "libvlc_media_player_new failed: " << libvlc_errmsg();
		return;
	}
	if (NULL == (pMedia = libvlc_media_new_path(pInstance, movieFile.replace('/', '\\').toStdString().c_str()))) { // vlc only accept '\' as directory seperator
		qDebug() << "libvlc_media_new_path failed: " << libvlc_errmsg();
		return;
	}
	libvlc_media_player_set_media(pMediaPlayer, pMedia);
	libvlc_media_player_set_hwnd(pMediaPlayer, (HWND)ui.videoWnd->winId());
	libvlc_media_player_play(pMediaPlayer);
}

void QVPlayer::on_exitBtn_clicked()
{
	exit(0);
}
