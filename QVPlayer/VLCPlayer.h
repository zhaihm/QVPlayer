#pragma once
#include <vlc/vlc.h>
#include <Windows.h>

class VLCPlayer
{
public:
	VLCPlayer();
	~VLCPlayer();

	void init(HWND hWnd);
	void play(const char *path = NULL);
	void pause();
	void stop();
	bool isPaused();
	bool isStopped();
	void setDuration(int ms);
	int length();
	void setVolume(int volume);
	int volume();
	void setMute(bool mute);
	bool isMute();

private:
	libvlc_instance_t		*_instance;
	libvlc_media_player_t	*_mediaPlayer;
};

