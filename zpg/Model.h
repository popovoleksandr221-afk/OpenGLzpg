#pragma once

#include <cstddef>

class Model
{
private:
    unsigned int vao;
    unsigned int vbo;
    int vertexCount;

public:
    Model(
        const float* data,
        std::size_t dataSize,
        int vertexCount
    );

    ~Model();

    Model(const Model&) = delete;
    Model& operator=(const Model&) = delete;

    void draw() const;

    unsigned int getVao() const;
    int getVertexCount() const;
};