#ifndef BOX_H
#define BOX_H
#include "object/Object.h"

class Box : protected Object
{
public:
    Box(unsigned int& id);
    virtual void initialize();
    virtual void draw(glm::mat4& viewProjectionMatrix);
private:
    void initializeTexture(const char*);
    void drawPlane(float a, glm::vec3 axis, glm::mat4&);
    unsigned int texture;
};

#endif // BOX_H
