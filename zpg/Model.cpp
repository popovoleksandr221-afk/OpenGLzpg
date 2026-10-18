#include "Model.h"
#include <glad/gl.h>

Model::Model(const float* data, std::size_t dataSize,
    int count, int floatsPerVertex)
    : vao(0), vbo(0), vertexCount(count)
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);

    const GLsizei stride = static_cast<GLsizei>(floatsPerVertex * sizeof(float));

    // Attribute 0: vertex position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);

    // Attribute 1: RGB (6 floats) or RGB after normals (9 floats)
    glEnableVertexAttribArray(1);
    const int colorOffset = (floatsPerVertex == 9) ? 6 : 3;
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride,
        (void*)(static_cast<std::size_t>(colorOffset) * sizeof(float)));

    if (floatsPerVertex == 9)
    {
        // Attribute 2: model normal
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride,
            (void*)(3 * sizeof(float)));
    }

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Model::~Model()
{
    if (vao != 0) glDeleteVertexArrays(1, &vao);
    if (vbo != 0) glDeleteBuffers(1, &vbo);
}

void Model::draw() const
{
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glBindVertexArray(0);
}

unsigned int Model::getVao() const { return vao; }
int Model::getVertexCount() const { return vertexCount; }
