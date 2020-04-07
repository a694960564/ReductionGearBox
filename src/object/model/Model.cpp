#include "Model.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Model::Model(const unsigned int&id,const GLchar* path, const glm::vec3& color):
    Object(&id),
    color(color),
    path(path),
    modelMatrix(glm::mat4(1.0))
{
}
Model::~Model(){
    delete verts;
    delete vnorms;
}
void Model::initialize(const glm::mat4& modelMatrix){
    initializeOpenGLFunctions();
    this->modelMatrix = modelMatrix;
    readSTL(path, verts, vnorms);
    glGenBuffers(2, VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof (float)*3*numofvertex, verts, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof (float)*3*numofvertex, vnorms, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glEnable(GL_DEPTH_TEST);
}

void Model::rotate(float degree, const glm::vec3& vector){
    modelMatrix = glm::rotate(modelMatrix, glm::radians(degree), vector);
}

void Model::translate(const glm::vec3 & vector){
    modelMatrix = glm::translate(modelMatrix, vector);
}

void Model::draw(const glm::mat4 &viewProjectionMatrix){
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof (float)*3*numofvertex, verts, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof (float)*3*numofvertex, vnorms, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    glUniform3fv(glGetUniformLocation(*ID, "u_ObjectColor"), 1, glm::value_ptr(color));
    glUniformMatrix4fv(glGetUniformLocation(*ID, "u_model"), 1, false,glm::value_ptr(modelMatrix));
    glm::mat4 modelViewProjectionMatrix = viewProjectionMatrix * modelMatrix;
    glUniformMatrix4fv(glGetUniformLocation(*ID, "u_Matrix"), 1, false, glm::value_ptr(modelViewProjectionMatrix));
    glDrawArrays(GL_TRIANGLES, 0, numofvertex);
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Model::readSTL(const GLchar *path,float*& verts,float*& vnorms){
    int max = 0;
    bool isbegin = false;
    long size = 0;
    int nlines = 0;
    int count1 = 0;
    int count2 = 0;
    FILE* file;
    fopen_s(&file, path, "r");
    fseek(file, 0L, SEEK_END);
    size = ftell(file);
    fclose(file);
    fopen_s(&file, path, "r");
    for (int i = 0; i < size; i++)
    {
        if (getc(file) == '\n')
        {
            nlines++;
        }
    }
    unsigned int num = nlines / 7;
    numofvertex = num * 3;
    rewind(file);
    while (getc(file) != '\n');
    verts = new float[9 * num];
    vnorms = new float[9 * num];
    for (int i = 0; i < num; i++)
    {
        char x[200] = "";
        char y[200] = "";
        char z[200] = "";
        if (3 != fscanf(file, "%*s %*s %80s %80s %80s\n", x, y, z))
        {
            break;
        }
        vnorms[count1] = vnorms[count1 + 3] = vnorms[count1 + 6] = atof(x);
        count1++;
        vnorms[count1] = vnorms[count1 + 3] = vnorms[count1 + 6] = atof(y);
        count1++;
        vnorms[count1] = vnorms[count1 + 3] = vnorms[count1 + 6] = atof(z);
        count1 += 7;
        fscanf(file, "%*s %*s");
        if (3 != fscanf(file, "%*s %80s %80s %80s\n", x, y, z))
        {
            break;
        }
        if (isbegin == false)
        {
            isbegin = true;
            max = atof(z);
        }
        verts[count2] = atof(x);
        count2++;
        verts[count2] = atof(y);
        count2++;
        verts[count2] = atof(z);
        count2++;
        if (3 != fscanf(file, "%*s %80s %80s %80s\n", x, y, z))
        {
            break;
        }
        verts[count2] = atof(x);
        count2++;
        verts[count2] = atof(y);
        count2++;
        verts[count2] = atof(z);
        count2++;
        if (3 != fscanf(file, "%*s %80s %80s %80s\n", x, y, z))
        {
            break;
        }
        verts[count2] = atof(x);
        count2++;
        verts[count2] = atof(y);
        count2++;
        verts[count2] = atof(z);
        count2++;
        fscanf(file, "%*s");
        fscanf(file, "%*s");
    }

    //求数组最大值最小值
    float max1 = verts[0];
    float min1 = verts[0];
    for (int i = 0; i < 9 * num; i = i + 3)
    {
        if (max1 < verts[i]) max1 = verts[i];
        if (min1 > verts[i]) min1 = verts[i];
    }
    m_fmaxmin[0] = max1;
    m_fmaxmin[1] = min1;

    max1 = verts[1];
    min1 = verts[1];
    for (int i = 1; i < 9 * num; i = i + 3)
    {
        if (max1 < verts[i]) max1 = verts[i];
        if (min1 > verts[i]) min1 = verts[i];
    }
    m_fmaxmin[2] = max1;
    m_fmaxmin[3] = min1;

    max1 = verts[2];
    min1 = verts[2];
    for (int i = 2; i < 9 * num; i = i + 3)
    {
        if (max1 < verts[i]) max1 = verts[i];
        if (min1 > verts[i]) min1 = verts[i];
    }
    m_fmaxmin[4] = max1;
    m_fmaxmin[5] = min1;
}
