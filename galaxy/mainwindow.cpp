#include "mainwindow.h"

#include <QtDebug>

void MainWindow::initialize()
{
	program = new QOpenGLShaderProgram(this);
	bool result = program->addShaderFromSourceFile(QOpenGLShader::Vertex, "vertex.glsl");

	if (!result)
	{
		qDebug() << program->log();
		return;
	}

	result = program->addShaderFromSourceFile(QOpenGLShader::Fragment, "fragment.glsl");

	if (!result)
	{
		qWarning() << program->log();
		return;
	}

	result = program->link();

	if (!result)
	{
		qWarning() << program->log();
		return;
	}
}

void MainWindow::render()
{

}
