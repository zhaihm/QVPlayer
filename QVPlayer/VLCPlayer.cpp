#include "VLCPlayer.h"
#include <QtWidgets>
#include <QDebug>

VLCPlayer::VLCPlayer()
{
	_instance = NULL;
	_mediaPlayer = NULL;
}

VLCPlayer::~VLCPlayer()
{
}

void VLCPlayer::init(HWND hWnd)
{
	if (_instance != NULL || _mediaPlayer != NULL) {
		qDebug() << "Already has a vlc instance running!";
		return;
	}

	if (NULL == (_instance = libvlc_new(0, NULL))) {
		qDebug() << "libvlc_new failed: " << libvlc_errmsg();
		return;
	}
	if (NULL == (_mediaPlayer = libvlc_media_player_new(_instance))) {
		qDebug() << "libvlc_media_player_new failed: " << libvlc_errmsg();
		return;
	}
	libvlc_media_player_set_hwnd(_mediaPlayer, hWnd);
}

void VLCPlayer::play(const char *path /*= NULL*/)
{
	if (path != NULL) {
		libvlc_media_t *media;
		if (NULL == (media = libvlc_media_new_path(_instance, path))) {
			qDebug() << "libvlc_media_new_path failed: " << libvlc_errmsg();
			return;
		}
		libvlc_media_player_set_media(_mediaPlayer, media);
	}
	libvlc_media_player_play(_mediaPlayer);
}

void VLCPlayer::setDuration(int ms)
{
	libvlc_media_player_set_time(_mediaPlayer, ms);
}

int VLCPlayer::length()
{
	return libvlc_media_player_get_length(_mediaPlayer);
}
