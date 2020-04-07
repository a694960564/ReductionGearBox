#ifndef MODEL_H
#define MODEL_H
#include "object/Object.h"

class Model : protected Object
{
public:
    Model(const unsigned int& id,const GLchar*, const glm::vec3& color);
    ~Model();
    void initialize(const glm::mat4& modelMatrix);
    void draw(const glm::mat4&);
    void rotate(float degree,const glm::vec3&);
    void translate(const glm::vec3&);
private:
    void readSTL(const GLchar*,float*&, float*&);
    int numofvertex;
    //数组最大值最小值
    float m_fmaxmin[6];
    const char* path;
    glm::mat4 modelMatrix;
    glm::vec3 color;
    unsigned int VBO[2];
    float* verts,* vnorms;
};

#endif // MODEL_H
