#pragma once

#include <cstddef>

class Model
{
private:
    unsigned int vao;
    unsigned int vbo;
    int vertexCount;

public:
    // 6 floats: XYZ + RGB (old models)
    // 9 floats: XYZ + normal XYZ + RGB (clock model)
    Model(const float* data, std::size_t dataSize,
        int vertexCount, int floatsPerVertex = 6);

    ~Model();
    Model(const Model&) = delete;
    Model& operator=(const Model&) = delete;

    void draw() const;
    unsigned int getVao() const;
    int getVertexCount() const;
};
