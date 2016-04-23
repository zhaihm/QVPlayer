# QVPlayer
Quick Video Player.

### Requirements
* Qt5 (5.6.0 recommended)
* VLC player (2.2.2 recommended)
* On Windows
	* Microsoft Visual Studio (VS2015 recommended)
* On Mac OS X
	* Xcode (XCode 7.3 recommended)

### Build Steps
* Clone the repository `git clone https://github.com/zhaihm/QVPlayer.git`
* On Windows
	* Copy these files to QVPlayer\Win32\Debug (mkdir if it doesn't exist): vlc\plugins\*, vlc\libvlc.dll, vlc\libvlccore.dll (I didn't import them into project, due to size reason)
	* Build the project with VS	
* On Mac OS X
	* `cd QVPlayer/QVPlayer`
	* Generate Xcode project file using: `qmake QVPlayer.pro -spec macx-xcode`
	* Open QVPlayer.xcodeproj with Xcode and build (currently there is linking issues with VLC)