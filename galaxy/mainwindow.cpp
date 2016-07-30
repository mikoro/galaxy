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

	result = computeProgram2.addShaderFromSourceFile(QOpenGLShader::Compute, "compute2.glsl");

	if (!result)
	{
		qWarning() << computeProgram2.log();
		return;
	}

	result = computeProgram2.link();

	if (!result)
	{
		qWarning() << computeProgram2.log();
		return;
	}

	stars.resize(STAR_COUNT);

	std::random_device rd;
	std::mt19937 random(rd());
	std::uniform_real_distribution<float> randomPositionX(-width() / 2.0f, width() / 2.0f);
	std::uniform_real_distribution<float> randomPositionY(-height() / 2.0f, height() / 2.0f);
	std::uniform_real_distribution<float> randomVelocity(-10.0f, 10.0f);
	std::array<float, 3> x = {{STAR_MIN_SIZE, (STAR_MAX_SIZE - STAR_MIN_SIZE) / 2.0f, STAR_MAX_SIZE}};
	std::array<float, 2> p = {{0.9f, 0.1f}};
	std::piecewise_constant_distribution<float> randomSize(x.begin(), x.end(), p.begin());
	std::uniform_real_distribution<float> randomAlpha(0.4f, 0.8f);

	ColorGradient gradient;
	gradient.addSegment(Color(1.0f, 1.0f, 1.0f), Color(1.0f, 1.0f, 0.0f), 10);
	gradient.addSegment(Color(1.0f, 1.0f, 0.0f), Color(1.0f, 0.0f, 0.0f), 10);

	for (size_t i = 0; i < stars.size(); ++i)
	{
		stars[i].position.x = randomPositionX(random);
		stars[i].position.y = randomPositionY(random);
		stars[i].position.z = 0.0f;
		stars[i].position.w = 1.0f;
		stars[i].velocity.x = randomVelocity(random);
		stars[i].velocity.y = randomVelocity(random);
		stars[i].velocity.x = 0.0f;
		stars[i].velocity.y = 0.0f;
		stars[i].velocity.z = 0.0f;
		stars[i].velocity.w = 0.0f;
		stars[i].force.x = 0.0f;
		stars[i].force.y = 0.0f;
		stars[i].force.z = 0.0f;
		stars[i].force.w = 0.0f;
		stars[i].size.x = randomSize(random);
		stars[i].size.y = stars[i].size.x;
		stars[i].size.z = 0.0f;
		stars[i].size.w = 0.0f;
		stars[i].color = gradient.getColor((std::max(stars[i].size.x, stars[i].size.y) - STAR_MIN_SIZE) / (STAR_MAX_SIZE - STAR_MIN_SIZE));
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
	renderProgram.enableAttributeArray(3);
	renderProgram.enableAttributeArray(4);
	renderProgram.setAttributeBuffer(0, GL_FLOAT, sizeof(float) * 0, 4, sizeof(Star));
	renderProgram.setAttributeBuffer(1, GL_FLOAT, sizeof(float) * 4, 4, sizeof(Star));
	renderProgram.setAttributeBuffer(2, GL_FLOAT, sizeof(float) * 8, 4, sizeof(Star));
	renderProgram.setAttributeBuffer(3, GL_FLOAT, sizeof(float) * 12, 4, sizeof(Star));
	renderProgram.setAttributeBuffer(4, GL_FLOAT, sizeof(float) * 16, 4, sizeof(Star));

	vao.release();
	vertexBuffer.release();
	renderProgram.release();

	glEnable(GL_BLEND);
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

	elapsedTimer.restart();
}

void MainWindow::resizeGL(int width, int height)
{
	projectionMatrix.setToIdentity();
	projectionMatrix.ortho(-width / 2.0f, width / 2.0f, -height / 2.0f, height / 2.0f, -100.0f, 100.0f);
}

void MainWindow::paintGL()
{
	float dt = (float)((double)elapsedTimer.nsecsElapsed() / 1000000000.0);
	elapsedTimer.restart();

	computeProgram1.bind();
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, vertexBuffer.bufferId());
	glDispatchCompute(STAR_COUNT / COMPUTE_GROUP_SIZE, 1, 1);
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
	computeProgram1.release();

	computeProgram2.bind();
	computeProgram2.setUniformValue("dt", dt);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, vertexBuffer.bufferId());
	glDispatchCompute(STAR_COUNT / COMPUTE_GROUP_SIZE, 1, 1);
	glMemoryBarrier(GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);
	computeProgram2.release();

	glClear(GL_COLOR_BUFFER_BIT);

	renderProgram.bind();
	renderProgram.setUniformValue("projectionMatrix", projectionMatrix);
	vao.bind();
	glDrawArrays(GL_POINTS, 0, int(stars.size()));
	vao.release();
	renderProgram.release();

	update();
}
