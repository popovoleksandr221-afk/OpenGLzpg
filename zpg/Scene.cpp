#include "Scene.h"

#include "Models/clock.h"

#include <ctime>
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>

#include "Models/sphere.h"
#include "Models/tree.h"
#include "Models/bushes.h"
#include "Models/login.h"
#include <random>
#include "TimeRotation.h"
#include "CompositeTransformation.h"
#include "Models/sunVertices.h"
#include "Models/earthVertices.h"
#include "Models/moonVertices.h"

// Update the three hands without separating the clock geometry.
static void setClockAngles(ShaderProgram* program)
{
    const std::time_t now = std::time(nullptr);
    std::tm localTime{};
#ifdef _WIN32
    localtime_s(&localTime, &now);
#else
    localtime_r(&now, &localTime);
#endif

    const float seconds = static_cast<float>(localTime.tm_sec);
    const float minutes = static_cast<float>(localTime.tm_min) + seconds / 60.0f;
    const float hours = static_cast<float>(localTime.tm_hour % 12) + minutes / 60.0f;
    const float fullCircle = 6.28318530718f;

    program->use();
    program->setUniform("secondAngle", fullCircle * seconds / 60.0f);
    program->setUniform("minuteAngle", fullCircle * minutes / 60.0f);
    program->setUniform("hourAngle", fullCircle * hours / 12.0f);
}

Scene::Scene(int sceneNumberValue)
    : sceneNumber(sceneNumberValue),
    shaderProgram(nullptr),
    loginShaderProgram(nullptr),
    treeShaderProgram(nullptr),
    bushShaderProgram(nullptr),
    sunShaderProgram(nullptr),
    clockShaderProgram(nullptr),
    model(nullptr),
    loginModel(nullptr),
    treeModel(nullptr),
    bushModel(nullptr),
    sunModel(nullptr),
    clockModelObject(nullptr)
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
        // Shader program for Sun, Earth and Moon
        shaderPrograms.push_back(
            std::make_unique<ShaderProgram>(
                "shaders/common.vert",
                "shaders/planet.frag"
            )
        );

        shaderProgram = shaderPrograms.back().get();

        // Shader program for login
        shaderPrograms.push_back(
            std::make_unique<ShaderProgram>(
                "shaders/common.vert",
                "shaders/login.frag"
            )
        );

        loginShaderProgram = shaderPrograms.back().get();
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

        // One shader program controls both forest clocks.
        shaderPrograms.push_back(
            std::make_unique<ShaderProgram>(
                "shaders/clock.vert", "shaders/clock.frag"
            )
        );
        clockShaderProgram = shaderPrograms.back().get();

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
    else if (sceneNumber == 5)
    {
        shaderPrograms.push_back(
            std::make_unique<ShaderProgram>(
                "shaders/clock.vert", "shaders/clock.frag"
            )
        );
        clockShaderProgram = shaderPrograms.back().get();

        shaderPrograms.push_back(
            std::make_unique<ShaderProgram>(
                "shaders/common.vert", "shaders/login.frag"
            )
        );
        loginShaderProgram = shaderPrograms.back().get();
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
        // Create Sun model
        models.push_back(
            std::make_unique<Model>(
                sunVertices,
                sizeof(sunVertices),
                sunVerticesVertexCount
            )
        );

        Model* sun = models.back().get();

        // Create Earth model
        models.push_back(
            std::make_unique<Model>(
                earthVertices,
                sizeof(earthVertices),
                earthVerticesVertexCount
            )
        );

        Model* earth = models.back().get();

        // Create Moon model
        models.push_back(
            std::make_unique<Model>(
                moonVertices,
                sizeof(moonVertices),
                moonVerticesVertexCount
            )
        );

        Model* moon = models.back().get();

        // Create Sun
        objects.push_back(
            std::make_unique<DrawableObject>(
                sun,
                shaderProgram,
                Transformation(
                    0.0f, 0.0f, 0.0f,
                    0.22f, 0.0f
                )
            )
        );

        // Sun rotates around its own axis
        objects.back()->addTransformation(
            std::make_shared<TimeRotation>(
                glm::vec3(0.0f, 1.0f, 0.0f),
                0.3f
            )
        );

        // Create Earth's orbit around the Sun
        auto earthOrbit =
            std::make_shared<CompositeTransformation>();

        // Orbital rotation in the XY plane
        earthOrbit->add(
            std::make_shared<TimeRotation>(
                glm::vec3(0.0f, 0.0f, 1.0f),
                0.45f
            )
        );

        // Distance from Sun to Earth
        earthOrbit->add(
            std::make_shared<Transformation>(
                0.68f, 0.0f, 0.0f,
                1.0f, 0.0f
            )
        );

        // Create Earth
        objects.push_back(
            std::make_unique<DrawableObject>(
                earth,
                shaderProgram,
                Transformation(
                    0.0f, 0.0f, 0.0f,
                    1.0f, 0.0f
                )
            )
        );

        // Apply Earth's orbit
        objects.back()->addTransformation(earthOrbit);

        // Earth size
        objects.back()->addTransformation(
            Transformation(
                0.0f, 0.0f, 0.0f,
                0.11f, 0.0f
            )
        );

        // Create Moon
        objects.push_back(
            std::make_unique<DrawableObject>(
                moon,
                shaderProgram,
                Transformation(
                    0.0f, 0.0f, 0.0f,
                    1.0f, 0.0f
                )
            )
        );

        // Moon follows Earth around the Sun
        objects.back()->addTransformation(earthOrbit);

        // Moon revolves around Earth
        objects.back()->addTransformation(
            std::make_shared<TimeRotation>(
                glm::vec3(0.0f, 0.0f, 1.0f),
                0.8f
            )
        );

        // Distance from Earth to Moon
        objects.back()->addTransformation(
            Transformation(
                0.25f, 0.0f, 0.0f,
                1.0f, 0.0f
            )
        );

        // Moon size
        objects.back()->addTransformation(
            Transformation(
                0.0f, 0.0f, 0.0f,
                0.045f, 0.0f
            )
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
                    0.0f, -0.85f, 0.0f,
                    0.10f, 0.0f
                )
            )
        );
    }

    else if (sceneNumber == 3)
    {
        // Tree model: position (xyz) + normal (xyz)
        models.push_back(std::make_unique<Model>(
            tree, sizeof(tree), static_cast<int>(sizeof(tree) / (6 * sizeof(float)))
        ));
        treeModel = models.back().get();

        models.push_back(std::make_unique<Model>(
            bushes, sizeof(bushes), static_cast<int>(sizeof(bushes) / (6 * sizeof(float)))
        ));
        bushModel = models.back().get();

        models.push_back(std::make_unique<Model>(
            sphere, sizeof(sphere), static_cast<int>(sizeof(sphere) / (6 * sizeof(float)))
        ));
        sunModel = models.back().get();

        // Reuse one clock VAO/VBO for both positions in the forest.
        models.push_back(std::make_unique<Model>(
            clockModel, sizeof(clockModel), static_cast<int>(vertexCount), 9
        ));
        clockModelObject = models.back().get();

        // Large ground on the XZ plane
        const float groundY = -0.65f;

        // Each clock is 2 units tall in the original model.
        // Uniform scaling keeps the clock perfectly round.
        const float forestClockScale = 0.65f;
        const glm::vec2 clockPositions[] = {
            glm::vec2(-1.8f, -2.7f),
            glm::vec2(2.5f, -7.0f)
        };

        const float ground[] = {
            -7.5f, groundY,   3.5f, 0.1f, 0.4f, 0.1f,
             7.5f, groundY,   3.5f, 0.1f, 0.4f, 0.1f,
             7.5f, groundY, -16.0f, 0.1f, 0.4f, 0.1f,
            -7.5f, groundY,   3.5f, 0.1f, 0.4f, 0.1f,
             7.5f, groundY, -16.0f, 0.1f, 0.4f, 0.1f,
            -7.5f, groundY, -16.0f, 0.1f, 0.4f, 0.1f
        };

        models.push_back(std::make_unique<Model>(ground, sizeof(ground), 6));
        Model* groundModel = models.back().get();
        objects.push_back(std::make_unique<DrawableObject>(
            groundModel, bushShaderProgram,
            Transformation(0.0f, 0.0f, 0.0f, 1.0f, 0.0f)
        ));

        float treeMinY = tree[1];
        float treeMaxY = tree[1];
        for (size_t i = 1; i < sizeof(tree) / sizeof(float); i += 6)
        {
            treeMinY = std::min(treeMinY, tree[i]);
            treeMaxY = std::max(treeMaxY, tree[i]);
        }
        float bushMinY = bushes[1];
        float bushMaxY = bushes[1];
        for (size_t i = 1; i < sizeof(bushes) / sizeof(float); i += 6)
        {
            bushMinY = std::min(bushMinY, bushes[i]);
            bushMaxY = std::max(bushMaxY, bushes[i]);
        }
        float treeModelHeight = treeMaxY - treeMinY;
        float bushModelHeight = bushMaxY - bushMinY;

        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_real_distribution<float> treeX(-7.0f, 7.0f);
        std::uniform_real_distribution<float> treeZ(-15.0f, -0.5f);
        std::uniform_real_distribution<float> treeHeight(1.0f, 1.6f);
        std::uniform_real_distribution<float> treeRotation(-0.8f, 0.8f);
        // Random bush properties
        std::uniform_real_distribution<float> bushX(-6.7f, 6.7f);
        std::uniform_real_distribution<float> bushZ(-14.5f, 1.0f);
        std::uniform_real_distribution<float> bushHeight(0.25f, 0.45f);
        std::uniform_real_distribution<float> bushRotation(-0.8f, 0.8f);
        std::vector<glm::vec2> treePositions;
        std::vector<glm::vec2> bushPositions;

        // Create 74 trees; keep minimum center distance of 0.85
        for (int i = 0; i < 74; ++i)
        {
            glm::vec2 position;
            bool validPosition = false;
            for (int attempt = 0; attempt < 5000; ++attempt)
            {
                position = glm::vec2(treeX(generator), treeZ(generator));
                validPosition = true;
                for (const glm::vec2& other : treePositions)
                {
                    if (glm::distance(position, other) < 0.85f)
                    {
                        validPosition = false;
                        break;
                    }
                }
                // Reserve open space around the clocks.
                if (validPosition)
                {
                    for (const glm::vec2& clockPosition : clockPositions)
                    {
                        if (glm::distance(position, clockPosition) < 1.4f)
                        {
                            validPosition = false;
                            break;
                        }
                    }
                }

                if (validPosition) break;
            }
            if (!validPosition) continue;
            treePositions.push_back(position);

            float scale = treeHeight(generator) / treeModelHeight;
            float y = groundY - treeMinY * scale;
            float rotation = treeRotation(generator);
            objects.push_back(std::make_unique<DrawableObject>(
                treeModel, treeShaderProgram,
                Transformation(position.x, y, position.y, scale, rotation)
            ));

            if (i == 0)
            {
                objects.back()->addTransformation(
                    Transformation(0.0f, 0.0f, 0.0f, 1.15f, 0.3f)
                );
            }
        }

        // Generate up to 35 bushes
        for (int i = 0; i < 35; i++)
        {
            glm::vec2 position;
            bool validPosition = false;

            // Find a free position for the bush
            for (int attempt = 0; attempt < 1000; attempt++)
            {
                position = glm::vec2(bushX(generator), bushZ(generator));
                validPosition = true;

                // Keep bushes away from other bushes
                for (const glm::vec2& other : bushPositions)
                {
                    if (glm::distance(position, other) < 0.65f)
                    {
                        validPosition = false;
                        break;
                    }
                }

                // Keep bushes away from tree trunks
                if (validPosition)
                {
                    for (const glm::vec2& treePosition : treePositions)
                    {
                        if (glm::distance(position, treePosition) < 0.70f)
                        {
                            validPosition = false;
                            break;
                        }
                    }
                }

                // Keep bushes away from both clocks
                if (validPosition)
                {
                    for (const glm::vec2& clockPosition : clockPositions)
                    {
                        if (glm::distance(position, clockPosition) < 1.0f)
                        {
                            validPosition = false;
                            break;
                        }
                    }
                }

                if (validPosition)
                {
                    break;
                }
            }

            if (!validPosition)
            {
                continue;
            }

            bushPositions.push_back(position);

            const float height = bushHeight(generator);
            const float scale = height / bushModelHeight;
            const float rotation = bushRotation(generator);
            const float y = groundY - bushMinY * scale;

            objects.push_back(
                std::make_unique<DrawableObject>(
                    bushModel,
                    bushShaderProgram,
                    Transformation(position.x, y, position.y, scale, rotation)
                )
            );
        }

        // Sun
        objects.push_back(std::make_unique<DrawableObject>(
            sunModel, sunShaderProgram,
            Transformation(0.78f, 0.72f, 0.0f, 0.16f, 0.0f)
        ));
        objects.back()->setDynamicVerticalMotion(0.07f, 1.3f);

        // Place two clocks on the ground, facing the forest camera.
        // Transformation is T * R * S with uniform scale on every axis.
        const float faceTowardCamera = glm::radians(180.0f);
        for (const glm::vec2& clockPosition : clockPositions)
        {
            objects.push_back(std::make_unique<DrawableObject>(
                clockModelObject,
                clockShaderProgram,
                Transformation(
                    clockPosition.x,
                    groundY + forestClockScale,
                    clockPosition.y,
                    forestClockScale,
                    faceTowardCamera
                )
            ));
        }

        // The login is deliberately the last object in the forest
        models.push_back(std::make_unique<Model>(
            login, sizeof(login), loginVertexCount
        ));
        loginModel = models.back().get();
        objects.push_back(std::make_unique<DrawableObject>(
            loginModel, loginShaderProgram,
            Transformation(0.0f, -0.94f, 0.0f, 0.06f, 0.0f)
        ));
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
                Transformation(0.0f, 0.0f, 0.0f, 0.3f, 0.0f)
            )
        );
    }
    else if (sceneNumber == 5)
    {
        // One Model contains all 44826 vertices of the clock.
        // This vertex layout is: position(3), normal(3), color(3).
        models.push_back(std::make_unique<Model>(
            clockModel, sizeof(clockModel),
            static_cast<int>(vertexCount), 9
        ));
        clockModelObject = models.back().get();

        // Separate overlay, not part of the clock model draw call
        models.push_back(std::make_unique<Model>(
            login, sizeof(login), loginVertexCount
        ));
        loginModel = models.back().get();
        objects.push_back(std::make_unique<DrawableObject>(
            loginModel, loginShaderProgram,
            Transformation(0.0f, -1.08f, 0.0f, 0.06f, 0.0f)
        ));
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

    // WASD moves the camera in the forest, not the ground.
    // The clock is animated in the vertex shader, not by object movement.
    if (sceneNumber == 3 || sceneNumber == 5)
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

void Scene::draw(const Camera& camera, const Camera& overlayCamera)
{
    if (sceneNumber == 5)
    {
        clockShaderProgram->use();

        // The supplied model is viewed from its front (-Z).
        const glm::mat4 clockView = glm::lookAt(
            glm::vec3(0.0f, 0.0f, -3.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );

        clockShaderProgram->setUniform("modelMatrix", glm::mat4(1.0f));
        clockShaderProgram->setUniform("viewMatrix", clockView);
        clockShaderProgram->setUniform(
            "projectionMatrix", camera.getProjectionMatrix()
        );

        setClockAngles(clockShaderProgram);

        // Exactly one glDrawArrays call for all clock geometry.
        clockModelObject->draw();

        // The login is a separate overlay object.
        glDisable(GL_DEPTH_TEST);
        for (const auto& object : objects)
        {
            object->draw(overlayCamera);
        }
        glEnable(GL_DEPTH_TEST);
        return;
    }

    if (sceneNumber == 3 && !objects.empty())
    {
        // Set clock hand angles once before drawing the two instances.
        setClockAngles(clockShaderProgram);

        // Draw the forest with the movable camera.
        for (size_t i = 0; i + 1 < objects.size(); ++i)
        {
            objects[i]->draw(camera);
        }

        // Keep the login in place while moving the forest camera.
        glDisable(GL_DEPTH_TEST);
        objects.back()->draw(overlayCamera);
        glEnable(GL_DEPTH_TEST);
        return;
    }

    for (const auto& object : objects)
    {
        object->draw(camera);
    }
}
