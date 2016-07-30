#include "mainwindow.h"

#include <QGuiApplication>

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);

	QSurfaceFormat format;
	format.setSwapInterval(0);

	MainWindow window;
	window.setFormat(format);
	window.resize(1280, 720);
	window.setTitle("Galaxy");
	window.show();

	window.setAnimating(true);

	return app.exec();
}
