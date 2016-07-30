#pragma once

#include <QOpenGLWindow>
#include <QOpenGLFunctions_4_5_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

class MainWindow : public QOpenGLWindow, protected QOpenGLFunctions_4_5_Core
{
public:

	void initializeGL() override;
	void resizeGL(int width, int height) override;
	void paintGL() override;

private:

	QOpenGLShaderProgram* program = nullptr;
	QOpenGLBuffer* vertexBuffer = nullptr;
	QOpenGLVertexArrayObject* vao = nullptr;
};
