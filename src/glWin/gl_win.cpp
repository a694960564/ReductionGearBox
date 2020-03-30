#include "gl_win.h"
#include "ui_gl_win.h"
#include <glut.h>
#include <QDebug>
#include <fstream>
#include <sstream>

gl_win::gl_win(QWidget *parent) :
    QOpenGLWidget(parent),
    ui(new Ui::gl_win)
{
    ui->setupUi(this);

}

gl_win::~gl_win()
{
    delete ui;
}
void gl_win::initializeGL() {
    // 初始化函数
    initializeOpenGLFunctions();
    glClearColor(0,0,0,1);

//    unsigned int VAO;
//    glGenVertexArrays(1, &VAO);
//    glBindVertexArray(VAO);

    doVertexShader();
    doFragmentShader();
    bindShader();

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    qDebug()<<"sizeof(vertices):"<<sizeof(vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof (vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void gl_win::resizeGL(int w, int h) {
    // 窗口大小变化时 调整大小
    glViewport(0,0,w,h);
}

void gl_win::paintGL() {
    //清除之前图形并将背景设置为 blue
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}
void gl_win::doVertexShader(){
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    std::string shaderCode = getShaderCode("../src/shaderSource/vertexshader.vert");
    const char* code = shaderCode.c_str();
    qDebug()<<"VertexCode:"<<code;
    glShaderSource(vertexShader, 1, &code, nullptr);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        qDebug()<<"Error::shader::vertex::compilation_failed:"<<infoLog;
    }
}

void gl_win::doFragmentShader(){
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string shaderCode = getShaderCode("../src/shaderSource/fragmentshader.frag");
    const char* code = shaderCode.c_str();
    qDebug()<<"FragmentCode:"<<code;
    glShaderSource(fragmentShader, 1, &code, nullptr);
    glCompileShader(fragmentShader);
    int success;
    char infoLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        qDebug()<<"Error::shader::fragment::compilation_failed:"<<infoLog;
    }
}

void gl_win::bindShader(){
    unsigned int shaderPorgram;
    shaderPorgram = glCreateProgram();
    glAttachShader(shaderPorgram, vertexShader);
    glAttachShader(shaderPorgram, fragmentShader);
    glLinkProgram(shaderPorgram);
    int success;
    char infoLog[512];
    glGetProgramiv(shaderPorgram, GL_LINK_STATUS, &success)    ;
    if(!success){
        glGetProgramInfoLog(shaderPorgram, 512, nullptr, infoLog);
    }
    glUseProgram(shaderPorgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

std::string gl_win::getShaderCode(const GLchar *path){
    qDebug()<<path;
    std::ifstream fileStream;
    fileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    std::string code;
    try{
        fileStream.open(path);
        std::stringstream stringstream;
        stringstream << fileStream.rdbuf();
        fileStream.close();
        code = stringstream.str();
    }catch(std::ifstream::failure e){
        qDebug()<<"Error::shader::file_not_succesfully_read!";
    }
    return code;
}
