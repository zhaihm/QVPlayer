# QVPlayer
Quick Video Player.

### Requirements
* Microsoft Visual Studio (VS2015 recommended)
* Qt5 (5.6.0 recommended)
* VLC player (2.2.2 recommended)

### Build Steps
* Clone the repository `git clone https://github.com/zhaihm/QVPlayer.git`
* Copy these files to QVPlayer\Win32\Debug (mkdir if it doesn't exist): vlc\plugins\*, vlc\libvlc.dll, vlc\libvlccore.dll (I didn't import them into project, due to size reason)
* Build the project with VS