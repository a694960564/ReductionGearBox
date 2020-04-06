#include "Box.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "common/stb_image.h"
#include <QDebug>

Box::Box(unsigned int&id):Object (&id)
{
}

void Box::initialize(){
    initializeOpenGLFunctions();
    float vertices[48] = {
        0.0f,  0.0f,  -0.5f, 1.0f, 1.0f, 1.0f, 0.5f, 0.5f,
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f
    };
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof (vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);
    initializeTexture("../src/image/container.jpg");
    glEnable(GL_DEPTH_TEST);
}

void Box::draw(glm::mat4 &viewProjectionMatrix){
    drawPlane(180, glm::vec3(1,0,0),viewProjectionMatrix);//前
    drawPlane(0, glm::vec3(1,0,0),viewProjectionMatrix);//后
    drawPlane(90,glm::vec3(1,0,0), viewProjectionMatrix);//上
    drawPlane(-90,glm::vec3(1,0,0), viewProjectionMatrix);//下
    drawPlane(90,glm::vec3(0,1,0), viewProjectionMatrix);//左
    drawPlane(-90,glm::vec3(0,1,0), viewProjectionMatrix);//右
}

void Box::drawPlane(float a, glm::vec3 axis, glm::mat4& viewProjectionMatrix){
    glm::mat4 modelMatrix(1.0);
//    modelMatrix = glm::translate(modelMatrix,translate);
    modelMatrix = glm::rotate(modelMatrix, float(glm::radians(a)), axis);
    glm::mat4 modelViewProjectionMatrix = viewProjectionMatrix * modelMatrix;
    glUniformMatrix4fv(glGetUniformLocation(*ID, "u_Matrix"), 1, false, glm::value_ptr(modelViewProjectionMatrix));
    glBindTexture(GL_TEXTURE_2D, texture);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 6);
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Box::initializeTexture(const char *path){
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
        glUniform1i(glGetUniformLocation(*ID,"ourTexture"), 0);
    }else {
        qDebug()<<"Failed to load texture";
    }
    stbi_image_free(data);
}
