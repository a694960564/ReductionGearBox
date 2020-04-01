#include "gl_win.h"
#include "ui_gl_win.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "common/stb_image.h"
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
    initializeOpenGLFunctions();
    glClearColor(0,0,0,1);
    initializeShader("../src/shaderSource/vertexshader.vert","../src/shaderSource/fragmentshader.frag");
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    qDebug()<<"sizeof(vertices):"<<sizeof(vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof (vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);
    viewMatrix = glm::lookAt(glm::vec3(0,0,2), glm::vec3(0,0,0), glm::vec3(0,1,0));
    initializeTexture("../src/image/container.jpg");
}

void gl_win::resizeGL(int w, int h) {
    glViewport(0,0,w,h);
    projectionMatrix = glm::perspective(45.0f, float(w) / float(h), 1.0f, 10.0f);
}
void gl_win::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);
    viewProjectionMatrix = projectionMatrix * viewMatrix;
    glm::mat4 modelMatrix(1.0);
    modelMatrix = glm::translate(modelMatrix,glm::vec3(0,0,0));
    modelMatrix = glm::rotate(modelMatrix, float(glm::radians(-60.0)), glm::vec3(1,0,0));
    modelViewProjectionMatrix = viewProjectionMatrix * modelMatrix;
    glUniformMatrix4fv(glGetUniformLocation(ID, "u_Matrix"), 1, false, glm::value_ptr(modelViewProjectionMatrix));
    glBindTexture(GL_TEXTURE_2D, texture);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 6);
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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

void gl_win::initializeTexture(const char *path){
    glGenTextures(1, &texture);
    if(texture == 0){
        qDebug()<<"Could not generate a new OpenGL texture object.";
        return;
    }
    glBindTexture(GL_TEXTURE_2D, texture);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    if(data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glActiveTexture(GL_TEXTURE0);
        glUniform1i(glGetUniformLocation(ID,"ourTexture"), 0);
        qDebug()<<"Get texture:";
    }else {
        qDebug()<<"Failed to load texture";
    }
    stbi_image_free(data);
}
