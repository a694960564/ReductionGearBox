#include "gl_win.h"
#include "ui_gl_win.h"
#include <QtOpenGL/glut.h>

#define PI 3.14159265358979323846
#define PI2 6.28318530717958647692

GLsizei width = 600,height = 600;

int uStepsNum = 50,vStepNum = 50;
gl_win::gl_win(QWidget *parent) :
    QOpenGLWidget(parent),
    ui(new Ui::gl_win)
{
    ui->setupUi(this);

    this->R = 1;
    this->wired = false;
    this->ang = 0.5;
    x = 0;
    y = 0;
    z = 0;
//    connect(&timer,SIGNAL(timeout()), this, SLOT(updateGL()));
//    timer.start(16);
}

gl_win::~gl_win()
{
    delete ui;
}

void gl_win::initializeGL() {
    // 初始化函数
    initializeOpenGLFunctions();


    glClearColor(0,1,1,1);
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0,1,1,1);
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GLfloat light_position [ ] = { 1.0f, 1.0f, 1.0f, 0.0f };
    GLfloat light_ambient  [ ] = { 0.2f, 0.2f, 0.2f, 0.2f };
    GLfloat light_diffuse  [ ] = { 0.5f, 0.5f, 0.5f, 0.2f };
    GLfloat light_specular [ ] = { 0.5f, 0.5f, 0.5f, 0.2f };
    glLightfv(GL_LIGHT0, GL_POSITION,  light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT,   light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,   light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR,  light_specular);

    glEnable (GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_AUTO_NORMAL);
    glEnable (GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc (GL_LESS);
}

void gl_win::resizeGL(int w, int h) {
    // 窗口大小变化时 调整大小
    glViewport(0,0,w,h);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(45.0,(float)w/h,0.01,100.0);
//    update();
}

class Point
{
public:
    Point(){};
    Point(double a,double b,double c):x(a),y(b),z(c){};
public:
    double x;
    double y;
    double z;
};
Point getPoint(double u,double v)
{
    double x = sin(PI*v)*cos(PI2*u);
    double y = sin(PI*v)*sin(PI2*u);
    double z = cos(PI*v);
    return Point(x,y,z);
}
void drawWire()
{
    double ustep = 1/(double)uStepsNum, vstep = 1/(double)vStepNum;
    double u = 0,v = 0;
    //绘制下端三角形组
    for(int i = 0;i<uStepsNum;i++)
    {
        glBegin(GL_LINE_LOOP);
        Point a = getPoint(0,0);
        glVertex3d(a.x,a.y,a.z);
        Point b = getPoint(u,vstep);
        glVertex3d(b.x,b.y,b.z);
        Point c = getPoint(u+ustep,vstep);
        glVertex3d(c.x,c.y,c.z);
        u += ustep;
        glEnd();
    }
    //绘制中间四边形组
    u = 0, v = vstep;
    for(int i=1;i<vStepNum-1;i++)
    {
        for(int j=0;j<uStepsNum;j++)
        {
            glBegin(GL_LINE_LOOP);
            Point a = getPoint(u,v);
            Point b = getPoint(u+ustep,v);
            Point c = getPoint(u+ustep,v+vstep);
            Point d = getPoint(u,v+vstep);
            glVertex3d(a.x,a.y,a.z);
            glVertex3d(b.x,b.y,b.z);
            glVertex3d(c.x,c.y,c.z);
            glVertex3d(d.x,d.y,d.z);
            u += ustep;
            glEnd();
        }
        v += vstep;
    }
    //绘制下端三角形组
    u = 0;
    for(int i=0;i<uStepsNum;i++)
    {
        glBegin(GL_LINE_LOOP);
        Point a = getPoint(0,1);
        Point b = getPoint(u,1-vstep);
        Point c = getPoint(u+ustep,1-vstep);
        glVertex3d(a.x,a.y,a.z);
        glVertex3d(b.x,b.y,b.z);
        glVertex3d(c.x,c.y,c.z);
        glEnd();
    }
}
void gl_win::paintGL() {
    //清除之前图形并将背景设置为 blue
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0,0.0,0.0);
    glPointSize(1.0);
    glRotated(30,1,0,0);
    glRotated(60,0,1,0);
    glRotated(90,0,0,1);
    drawWire();
    //glutSwapBuffers();
}
