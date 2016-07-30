#include "mainwindow.h"

#include <QtDebug>

MainWindow::MainWindow() : vertexBuffer(QOpenGLBuffer::VertexBuffer)
{
}

void MainWindow::initializeGL()
{
	initializeOpenGLFunctions();

	bool result = program.addShaderFromSourceFile(QOpenGLShader::Vertex, "vertex.glsl");

	if (!result)
	{
		qDebug() << program.log();
		return;
	}

	result = program.addShaderFromSourceFile(QOpenGLShader::Geometry, "geometry.glsl");

	if (!result)
	{
		qDebug() << program.log();
		return;
	}

	result = program.addShaderFromSourceFile(QOpenGLShader::Fragment, "fragment.glsl");

	if (!result)
	{
		qWarning() << program.log();
		return;
	}

	result = program.link();

	if (!result)
	{
		qWarning() << program.log();
		return;
	}

	stars.resize(4);

	stars[0].x = 0;
	stars[0].y = 0;
	stars[0].r = 1;
	stars[0].g = 0;
	stars[0].b = 0;

	stars[1].x = 30;
	stars[1].y = 30;
	stars[1].r = 0;
	stars[1].g = 1;
	stars[1].b = 0;

	stars[2].x = 60;
	stars[2].y = 60;
	stars[2].r = 0;
	stars[2].g = 0;
	stars[2].b = 1;

	stars[3].x = 90;
	stars[3].y = 90;
	stars[3].r = 1;
	stars[3].g = 0;
	stars[3].b = 1;

	vertexBuffer.create();
	vertexBuffer.bind();
	vertexBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
	vertexBuffer.allocate(stars.data(), int(sizeof(Star) * stars.size()));

	vao.create();
	vao.bind();

	program.enableAttributeArray(0);
	program.enableAttributeArray(1);
	program.setAttributeBuffer(0, GL_FLOAT, sizeof(float) * 0, 2, sizeof(float) * 5);
	program.setAttributeBuffer(1, GL_FLOAT, sizeof(float) * 2, 3, sizeof(float) * 5);

	vao.release();
	vertexBuffer.release();
	program.release();

	glEnable(GL_BLEND);
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
}

void MainWindow::resizeGL(int width, int height)
{
	projectionMatrix.setToIdentity();
	projectionMatrix.ortho(-width / 2.0f, width / 2.0f, -height / 2.0f, height / 2.0f, -100.0f, 100.0f);
}

void MainWindow::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT);

	program.bind();
	program.setUniformValue("projectionMatrix", projectionMatrix);
	vao.bind();
	glDrawArrays(GL_POINTS, 0, int(stars.size()));
	vao.release();
	program.release();
}
