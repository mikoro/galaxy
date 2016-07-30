// Copyright © 2016 Mikko Ronkainen <firstname@mikkoronkainen.com>
// License: MIT, see the LICENSE file.

#include "mainwindow.h"

#include <QGuiApplication>

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);

	QSurfaceFormat format;
	format.setRenderableType(QSurfaceFormat::OpenGL);
	format.setProfile(QSurfaceFormat::CoreProfile);
	format.setVersion(4,5);
	format.setSwapInterval(1);

	MainWindow window;
	window.setFormat(format);
	window.resize(1280, 720);
	window.setTitle("Galaxy");
	window.show();

	return app.exec();
}
