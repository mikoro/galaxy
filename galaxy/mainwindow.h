// Copyright © 2016 Mikko Ronkainen <firstname@mikkoronkainen.com>
// License: MIT, see the LICENSE file.

#pragma once

#include <QOpenGLWindow>
#include <QOpenGLFunctions_4_5_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QMatrix4x4>

#include <vector>

#include "colorgradient.h"

#define STAR_COUNT 1024
#define COMPUTE_GROUP_SIZE 128
#define STAR_MIN_SIZE 1.0f
#define STAR_MAX_SIZE 30.0f

struct Star
{
	float x;
	float y;
	float z;
	float size;
	Color color;
};

class MainWindow : public QOpenGLWindow, protected QOpenGLFunctions_4_5_Core
{
public:

	MainWindow();

	void initializeGL() override;
	void resizeGL(int width, int height) override;
	void paintGL() override;

private:

	QOpenGLBuffer vertexBuffer;
	QOpenGLVertexArrayObject vao;
	QOpenGLShaderProgram renderProgram;
	QOpenGLShaderProgram computeProgram1;
	QOpenGLShaderProgram computeProgram2;

	QMatrix4x4 projectionMatrix;

	std::vector<Star> stars;
};
