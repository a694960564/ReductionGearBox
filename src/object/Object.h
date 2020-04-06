#ifndef OBJECT_H
#define OBJECT_H
#include <QOpenGLExtraFunctions>
#include <glm/glm.hpp>
class Object : protected QOpenGLExtraFunctions{
protected:
    explicit Object(unsigned int* id):ID(id){}
    virtual ~Object(){}
    virtual void initialize() = 0;
    virtual void draw(glm::mat4&) = 0;
    unsigned int* ID;
};
#endif // OBJECT_H
