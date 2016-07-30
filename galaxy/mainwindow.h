#pragma once

#include <openglwindow.h>

#include <QtGui/QOpenGLShaderProgram>

class MainWindow : public OpenGLWindow
{
public:

	void initialize() override;
	void render() override;

private:

	GLuint m_posAttr;
	GLuint m_colAttr;
	GLuint m_matrixUniform;

	QOpenGLShaderProgram* m_program;
	int m_frame;
};
