#include "GearBox.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <QDebug>

GearBox::GearBox(const unsigned int& id):
    Object(&id),
    centerGear(new Model(id, "../stl/centerGear.STL", glm::vec3(1.0, 0.0, 0.0))),
    planetGear(new Model(id, "../stl/planetGear.STL", glm::vec3(0.0, 1.0, 0.0))),
    bearing(new Model(id, "../stl/Bearing.STL", glm::vec3(0.0, 0.0, 1.0))),
    box(new Model(id, "../stl/Box.STL", glm::vec3(0.75,0.75,0.75))),
    gearRing(new Model(id, "../stl/gearRing.STL", glm::vec3(0.5, 0.5, 0.5))),
    outPut(new Model(id, "../stl/outPut.STL", glm::vec3(0.75, 0.75, 0.75))),
    planetAxis(new Model(id, "../stl/planetAxis.STL", glm::vec3(0,1,0)))
{
    const float v = 10;//调速
    centerStep *= v;
    globalStep *= v;
    planetStep *= v;
}

void GearBox::SetValue(int v){
    centerStep =   0.6f * v;
    globalStep =   0.1f * v;
    planetStep =   0.15f * v;
}

void GearBox::initialize(const glm::mat4& modelMatrix){
    initializeOpenGLFunctions();
    centerGear->initialize(modelMatrix);
    planetGear->initialize(glm::translate(modelMatrix, glm::vec3(b, -a, 0)));
    bearing->initialize(glm::translate(modelMatrix, glm::vec3(58.47, -a, 10)));
    box->initialize(modelMatrix);
    gearRing->initialize(glm::translate(modelMatrix, glm::vec3(0.0, 0.0, 20)));
    outPut->initialize(glm::translate(modelMatrix, glm::vec3(0.0, 0.0, 56.8)));
    planetAxis->initialize(modelMatrix);
}
static glm::vec3 z = glm::vec3(0, 0, 1);
void GearBox::draw(const glm::mat4 &viewProjectionMatrix){
    static float aa = 0.0;
    glUniform3fv(glGetUniformLocation(*ID, "viewPos"), 1, glm::value_ptr(viewPos));
    glUniform3f(glGetUniformLocation(*ID, "lightPos"), 100*sin(glm::radians(aa)), 0, 100*cos(glm::radians(aa)));
    aa++;
    centerGear->rotate(centerStep, z);
    centerGear->draw(viewProjectionMatrix);

    outPut->rotate(globalStep, z);
    outPut->draw(viewProjectionMatrix);

    float x1 = c * glm::sin(glm::radians(60 + globalSum)) - a;
    float y1 = b - c * glm::cos(glm::radians(60 + globalSum));
    planetGear->IdentityTranslate(glm::vec3(a, -b, 0));//1
    planetGear->translate(glm::vec3(x1, y1, 0));
    planetGear->rotate(5-planetSum,z);
    planetGear->draw(viewProjectionMatrix);
    float x2 =  a - c * glm::sin(glm::radians(60 - globalSum));
    float y2 =  b - c * glm::cos(glm::radians(60 - globalSum));
    planetGear->IdentityTranslate(glm::vec3(-a, -b, 0));//2
    planetGear->translate(glm::vec3(x2, y2, 0));
    planetGear->rotate(5-planetSum, z);
    planetGear->draw(viewProjectionMatrix);
    float x3 =  -c * glm::sin(glm::radians(globalSum));
    float y3 =  c * glm::cos(glm::radians(globalSum)) - c;
    planetGear->IdentityTranslate(glm::vec3(0,c,0));//3
    planetGear->translate(glm::vec3(x3, y3, 0));
    planetGear->rotate(5-planetSum, z);
    planetGear->draw(viewProjectionMatrix);    

    bearing->IdentityTranslate(glm::vec3(a, -b, 10));//1
    bearing->translate(glm::vec3(x1, y1, 0));
    bearing->rotate(-planetSum, z);
    bearing->draw(viewProjectionMatrix);
    bearing->IdentityTranslate(glm::vec3(-a, -b, 10));//2
    bearing->translate(glm::vec3(x2, y2, 0));
    bearing->rotate(-planetSum, z);
    bearing->draw(viewProjectionMatrix);
    bearing->IdentityTranslate(glm::vec3(0,c,10));//3
    bearing->translate(glm::vec3(x3, y3, 0));
    bearing->rotate(-planetSum, z);
    bearing->draw(viewProjectionMatrix);

    planetAxis->IdentityTranslate(glm::vec3(a, -b, 10));//1
    planetAxis->translate(glm::vec3(x1, y1, 0));
    planetAxis->draw(viewProjectionMatrix);
    planetAxis->IdentityTranslate(glm::vec3(-a, -b, 10));//2
    planetAxis->translate(glm::vec3(x2, y2, 0));
    planetAxis->draw(viewProjectionMatrix);
    planetAxis->IdentityTranslate(glm::vec3(0,c,10));//3
    planetAxis->translate(glm::vec3(x3, y3, 0));
    planetAxis->draw(viewProjectionMatrix);

    planetSum += planetStep;
    globalSum += globalStep;

    gearRing->draw(viewProjectionMatrix);
    box->draw(viewProjectionMatrix);
}
