#include "GearBox.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GearBox::GearBox(const unsigned int& id):
    Object(&id),
    centerGear(new Model(id, "../stl/centerGear.STL", glm::vec3(1.0, 0.0, 0.0))),
    planetGear(new Model(id, "../stl/planetGear.STL", glm::vec3(0.0, 1.0, 0.0)))
{
}

void GearBox::initialize(const glm::mat4& modelMatrix){
    initializeOpenGLFunctions();
    centerGear->initialize(modelMatrix);
    planetGear->initialize(glm::translate(modelMatrix, glm::vec3(56.57, -36.82, 0)));
}

void GearBox::draw(const glm::mat4 &viewProjectionMatrix){
    static float a = 0.0;
    glUniform3fv(glGetUniformLocation(*ID, "viewPos"), 1, glm::value_ptr(viewPos));
    glUniform3f(glGetUniformLocation(*ID, "lightPos"), 100*sin(glm::radians(a)), 0, 100*cos(glm::radians(a)));
    a++;
    centerGear->draw(viewProjectionMatrix);
    planetGear->draw(viewProjectionMatrix);
}
