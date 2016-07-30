// Copyright © 2016 Mikko Ronkainen <firstname@mikkoronkainen.com>
// License: MIT, see the LICENSE file.

#include "mainwindow.h"

#include <QtDebug>

#include <array>
#include <iostream>
#include <iomanip>
#include <random>

MainWindow::MainWindow() : vertexBuffer(QOpenGLBuffer::VertexBuffer)
{
}

void MainWindow::initializeGL()
{
	initializeOpenGLFunctions();

	bool result = renderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, "vertex.glsl");

	if (!result)
	{
		qDebug() << renderProgram.log();
		return;
	}

	result = renderProgram.addShaderFromSourceFile(QOpenGLShader::Geometry, "geometry.glsl");

	if (!result)
	{
		qDebug() << renderProgram.log();
		return;
	}

	result = renderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, "fragment.glsl");

	if (!result)
	{
		qWarning() << renderProgram.log();
		return;
	}

	result = renderProgram.link();

	if (!result)
	{
		qWarning() << renderProgram.log();
		return;
	}

	result = computeProgram1.addShaderFromSourceFile(QOpenGLShader::Compute, "compute1.glsl");

	if (!result)
	{
		qWarning() << computeProgram1.log();
		return;
	}

	result = computeProgram1.link();

	if (!result)
	{
		qWarning() << computeProgram1.log();
		return;
	}

	stars.resize(STAR_COUNT);

	std::random_device rd;
	std::mt19937 random(rd());
	std::uniform_real_distribution<float> randomPositionX(-width() / 2.0f, width() / 2.0f);
	std::uniform_real_distribution<float> randomPositionY(-height() / 2.0f, height() / 2.0f);
	std::array<float, 3> x = {{STAR_MIN_SIZE, (STAR_MAX_SIZE - STAR_MIN_SIZE) / 2.0f, STAR_MAX_SIZE}};
	std::array<float, 2> p = {{0.9f, 0.1f}};
	std::piecewise_constant_distribution<float> randomSize(x.begin(), x.end(), p.begin());
	std::uniform_real_distribution<float> randomAlpha(0.4f, 0.8f);

	ColorGradient gradient;
	gradient.addSegment(Color(1.0f, 1.0f, 1.0f), Color(1.0f, 1.0f, 0.0f), 10);
	gradient.addSegment(Color(1.0f, 1.0f, 0.0f), Color(1.0f, 0.0f, 0.0f), 10);

	for (size_t i = 0; i < stars.size(); ++i)
	{
		stars[i].x = randomPositionX(random);
		stars[i].y = randomPositionY(random);
		stars[i].z = 0.0f;
		stars[i].size = randomSize(random);
		stars[i].color = gradient.getColor((stars[i].size - STAR_MIN_SIZE) / (STAR_MAX_SIZE - STAR_MIN_SIZE));
		stars[i].color.a = randomAlpha(random);
	}

	vertexBuffer.create();
	vertexBuffer.bind();
	vertexBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
	vertexBuffer.allocate(stars.data(), int(sizeof(Star) * stars.size()));

	vao.create();
	vao.bind();

	renderProgram.enableAttributeArray(0);
	renderProgram.enableAttributeArray(1);
	renderProgram.enableAttributeArray(2);
	renderProgram.setAttributeBuffer(0, GL_FLOAT, sizeof(float) * 0, 3, sizeof(float) * 8);
	renderProgram.setAttributeBuffer(1, GL_FLOAT, sizeof(float) * 3, 1, sizeof(float) * 8);
	renderProgram.setAttributeBuffer(2, GL_FLOAT, sizeof(float) * 4, 4, sizeof(float) * 8);

	vao.release();
	vertexBuffer.release();
	renderProgram.release();

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
	computeProgram1.bind();
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, vertexBuffer.bufferId());
	glDispatchCompute(STAR_COUNT / COMPUTE_GROUP_SIZE, 1, 1);
	glMemoryBarrier(GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);
	computeProgram1.release();

	glClear(GL_COLOR_BUFFER_BIT);

	renderProgram.bind();
	renderProgram.setUniformValue("projectionMatrix", projectionMatrix);
	vao.bind();
	glDrawArrays(GL_POINTS, 0, int(stars.size()));
	vao.release();
	renderProgram.release();

	update();
}
