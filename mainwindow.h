// Copyright © 2016 Mikko Ronkainen <firstname@mikkoronkainen.com>
// License: MIT, see the LICENSE file.

#pragma once

#include <QOpenGLWindow>
#include <QOpenGLFunctions_4_5_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QMatrix4x4>
#include <QElapsedTimer>

#include <vector>

#include "colorgradient.h"

#define STAR_COUNT 32768
#define COMPUTE_GROUP_SIZE 512
#define STAR_MIN_SIZE 2.0f
#define STAR_MAX_SIZE 30.0f

struct Vec4f
{
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float w = 0.0f;
};

struct Star
{
	Vec4f position;
	Vec4f velocity;
	Vec4f force;
	Vec4f size;
	Color color;
};

class MainWindow : public QOpenGLWindow, protected QOpenGLFunctions_4_5_Core
{
public:

	MainWindow();

	void initializeGL() override;
	void resizeGL(int width, int height) override;
	void paintGL() override;

protected:

	void keyPressEvent(QKeyEvent* event) override;

private:

	void initStars();

	QOpenGLBuffer vertexBuffer;
	QOpenGLVertexArrayObject vao;
	QOpenGLShaderProgram renderProgram;
	QOpenGLShaderProgram computeProgram1;
	QOpenGLShaderProgram computeProgram2;

	QMatrix4x4 projectionMatrix;

	QElapsedTimer elapsedTimer;

	std::vector<Star> stars;
};
