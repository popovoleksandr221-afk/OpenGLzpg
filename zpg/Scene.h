#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <vector>

#include "DrawableObject.h"
#include "Model.h"
#include "ShaderProgram.h"
#include "Camera.h"

class Scene
{
private:
    int sceneNumber;
    Camera solarCamera;
    int solarWidth = 0;
    int solarHeight = 0;
    std::vector<std::unique_ptr<Model>> models;
    std::vector<std::unique_ptr<ShaderProgram>> shaderPrograms;
    std::vector<std::unique_ptr<DrawableObject>> objects;

    ShaderProgram* shaderProgram;
    ShaderProgram* loginShaderProgram;
    ShaderProgram* treeShaderProgram;
    ShaderProgram* bushShaderProgram;
    ShaderProgram* sunShaderProgram;
    ShaderProgram* clockShaderProgram;
    ShaderProgram* rocketShaderProgram;
    ShaderProgram* lightingPrograms[4] = {};

    Model* model;
    Model* loginModel;
    Model* treeModel;
    Model* bushModel;
    Model* sunModel;
    Model* clockModelObject;

public:
    explicit Scene(int sceneNumber);

    void createShaders();
    void createModels();
    void update(GLFWwindow* window);
    void observeCameras(Camera& camera, Camera& forestCamera);
    void draw();
};
