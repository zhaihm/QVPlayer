#include "VLCPlayer.h"
#include <QtWidgets>
#include <QDebug>
#include <QtGlobal>

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
	Q_ASSERT_X(_instance == NULL && _mediaPlayer == NULL, __FUNCTION__, "Already has a vlc instance running!");

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
	Q_ASSERT_X(_instance != NULL && _mediaPlayer != NULL, __FUNCTION__, "Media player not initialized!");

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

void VLCPlayer::pause()
{
	Q_ASSERT_X(_instance != NULL && _mediaPlayer != NULL, __FUNCTION__, "Media player not initialized!");
	libvlc_media_player_pause(_mediaPlayer);
}

void VLCPlayer::stop()
{
	Q_ASSERT_X(_instance != NULL && _mediaPlayer != NULL, __FUNCTION__, "Media player not initialized!");
	libvlc_media_player_stop(_mediaPlayer);
}

bool VLCPlayer::isPaused()
{
	Q_ASSERT_X(_instance != NULL && _mediaPlayer != NULL, __FUNCTION__, "Media player not initialized!");
	return libvlc_Paused == libvlc_media_player_get_state(_mediaPlayer);
}

bool VLCPlayer::isStopped()
{
	Q_ASSERT_X(_instance != NULL && _mediaPlayer != NULL, __FUNCTION__, "Media player not initialized!");
	return libvlc_Stopped == libvlc_media_player_get_state(_mediaPlayer);
}

void VLCPlayer::setDuration(int ms)
{
	Q_ASSERT_X(_instance != NULL && _mediaPlayer != NULL, __FUNCTION__, "Media player not initialized!");
	libvlc_media_player_set_time(_mediaPlayer, ms);
}

int VLCPlayer::length()
{
	Q_ASSERT_X(_instance != NULL && _mediaPlayer != NULL, __FUNCTION__, "Media player not initialized!");
	return libvlc_media_player_get_length(_mediaPlayer);
}

void VLCPlayer::setVolume(int volume)
{
	Q_ASSERT_X(_instance != NULL && _mediaPlayer != NULL, __FUNCTION__, "Media player not initialized!");
	libvlc_audio_set_volume(_mediaPlayer, volume);
}

int VLCPlayer::volume()
{
	Q_ASSERT_X(_instance != NULL && _mediaPlayer != NULL, __FUNCTION__, "Media player not initialized!");
	return libvlc_audio_get_volume(_mediaPlayer);
}

void VLCPlayer::setMute(bool mute)
{
	Q_ASSERT_X(_instance != NULL && _mediaPlayer != NULL, __FUNCTION__, "Media player not initialized!");
	libvlc_audio_set_mute(_mediaPlayer, mute ? 1 : 0);
}

bool VLCPlayer::isMute()
{
	Q_ASSERT_X(_instance != NULL && _mediaPlayer != NULL, __FUNCTION__, "Media player not initialized!");
	return libvlc_audio_get_mute(_mediaPlayer) == 1;
}
