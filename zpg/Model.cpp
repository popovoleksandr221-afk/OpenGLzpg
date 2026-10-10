#include "Model.h"
#include <glad/gl.h>

Model::Model(
    const float* data,
    std::size_t dataSize,
    int count)
    : vao(0),
    vbo(0),
    vertexCount(count)
{
    glGenBuffers(
        1,
        &vbo
    );

    glBindBuffer(
        GL_ARRAY_BUFFER,
        vbo
    );

    glBufferData(
        GL_ARRAY_BUFFER,
        dataSize,
        data,
        GL_STATIC_DRAW
    );

    glGenVertexArrays(
        1,
        &vao
    );

    glBindVertexArray(
        vao
    );

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(1);

    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*)(3 * sizeof(float))
    );

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Model::~Model()
{
    if (vao != 0)
    {
        glDeleteVertexArrays(
            1,
            &vao
        );
    }

    if (vbo != 0)
    {
        glDeleteBuffers(
            1,
            &vbo
        );
    }
}

void Model::draw() const
{
    glBindVertexArray(vao);

    glDrawArrays(
        GL_TRIANGLES,
        0,
        vertexCount
    );
}

unsigned int Model::getVao() const
{
    return vao;
}

int Model::getVertexCount() const
{
    return vertexCount;
}