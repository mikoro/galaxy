#include "mainwindow.h"

#include <QtDebug>

#include <random>

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

	stars.resize(100);

	std::random_device rd;
	std::mt19937 random(rd());
	std::uniform_real_distribution<float> randomPositionX(-width() / 2.0f, width() / 2.0f);
	std::uniform_real_distribution<float> randomPositionY(-height() / 2.0f, height() / 2.0f);
	std::uniform_real_distribution<float> randomSize(5.0f, 40.0f);

	for (size_t i = 0; i < stars.size(); ++i)
	{
		stars[i].x = randomPositionX(random);
		stars[i].y = randomPositionY(random);
		stars[i].size = randomSize(random);
		stars[i].r = 1;
		stars[i].g = 0;
		stars[i].b = 0;
		stars[i].a = 0.5f;
	}

	vertexBuffer.create();
	vertexBuffer.bind();
	vertexBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
	vertexBuffer.allocate(stars.data(), int(sizeof(Star) * stars.size()));

	vao.create();
	vao.bind();

	program.enableAttributeArray(0);
	program.enableAttributeArray(1);
	program.enableAttributeArray(2);
	program.setAttributeBuffer(0, GL_FLOAT, sizeof(float) * 0, 2, sizeof(float) * 7);
	program.setAttributeBuffer(1, GL_FLOAT, sizeof(float) * 2, 1, sizeof(float) * 7);
	program.setAttributeBuffer(2, GL_FLOAT, sizeof(float) * 3, 4, sizeof(float) * 7);

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
