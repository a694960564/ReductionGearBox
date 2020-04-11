#ifndef GEARBOX_H
#define GEARBOX_H
#include "model/Model.h"
#include "Object.h"
#include <memory>

class GearBox : protected Object
{
public:
    explicit GearBox(const unsigned int& id);
    void initialize(const glm::mat4&);
    void draw(const glm::mat4&);
    glm::vec3 viewPos;
private:
    std::unique_ptr<Model>centerGear;
    std::unique_ptr<Model>planetGear;
    std::unique_ptr<Model>bearing;
    std::unique_ptr<Model>box;
    std::unique_ptr<Model>gearRing;
};

#endif // GEARBOX_H
