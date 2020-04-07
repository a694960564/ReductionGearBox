#ifndef OBJECT_H
#define OBJECT_H
#include <QOpenGLExtraFunctions>
#include <glm/glm.hpp>
class Object : protected QOpenGLExtraFunctions{
protected:
    explicit Object(const unsigned int* id):ID(id){}
    virtual ~Object(){}
    virtual void initialize(const glm::mat4& modelMatrix) = 0;
    virtual void draw(const glm::mat4& viewProjectionMatrix) = 0;
    const unsigned int* ID;
};
#endif // OBJECT_H
