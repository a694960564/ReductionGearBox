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
    float centerStep = 0.6f, globalStep = 0.1f,
    planetStep = 0.15f;
    float globalSum = 0.0, planetSum = 0.0;
    const float a = 58.47f, b = 33.75f, c = 67.5f;
};

#endif // GEARBOX_H
