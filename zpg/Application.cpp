#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#undef GLAD_GL_IMPLEMENTATION

#include "Application.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <memory>

Application::Application()
    : window(nullptr), activeScene(0), rightMouseHeld(false),
    lastMouseX(0.0), lastMouseY(0.0)
{
    scenes.push_back(std::make_unique<Scene>(1));
    scenes.push_back(std::make_unique<Scene>(2));
    scenes.push_back(std::make_unique<Scene>(3));
    scenes.push_back(std::make_unique<Scene>(4));
    scenes.push_back(std::make_unique<Scene>(5));
}

Application::~Application()
{
    // Release OpenGL objects before destroying the context.
    scenes.clear();

    if (window != nullptr)
    {
        glfwDestroyWindow(window);
    }

    glfwTerminate();
}

void Application::error_callback(int error, const char* description)
{
    std::fprintf(stderr, "GLFW error %d: %s\n", error, description);
}

void Application::key_callback(
    GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    Application* application = static_cast<Application*>(
        glfwGetWindowUserPointer(window)
        );

    if (application == nullptr)
    {
        return;
    }

    if (action == GLFW_PRESS)
    {
        if (key == GLFW_KEY_1) application->switchScene(0);
        if (key == GLFW_KEY_2) application->switchScene(1);
        if (key == GLFW_KEY_3) application->switchScene(2);
        if (key == GLFW_KEY_4) application->switchScene(3);
        if (key == GLFW_KEY_5) application->switchScene(4);
    }

    std::printf("key_callback [%d,%d,%d,%d]\n",
        key, scancode, action, mods);
}

void Application::framebuffer_size_callback(
    GLFWwindow* window, int width, int height)
{
    std::printf("resize %d, %d\n", width, height);
    glViewport(0, 0, width, height);

    Application* application = static_cast<Application*>(
        glfwGetWindowUserPointer(window)
        );

    if (application != nullptr)
    {
        application->camera.resize(width, height);
        application->forestCamera.resize(width, height);
    }
}

void Application::initialization()
{
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
    {
        std::exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(800, 600, "ZPG", nullptr, nullptr);

    if (!window)
    {
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);
    glfwSwapInterval(1);

    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
    {
        std::cerr << "GLAD initialization failed" << std::endl;
        glfwDestroyWindow(window);
        window = nullptr;
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }

    std::printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    std::printf("Vendor: %s\n", glGetString(GL_VENDOR));
    std::printf("Renderer: %s\n", glGetString(GL_RENDERER));
    std::printf("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    int width;
    int height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    camera.resize(width, height);
    forestCamera.resize(width, height);
    glEnable(GL_DEPTH_TEST);
}

void Application::createShaders()
{
    for (const auto& scene : scenes)
    {
        scene->createShaders();
        scene->observeCameras(camera, forestCamera);
    }

}

void Application::createModels()
{
    for (const auto& scene : scenes)
    {
        scene->createModels();
    }

}

void Application::switchScene(int sceneIndex)
{
    // Four old scenes (0-3) and the clock scene (4).
    if (sceneIndex < 0 || sceneIndex > 4)
    {
        return;
    }

    activeScene = sceneIndex;
    rightMouseHeld = false;

    std::printf("Active scene: %d\n", activeScene + 1);
}

void Application::run()
{
    double previousTime = glfwGetTime();

    while (!glfwWindowShouldClose(window))
    {
        const double currentTime = glfwGetTime();
        float deltaTime = static_cast<float>(currentTime - previousTime);
        previousTime = currentTime;

        if (deltaTime > 0.1f)
        {
            deltaTime = 0.1f;
        }

        // WASD and right mouse button control only the forest camera.
        if (activeScene == 2 &&
            glfwGetWindowAttrib(window, GLFW_FOCUSED) == GLFW_TRUE)
        {
            float forward = 0.0f;
            float right = 0.0f;

            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) forward += 1.0f;
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) forward -= 1.0f;
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) right += 1.0f;
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) right -= 1.0f;

            forestCamera.move(forward, right, deltaTime);

            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
            {
                double mouseX;
                double mouseY;
                glfwGetCursorPos(window, &mouseX, &mouseY);

                if (rightMouseHeld)
                {
                    forestCamera.lookAround(
                        mouseX - lastMouseX,
                        lastMouseY - mouseY
                    );
                }

                lastMouseX = mouseX;
                lastMouseY = mouseY;
                rightMouseHeld = true;
            }
            else
            {
                rightMouseHeld = false;
            }
        }
        else
        {
            rightMouseHeld = false;
        }

        // Use the same black background in all five scenes.
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        scenes[activeScene]->update(window);
        // Scene shaders already observe the correct camera.
        scenes[activeScene]->draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
