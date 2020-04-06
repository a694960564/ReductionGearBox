#ifndef MODEL_H
#define MODEL_H
#include "object/Object.h"

class Model : protected Object
{
public:
    Model(unsigned int& id);
    void initialize();
    void draw(glm::mat4&);
private:
    void readSTL(const GLchar*,float*&, float*&);
    int numofvertex;
    //数组最大值最小值
    float m_fmaxmin[6];
};

#endif // MODEL_H
