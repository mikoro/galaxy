#pragma once

#include <QOpenGLWindow>
#include <QOpenGLFunctions_4_5_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QMatrix4x4>

class MainWindow : public QOpenGLWindow, protected QOpenGLFunctions_4_5_Core
{
public:

	MainWindow();

	void initializeGL() override;
	void resizeGL(int width, int height) override;
	void paintGL() override;

private:

	QOpenGLShaderProgram program;
	QOpenGLBuffer vertexBuffer;
	QOpenGLVertexArrayObject vao;

	QMatrix4x4 viewMatrix;
};
