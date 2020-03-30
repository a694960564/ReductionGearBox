#ifndef GL_WIN_H
#define GL_WIN_H
#define GLUT_DISABLE_ATEXIT_HACK

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QTimer>
#include <gl/GLU.h>
#include <QOpenGLExtraFunctions>

namespace Ui {
class gl_win;
}


class gl_win : public QOpenGLWidget , protected QOpenGLExtraFunctions
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

    void doVertexShader();
    void doFragmentShader();
    void bindShader();

    unsigned int vertexShader;
    unsigned int fragmentShader;

    float vertices[9] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    std::string getShaderCode(const GLchar*);
};

#endif // GL_WIN_H
