#ifndef OG_WINDOW_H
#define OG_WINDOW_H

#include <QWindow>
#include <QOpenGLContext>
#include <QOpenGLPaintDevice>
#include <QPainter>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QTimer>

class OGGame;

class OGWindow : public QWindow
{
        Q_OBJECT

    public:
        explicit OGWindow(OGGame* game, QWindow* parent = 0);
        virtual ~OGWindow();

        void draw();

        void setActive(bool active);

    protected:
        void keyReleaseEvent(QKeyEvent* event);
        void keyPressEvent(QKeyEvent* event);
        void exposeEvent(QExposeEvent* event);
        void showEvent(QShowEvent* event);
        void resizeEvent(QResizeEvent* event);
        void mousePressEvent(QMouseEvent* event);
        void mouseReleaseEvent(QMouseEvent* event);
        void mouseMoveEvent(QMouseEvent* event);
        void wheelEvent(QWheelEvent* event);

    private:
        QOpenGLContext* pContext_;
        QOpenGLPaintDevice* pPaintDevice_;
        QTimer* pTimer_;
        OGGame* pGame_;

        bool _initOpenGL();

    private slots:
        void processing();
};

#endif // OG_WINDOW_H
