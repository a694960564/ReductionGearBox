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
#include <QWheelEvent>
#include <QMouseEvent>
#include "object/box/Box.h"
#include "object/model/Model.h"
namespace Ui {
class gl_win;
}

class gl_win : public QOpenGLWidget , protected QOpenGLExtraFunctions
{
    Q_OBJECT
public:
    explicit gl_win(QWidget *parent = nullptr);
    ~gl_win()override;
protected:
    void initializeGL()override;
    void resizeGL(int w,int h)override;
    void paintGL()override;
//    void mousePressEvent(QMouseEvent *event) override;
//    void mouseReleaseEvent(QMouseEvent *event) override;
//    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
private:
    Ui::gl_win *ui;
    unsigned int ID;
    int width, height;
    float fov;
    std::shared_ptr<QTimer>_timer;

    void initializeShader(const GLchar*vertexPath,const GLchar*fragmentPath);

    glm::mat4 viewMatrix;//setLookAt
    glm::mat4 projectionMatrix;//perspective
    glm::mat4 viewProjectionMatrix;//=projectionMatrix * viewMatrix
    glm::mat4 modelViewProjectionMatrix;

private:
    Box* box;
    Model* model;
};

#endif // GL_WIN_H
