#include "qvplayer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QVPlayer w;
	w.show();
	return a.exec();
}
