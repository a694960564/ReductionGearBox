#include "gl_win.h"
#include "ui_gl_win.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <qmath.h>

gl_win::gl_win(QWidget *parent) :
    QOpenGLWidget(parent),
    ui(new Ui::gl_win),
    fov(45.0),
    _timer(std::make_shared<QTimer>())
{
    ui->setupUi(this);
    connect(_timer.get(),&QTimer::timeout,[=](){
       this->update();
    });
    _timer->start(20);
}

gl_win::~gl_win()
{
    delete ui;
}
void gl_win::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0,0,0,1);
    initializeShader("../src/object/model/vertexshader.vert","../src/object/model/fragmentshader.frag");
    gearBox = new GearBox(ID);
    gearBox->initialize(glm::mat4(1.0));
}

void gl_win::resizeGL(int w, int h) {
    glViewport(0,0,w,h);
}

void gl_win::paintGL() {
    static float i = 0.0;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    projectionMatrix = glm::perspective(fov, float(this->width()) / float(this->height()), 1.0f, 10000.0f);
    glm::vec3 camera = {500*glm::sin(glm::radians(i)), 0.0, -500*glm::cos(glm::radians(i))};
    viewMatrix = glm::lookAt(camera, glm::vec3(0,0,0), glm::vec3(0,1,0));
//    i++;
    viewProjectionMatrix = projectionMatrix * viewMatrix;
    gearBox->viewPos = camera;
    gearBox->draw(viewProjectionMatrix);
}

void gl_win::initializeShader(const GLchar *vertexPath,const GLchar *fragmentPath){
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        vShaderFile.close();
        fShaderFile.close();
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    } catch (std::ifstream::failure e) {
        qDebug()<<"Error::shader::file_not_succesfully_read!";
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        qDebug()<<"Error::shader::VERTEX::compilation_failed:"<<infoLog;

    }
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        qDebug()<<"Error::shader::fragment::compilation_failed:"<<infoLog;
    }
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(ID, 512, nullptr, infoLog);
        qDebug()<<"Error::shader::program::linking_failed:"<<infoLog;
    }
    glUseProgram(ID);
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void gl_win::wheelEvent(QWheelEvent *event) {
    if(event->angleDelta().y() > 0){
        fov+=0.1f;
    }else{
        fov-=0.1f;
    }
    projectionMatrix = glm::perspective(fov, float(this->width()) / float(this->height()), 1.0f, 10.0f);
}
