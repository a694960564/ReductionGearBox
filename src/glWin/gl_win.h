#ifndef GL_WIN_H
#define GL_WIN_H
#define GLUT_DISABLE_ATEXIT_HACK

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QTimer>
//#include <gl/GLU.h>
#include <QOpenGLExtraFunctions>
#include <QDebug>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>

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

    unsigned int ID;

    void initializeShader(const GLchar*vertexPath,const GLchar*fragmentPath);

    float vertices[18] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    glm::mat4 viewMatrix;//setLookAt
    glm::mat4 projectionMatrix;//perspective
    glm::mat4 viewProjectionMatrix;//=projectionMatrix * viewMatrix
    glm::mat4 modelViewProjectionMatrix;
};

#endif // GL_WIN_H
