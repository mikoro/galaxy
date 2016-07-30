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

	float vboData[] =
	{
		10.0f, 200.0f,   1.0f, 0.0f, 0.0f,
		300.0f, 100.0f,   0.0f, 1.0f, 0.0f,
		0.0f, 0.0f,   0.0f, 0.0f, 1.0f
	};

	vertexBuffer.create();
	vertexBuffer.bind();
	vertexBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
	vertexBuffer.allocate(vboData, sizeof(vboData));

	vao.create();
	vao.bind();

	program.enableAttributeArray(0);
	program.enableAttributeArray(1);
	program.setAttributeBuffer(0, GL_FLOAT, sizeof(float) * 0, 2, sizeof(float) * 5);
	program.setAttributeBuffer(1, GL_FLOAT, sizeof(float) * 2, 3, sizeof(float) * 5);

	vao.release();
	vertexBuffer.release();
	program.release();
}

void MainWindow::resizeGL(int width, int height)
{
	viewMatrix.setToIdentity();
	viewMatrix.ortho(-width / 2, width / 2, -height / 2, height / 2, -100, 100);
}

void MainWindow::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT);

	program.bind();
	program.setUniformValue("viewMatrix", viewMatrix);
	vao.bind();
	glDrawArrays(GL_TRIANGLES, 0, 3);
	vao.release();
	program.release();
}
