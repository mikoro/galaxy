// Copyright © 2016 Mikko Ronkainen <firstname@mikkoronkainen.com>
// License: MIT, see the LICENSE file.

#pragma once

#include <QOpenGLWindow>
#include <QOpenGLFunctions_4_3_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QMatrix4x4>
#include <QElapsedTimer>

#include <vector>

#include "colorgradient.h"

#define COMPUTE_GROUP_SIZE 128

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

struct Settings
{
	int count = 32768;
	float minSize = 2.0f;
	float maxSize = 30.0f;
	float minAlpha = 0.1f;
	float maxAlpha = 0.9f;
	float smallProb = 0.99f;
	float bigProb = 0.01f;
	float maxStartVel = 20.0f;
	bool rotateStart = false;
	float minGravityDist = 1.0f;
	float gravityCoeff = 0.1f;
	float dragCoeff = 0.001f;

	void load();
};

class MainWindow : public QOpenGLWindow, protected QOpenGLFunctions_4_3_Core
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

	Settings settings;

	QOpenGLBuffer vertexBuffer;
	QOpenGLVertexArrayObject vao;
	QOpenGLShaderProgram renderProgram;
	QOpenGLShaderProgram computeProgram1;
	QOpenGLShaderProgram computeProgram2;

	QMatrix4x4 projectionMatrix;

	QElapsedTimer elapsedTimer;

	std::vector<Star> stars;
};
