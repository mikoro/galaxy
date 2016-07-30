#pragma once

#include <QtGui/QWindow>
#include <QtGui/QOpenGLFunctions>

class QPainter;
class QOpenGLContext;
class QOpenGLPaintDevice;

class OpenGLWindow : public QWindow, protected QOpenGLFunctions
{
	Q_OBJECT

public:

	explicit OpenGLWindow(QWindow* parent = nullptr);
	~OpenGLWindow();

	virtual void render(QPainter* painter);
	virtual void render();
	virtual void initialize();

	void setAnimating(bool animating);

public slots:

	void renderLater();
	void renderNow();

protected:

	bool event(QEvent* event) override;
	void exposeEvent(QExposeEvent* event) override;

private:

	bool update_pending = false;
	bool animating = false;

	QOpenGLContext* context = nullptr;
	QOpenGLPaintDevice* device = nullptr;
};
