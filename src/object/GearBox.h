#ifndef GEARBOX_H
#define GEARBOX_H
#include "model/Model.h"
#include "Object.h"

class GearBox : protected Object
{
public:
    explicit GearBox(const unsigned int& id);
    void initialize(const glm::mat4&);
    void draw(const glm::mat4&);
    glm::vec3 viewPos;
private:
    Model* centerGear;
    Model* planetGear;
};

#endif // GEARBOX_H
