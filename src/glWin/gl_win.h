#ifndef GL_WIN_H
#define GL_WIN_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QTimer>
#include <gl/GLU.h>

namespace Ui {
class gl_win;
}

class gl_win : public QOpenGLWidget , protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit gl_win(QWidget *parent = nullptr);
    ~gl_win();
protected:
    void initializeGL();
    void resizeGL(int w,int h);
    void paintGL();
private:
    Ui::gl_win *ui;

    int R;
    double x,y,z;
    bool wired;
    float ang;
    QTimer timer;
};

#endif // GL_WIN_H
