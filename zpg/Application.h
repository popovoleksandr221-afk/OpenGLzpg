#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <vector>

#include "Scene.h"
#include "Camera.h"

class Application
{
private:
    GLFWwindow* window;

    std::vector<std::unique_ptr<Scene>> scenes;

    int activeScene;

    Camera camera;

    static void error_callback(
        int error,
        const char* description
    );

    static void key_callback(
        GLFWwindow* window,
        int key,
        int scancode,
        int action,
        int mods
    );

    static void framebuffer_size_callback(
        GLFWwindow* window,
        int width,
        int height
    );

public:
    Application();
    ~Application();

    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    void initialization();
    void createShaders();
    void createModels();
    void run();

    void switchScene(int sceneIndex);
};