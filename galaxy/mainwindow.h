#pragma once

#include <openglwindow.h>

#include <QtGui/QOpenGLShaderProgram>

class MainWindow : public OpenGLWindow
{
public:

	void initialize() override;
	void render() override;

private:

	QOpenGLShaderProgram* program = nullptr;
};
