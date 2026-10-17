#pragma once

#include "DrawableObject.h"
#include "Model.h"
#include "ShaderProgram.h"
#include "Camera.h"

#include <GLFW/glfw3.h>

#include <memory>
#include <vector>

class Scene
{
private:
    int sceneNumber;

    std::vector<std::unique_ptr<Model>> models;
    std::vector<std::unique_ptr<ShaderProgram>> shaderPrograms;
    std::vector<std::unique_ptr<DrawableObject>> objects;

    ShaderProgram* shaderProgram;
    ShaderProgram* loginShaderProgram;
    ShaderProgram* treeShaderProgram;
    ShaderProgram* bushShaderProgram;
    ShaderProgram* sunShaderProgram;

    Model* model;
    Model* loginModel;
    Model* treeModel;
    Model* bushModel;
    Model* sunModel;

public:
    explicit Scene(int sceneNumber);

    void createShaders();
    void createModels();

    void update(GLFWwindow* window);
    void draw(const Camera& camera);
};