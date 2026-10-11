#include "Scene.h"

#include "Models/sphere.h"
#include "Models/tree.h"
#include "Models/bushes.h"
#include "Models/login.h"
#include <random>
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
        // Create triangle vertices
        const float trianglePoints[] =
        {
             0.0f,  0.5f, 0.0f,
             1.0f,  0.0f, 0.0f,

             0.5f, -0.5f, 0.0f,
             0.0f, 1.0f, 0.0f,

            -0.5f, -0.5f, 0.0f,
             0.0f, 0.0f, 1.0f
        };

        // Create triangle model
        models.push_back(
            std::make_unique<Model>(
                trianglePoints,
                sizeof(trianglePoints),
                3
            )
        );

        model = models.back().get();

        // Create triangle drawable object
        objects.push_back(
            std::make_unique<DrawableObject>(
                model,
                shaderProgram,
                Transformation(
                    0.0f,
                    0.0f,
                    0.0f,
                    1.0f,
                    0.0f
                )
            )
        );

        // Create a composite transformation
        auto group = std::make_shared<CompositeTransformation>();
       
        
        // T * R - Translation, then rotation
        // Add translation
        group->add(
            std::make_shared<Transformation>(
                0.55f,
                0.1f,
                0.0f,
                1.0f,
                0.0f
            )
        );

        // Add rotation around the Y axis
        group->add(
            std::make_shared<Transformation>(
                0.0f,
                0.0f,
                0.0f,
                1.0f,
                1.0f
            )
        );
        /*
    // R * T - Rotation, then translation
    group->add(
    std::make_shared<Transformation>(
        0.0f, 0.0f, 0.0f, 1.0f, 1.0f
         )
    );

    group->add(
    std::make_shared<Transformation>(
        0.55f, 0.1f, 0.0f, 1.0f, 0.0f
    )
    );
    */
        // Assign composite transformation to triangle
        objects.back()->addTransformation(group);

        // Create login model
        models.push_back(
            std::make_unique<Model>(
                login,
                sizeof(login),
                loginVertexCount
            )
        );

        loginModel = models.back().get();

        // Create login drawable object
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
        // Create tree model
        models.push_back(
            std::make_unique<Model>(
                tree,
                sizeof(tree),
                static_cast<int>(
                    sizeof(tree) / (6 * sizeof(float))
                    )
            )
        );

        treeModel = models.back().get();

        // Create bush model
        models.push_back(
            std::make_unique<Model>(
                bushes,
                sizeof(bushes),
                static_cast<int>(
                    sizeof(bushes) / (6 * sizeof(float))
                    )
            )
        );

        bushModel = models.back().get();

        // Create sun model
        models.push_back(
            std::make_unique<Model>(
                sphere,
                sizeof(sphere),
                static_cast<int>(
                    sizeof(sphere) / (6 * sizeof(float))
                    )
            )
        );

        sunModel = models.back().get();


        // Initialize random number generator
        std::random_device rd;
        std::mt19937 generator(rd());

        // Random tree properties
        std::uniform_real_distribution<float> treeX(
            -0.85f, 0.85f
        );

        std::uniform_real_distribution<float> treeY(
            -0.68f, 0.25f
        );

        std::uniform_real_distribution<float> treeScale(
            0.045f, 0.065f
        );

        std::uniform_real_distribution<float> treeRotation(
            -0.8f, 0.8f
        );

        // Random bush properties
        std::uniform_real_distribution<float> bushX(
            -0.90f, 0.90f
        );

        std::uniform_real_distribution<float> bushY(
            -0.88f, -0.35f
        );

        std::uniform_real_distribution<float> bushScale(
            0.09f, 0.13f
        );

        std::uniform_real_distribution<float> bushRotation(
            -0.8f, 0.8f
        );

        // Store generated positions
        std::vector<glm::vec2> treePositions;
        std::vector<glm::vec2> bushPositions;


        // Generate random trees
        for (int i = 0; i < 12; i++)
        {
            glm::vec2 position;
            bool validPosition = false;

            // Find a suitable position
            for (int attempt = 0; attempt < 100; attempt++)
            {
                position = glm::vec2(
                    treeX(generator),
                    treeY(generator)
                );

                validPosition = true;

                // Check distance from existing trees
                for (const glm::vec2& other : treePositions)
                {
                    if (glm::distance(position, other) < 0.25f)
                    {
                        validPosition = false;
                        break;
                    }
                }

                if (validPosition)
                {
                    break;
                }
            }

            // Skip the tree if no suitable position was found
            if (!validPosition)
            {
                continue;
            }

            treePositions.push_back(position);

            float scale = treeScale(generator);
            float rotation = treeRotation(generator);

            // Create tree drawable object
            objects.push_back(
                std::make_unique<DrawableObject>(
                    treeModel,
                    treeShaderProgram,
                    Transformation(
                        position.x,
                        position.y,
                        0.0f,
                        scale,
                        rotation
                    )
                )
            );

            // Add an extra transformation to the first tree
            if (i == 0)
            {
                objects.back()->addTransformation(
                    Transformation(
                        0.0f,
                        0.0f,
                        0.0f,
                        1.15f,
                        0.3f
                    )
                );
            }
        }


        // Generate random bushes
        for (int i = 0; i < 13; i++)
        {
            glm::vec2 position;
            bool validPosition = false;

            // Find a suitable position
            for (int attempt = 0; attempt < 100; attempt++)
            {
                position = glm::vec2(
                    bushX(generator),
                    bushY(generator)
                );

                validPosition = true;

                // Check distance from existing bushes
                for (const glm::vec2& other : bushPositions)
                {
                    if (glm::distance(position, other) < 0.13f)
                    {
                        validPosition = false;
                        break;
                    }
                }

                if (validPosition)
                {
                    break;
                }
            }

            // Skip the bush if no suitable position was found
            if (!validPosition)
            {
                continue;
            }

            bushPositions.push_back(position);

            float scale = bushScale(generator);
            float rotation = bushRotation(generator);

            // Create bush drawable object
            objects.push_back(
                std::make_unique<DrawableObject>(
                    bushModel,
                    bushShaderProgram,
                    Transformation(
                        position.x,
                        position.y,
                        0.0f,
                        scale,
                        rotation
                    )
                )
            );
        }


        // Create sun
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

        // Enable dynamic sun movement
        objects.back()->setDynamicVerticalMotion(
            0.07f,
            1.3f
        );


        // Create login model
        models.push_back(
            std::make_unique<Model>(
                login,
                sizeof(login),
                loginVertexCount
            )
        );

        loginModel = models.back().get();

        // Create login drawable object
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
    float time = static_cast<float>(glfwGetTime());

    for (auto& object : objects)
    {
        object->update(time);
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