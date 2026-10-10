#include "Scene.h"

#include "Models/sphere.h"
#include "Models/tree.h"
#include "Models/bushes.h"
#include "Models/login.h"

Scene::Scene(int sceneNumberValue)
    : sceneNumber(sceneNumberValue),
    shaderProgram(nullptr),
    loginShaderProgram(nullptr),
    treeShaderProgram(nullptr),
    bushShaderProgram(nullptr),
    sunShaderProgram(nullptr),
    model(nullptr),
    loginModel(nullptr),
    treeModel(nullptr),
    bushModel(nullptr),
    sunModel(nullptr)
{
}

void Scene::createShaders()
{
    if (sceneNumber == 1)
    {
        shaderPrograms.push_back(
            std::make_unique<ShaderProgram>(
                "shaders/common.vert",
                "shaders/triangle.frag"
            )
        );

        shaderProgram =
            shaderPrograms.back().get();

        shaderPrograms.push_back(
            std::make_unique<ShaderProgram>(
                "shaders/common.vert",
                "shaders/login.frag"
            )
        );

        loginShaderProgram =
            shaderPrograms.back().get();
    }
    else if (sceneNumber == 2)
    {
        shaderPrograms.push_back(
            std::make_unique<ShaderProgram>(
                "shaders/common.vert",
                "shaders/sphere.frag"
            )
        );

        shaderProgram =
            shaderPrograms.back().get();

        shaderPrograms.push_back(
            std::make_unique<ShaderProgram>(
                "shaders/common.vert",
                "shaders/login.frag"
            )
        );

        loginShaderProgram =
            shaderPrograms.back().get();
    }
    else if (sceneNumber == 3)
    {
        shaderPrograms.push_back(
            std::make_unique<ShaderProgram>(
                "shaders/common.vert",
                "shaders/tree.frag"
            )
        );

        treeShaderProgram =
            shaderPrograms.back().get();

        shaderPrograms.push_back(
            std::make_unique<ShaderProgram>(
                "shaders/common.vert",
                "shaders/bush.frag"
            )
        );

        bushShaderProgram =
            shaderPrograms.back().get();

        shaderPrograms.push_back(
            std::make_unique<ShaderProgram>(
                "shaders/common.vert",
                "shaders/sun.frag"
            )
        );

        sunShaderProgram =
            shaderPrograms.back().get();

        shaderPrograms.push_back(
            std::make_unique<ShaderProgram>(
                "shaders/common.vert",
                "shaders/login.frag"
            )
        );

        loginShaderProgram =
            shaderPrograms.back().get();
    }
    else if (sceneNumber == 4)
    {
        shaderPrograms.push_back(
            std::make_unique<ShaderProgram>(
                "shaders/common.vert",
                "shaders/login.frag"
            )
        );

        shaderProgram =
            shaderPrograms.back().get();
    }
}

void Scene::createModels()
{
    if (sceneNumber == 1)
    {
        const float trianglePoints[] =
        {
             0.0f,  0.5f, 0.0f,
             1.0f,  0.0f, 0.0f,

             0.5f, -0.5f, 0.0f,
             0.0f, 1.0f, 0.0f,

            -0.5f, -0.5f, 0.0f,
             0.0f, 0.0f, 1.0f
        };

        models.push_back(
            std::make_unique<Model>(
                trianglePoints,
                sizeof(trianglePoints),
                3
            )
        );

        model =
            models.back().get();

        objects.push_back(
            std::make_unique<DrawableObject>(
                model,
                shaderProgram,
                Transformation(
                    0.0f,
                    0.05f,
                    0.0f,
                    0.7f,
                    0.0f
                )
            )
        );

        models.push_back(
            std::make_unique<Model>(
                login,
                sizeof(login),
                loginVertexCount
            )
        );

        loginModel =
            models.back().get();

        objects.push_back(
            std::make_unique<DrawableObject>(
                loginModel,
                loginShaderProgram,
                Transformation(
                    0.0f,
                    -0.85f,
                    0.0f,
                    0.10f,
                    0.0f
                )
            )
        );
    }
    else if (sceneNumber == 2)
    {
        models.push_back(
            std::make_unique<Model>(
                sphere,
                sizeof(sphere),
                static_cast<int>(
                    sizeof(sphere) /
                    (6 * sizeof(float))
                    )
            )
        );

        model =
            models.back().get();

        objects.push_back(
            std::make_unique<DrawableObject>(
                model,
                shaderProgram,
                Transformation(
                    0.0f,
                    0.05f,
                    0.0f,
                    0.5f,
                    0.0f
                )
            )
        );

        models.push_back(
            std::make_unique<Model>(
                login,
                sizeof(login),
                loginVertexCount
            )
        );

        loginModel =
            models.back().get();

        objects.push_back(
            std::make_unique<DrawableObject>(
                loginModel,
                loginShaderProgram,
                Transformation(
                    0.0f,
                    -0.85f,
                    0.0f,
                    0.10f,
                    0.0f
                )
            )
        );
    }
    else if (sceneNumber == 3)
    {
        models.push_back(
            std::make_unique<Model>(
                tree,
                sizeof(tree),
                static_cast<int>(
                    sizeof(tree) /
                    (6 * sizeof(float))
                    )
            )
        );

        treeModel =
            models.back().get();

        models.push_back(
            std::make_unique<Model>(
                bushes,
                sizeof(bushes),
                static_cast<int>(
                    sizeof(bushes) /
                    (6 * sizeof(float))
                    )
            )
        );

        bushModel =
            models.back().get();

        models.push_back(
            std::make_unique<Model>(
                sphere,
                sizeof(sphere),
                static_cast<int>(
                    sizeof(sphere) /
                    (6 * sizeof(float))
                    )
            )
        );

        sunModel =
            models.back().get();

        objects.push_back(
            std::make_unique<DrawableObject>(
                treeModel,
                treeShaderProgram,
                Transformation(
                    -0.88f,
                    -0.65f,
                    0.0f,
                    0.055f,
                    -0.2f
                )
            )
        );
        objects.back()->setTransformation(
            Transformation(
                -0.88f,
                -0.65f,
                0.0f,
                0.055f,
                -0.2f
            )
        );

        objects.back()->addTransformation(
            Transformation(
                0.0f,
                0.0f,
                0.0f,
                1.5f,
                0.8f
            )
        );
        objects.push_back(
            std::make_unique<DrawableObject>(
                treeModel,
                treeShaderProgram,
                Transformation(
                    -0.58f,
                    -0.40f,
                    0.0f,
                    0.065f,
                    0.1f
                )
            )
        );

        objects.push_back(
            std::make_unique<DrawableObject>(
                treeModel,
                treeShaderProgram,
                Transformation(
                    -0.30f,
                    -0.68f,
                    0.0f,
                    0.050f,
                    -0.15f
                )
            )
        );

        objects.push_back(
            std::make_unique<DrawableObject>(
                treeModel,
                treeShaderProgram,
                Transformation(
                    -0.05f,
                    -0.43f,
                    0.0f,
                    0.060f,
                    0.2f
                )
            )
        );

        objects.push_back(
            std::make_unique<DrawableObject>(
                treeModel,
                treeShaderProgram,
                Transformation(
                    0.20f,
                    -0.67f,
                    0.0f,
                    0.055f,
                    -0.2f
                )
            )
        );

        objects.push_back(
            std::make_unique<DrawableObject>(
                treeModel,
                treeShaderProgram,
                Transformation(
                    0.43f,
                    -0.40f,
                    0.0f,
                    0.065f,
                    0.15f
                )
            )
        );

        objects.push_back(
            std::make_unique<DrawableObject>(
                treeModel,
                treeShaderProgram,
                Transformation(
                    0.68f,
                    -0.66f,
                    0.0f,
                    0.055f,
                    -0.1f
                )
            )
        );

        objects.push_back(
            std::make_unique<DrawableObject>(
                treeModel,
                treeShaderProgram,
                Transformation(
                    0.90f,
                    -0.43f,
                    0.0f,
                    0.050f,
                    0.2f
                )
            )
        );

        objects.push_back(
            std::make_unique<DrawableObject>(
                treeModel,
                treeShaderProgram,
                Transformation(
                    -0.72f,
                    -0.05f,
                    0.0f,
                    0.045f,
                    -0.2f
                )
            )
        );

        objects.push_back(
            std::make_unique<DrawableObject>(
                treeModel,
                treeShaderProgram,
                Transformation(
                    -0.38f,
                    0.02f,
                    0.0f,
                    0.050f,
                    0.1f
                )
            )
        );

        objects.push_back(
            std::make_unique<DrawableObject>(
                treeModel,
                treeShaderProgram,
                Transformation(
                    0.34f,
                    0.0f,
                    0.0f,
                    0.045f,
                    -0.15f
                )
            )
        );

        objects.push_back(
            std::make_unique<DrawableObject>(
                treeModel,
                treeShaderProgram,
                Transformation(
                    0.72f,
                    0.03f,
                    0.0f,
                    0.050f,
                    0.15f
                )
            )
        );

        objects.push_back(
            std::make_unique<DrawableObject>(
                bushModel,
                bushShaderProgram,
                Transformation(
                    -0.90f,
                    -0.84f,
                    0.0f,
                    0.12f,
                    0.0f
                )
            )
        );

        objects.push_back(
            std::make_unique<DrawableObject>(
                bushModel,
                bushShaderProgram,
                Transformation(
                    -0.73f,
                    -0.80f,
                    0.0f,
                    0.10f,
                    0.2f
                )
            )
        );

        objects.push_back(
            std::make_unique<DrawableObject>(
                bushModel,
                bushShaderProgram,
                Transformation(
                    -0.56f,
                    -0.85f,
                    0.0f,
                    0.13f,
                    -0.1f
                )
            )
        );

        objects.push_back(
            std::make_unique<DrawableObject>(
                bushModel,
                bushShaderProgram,
                Transformation(
                    -0.39f,
                    -0.81f,
                    0.0f,
                    0.11f,
                    0.15f
                )
            )
        );

        objects.push_back(
            std::make_unique<DrawableObject>(
                bushModel,
                bushShaderProgram,
                Transformation(
                    -0.22f,
                    -0.86f,
                    0.0f,
                    0.12f,
                    0.0f
                )
            )
        );

        objects.push_back(
            std::make_unique<DrawableObject>(
                bushModel,
                bushShaderProgram,
                Transformation(
                    -0.05f,
                    -0.82f,
                    0.0f,
                    0.11f,
                    -0.2f
                )
            )
        );

        objects.push_back(
            std::make_unique<DrawableObject>(
                bushModel,
                bushShaderProgram,
                Transformation(
                    0.12f,
                    -0.85f,
                    0.0f,
                    0.13f,
                    0.1f
                )
            )
        );

        objects.push_back(
            std::make_unique<DrawableObject>(
                bushModel,
                bushShaderProgram,
                Transformation(
                    0.30f,
                    -0.81f,
                    0.0f,
                    0.11f,
                    -0.15f
                )
            )
        );

        objects.push_back(
            std::make_unique<DrawableObject>(
                bushModel,
                bushShaderProgram,
                Transformation(
                    0.48f,
                    -0.86f,
                    0.0f,
                    0.12f,
                    0.1f
                )
            )
        );

        objects.push_back(
            std::make_unique<DrawableObject>(
                bushModel,
                bushShaderProgram,
                Transformation(
                    0.66f,
                    -0.81f,
                    0.0f,
                    0.11f,
                    0.2f
                )
            )
        );

        objects.push_back(
            std::make_unique<DrawableObject>(
                bushModel,
                bushShaderProgram,
                Transformation(
                    0.83f,
                    -0.85f,
                    0.0f,
                    0.12f,
                    -0.1f
                )
            )
        );

        objects.push_back(
            std::make_unique<DrawableObject>(
                bushModel,
                bushShaderProgram,
                Transformation(
                    -0.62f,
                    -0.60f,
                    0.0f,
                    0.09f,
                    0.1f
                )
            )
        );

        objects.push_back(
            std::make_unique<DrawableObject>(
                bushModel,
                bushShaderProgram,
                Transformation(
                    0.60f,
                    -0.58f,
                    0.0f,
                    0.09f,
                    -0.1f
                )
            )
        );

        objects.push_back(
            std::make_unique<DrawableObject>(
                sunModel,
                sunShaderProgram,
                Transformation(
                    0.78f,
                    0.72f,
                    0.0f,
                    0.16f,
                    0.0f
                )
            )
        );

        models.push_back(
            std::make_unique<Model>(
                login,
                sizeof(login),
                loginVertexCount
            )
        );

        loginModel =
            models.back().get();

        objects.push_back(
            std::make_unique<DrawableObject>(
                loginModel,
                loginShaderProgram,
                Transformation(
                    0.0f,
                    -0.94f,
                    0.0f,
                    0.06f,
                    0.0f
                )
            )
        );
    }
    else if (sceneNumber == 4)
    {
        models.push_back(
            std::make_unique<Model>(
                login,
                sizeof(login),
                loginVertexCount
            )
        );

        loginModel =
            models.back().get();

        objects.push_back(
            std::make_unique<DrawableObject>(
                loginModel,
                shaderProgram,
                Transformation(
                    0.0f,
                    0.0f,
                    0.0f,
                    0.3f,
                    0.0f
                )
            )
        );
    }
}

void Scene::update(GLFWwindow* window)
{
    if (objects.empty())
    {
        return;
    }

    DrawableObject* object =
        objects[0].get();

    const float moveSpeed = 0.000825f;
    const float rotationSpeed = 0.0025f;
    const float scaleSpeed = 0.00005f;

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        object->translate(
            -moveSpeed,
            0.0f,
            0.0f
        );
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        object->translate(
            moveSpeed,
            0.0f,
            0.0f
        );
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        object->translate(
            0.0f,
            moveSpeed,
            0.0f
        );
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        object->translate(
            0.0f,
            -moveSpeed,
            0.0f
        );
    }

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        object->rotateY(
            rotationSpeed
        );
    }

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        object->rotateY(
            -rotationSpeed
        );
    }

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        object->changeScale(
            scaleSpeed
        );
    }

    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    {
        object->changeScale(
            -scaleSpeed
        );
    }
}

void Scene::draw()
{
    for (const auto& object : objects)
    {
        object->draw();
    }
}