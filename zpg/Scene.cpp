#include "Scene.h"

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


    // Ground height
    const float groundY = -0.65f;

    // Create ground using two triangles
    const float ground[] =
    {
        -7.5f, groundY,   3.5f,  0.1f, 0.4f, 0.1f,
         7.5f, groundY,   3.5f,  0.1f, 0.4f, 0.1f,
         7.5f, groundY, -16.0f,  0.1f, 0.4f, 0.1f,

        -7.5f, groundY,   3.5f,  0.1f, 0.4f, 0.1f,
         7.5f, groundY, -16.0f,  0.1f, 0.4f, 0.1f,
        -7.5f, groundY, -16.0f,  0.1f, 0.4f, 0.1f
    };

    // Create ground model
    models.push_back(
        std::make_unique<Model>(
            ground,
            sizeof(ground),
            6
        )
    );

    Model* groundModel = models.back().get();

    // Add ground to the scene
    objects.push_back(
        std::make_unique<DrawableObject>(
            groundModel,
            bushShaderProgram,
            Transformation(
                0.0f,
                0.0f,
                0.0f,
                1.0f,
                0.0f
            )
        )
    );


    // Find the lowest and highest tree vertices
    float treeMinY = tree[1];
    float treeMaxY = tree[1];

    for (size_t i = 1;
        i < sizeof(tree) / sizeof(float);
        i += 6)
    {
        if (tree[i] < treeMinY)
        {
            treeMinY = tree[i];
        }

        if (tree[i] > treeMaxY)
        {
            treeMaxY = tree[i];
        }
    }

    // Find the lowest and highest bush vertices
    float bushMinY = bushes[1];
    float bushMaxY = bushes[1];

    for (size_t i = 1;
        i < sizeof(bushes) / sizeof(float);
        i += 6)
    {
        if (bushes[i] < bushMinY)
        {
            bushMinY = bushes[i];
        }

        if (bushes[i] > bushMaxY)
        {
            bushMaxY = bushes[i];
        }
    }

    float treeModelHeight = treeMaxY - treeMinY;
    float bushModelHeight = bushMaxY - bushMinY;


    // Initialize random number generator
    std::random_device rd;
    std::mt19937 generator(rd());

    // Random tree properties
    std::uniform_real_distribution<float> treeX(
        -7.0f, 7.0f
    );

    std::uniform_real_distribution<float> treeZ(
        -15.0f, -0.5f
    );
    std::uniform_real_distribution<float> treeHeight(
        1.0f, 1.6f
    );

    std::uniform_real_distribution<float> treeRotation(
        -0.8f, 0.8f
    );

    // Random bush properties
    std::uniform_real_distribution<float> bushX(
        -2.8f, 2.8f
    );

    std::uniform_real_distribution<float> bushZ(
        -6.5f, 0.0f
    );

    std::uniform_real_distribution<float> bushHeight(
        0.12f, 0.28f
    );

    std::uniform_real_distribution<float> bushRotation(
        -0.8f, 0.8f
    );

    // Store positions on the XZ ground plane
    std::vector<glm::vec2> treePositions;
    std::vector<glm::vec2> bushPositions;


    // Generate random trees
    for (int i = 0; i < 74; i++)
    {
        glm::vec2 position;
        bool validPosition = false;

        // Find a suitable position
        for (int attempt = 0; attempt < 100; attempt++)
        {
            position = glm::vec2(
                treeX(generator),
                treeZ(generator)
            );

            validPosition = true;

            // Check distance from existing trees
            for (const glm::vec2& other : treePositions)
            {
                if (glm::distance(position, other) < 0.85f)
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

        if (!validPosition)
        {
            continue;
        }

        treePositions.push_back(position);

        // Calculate scale from the desired tree height
        float height = treeHeight(generator);
        float scale = height / treeModelHeight;

        float rotation = treeRotation(generator);

        // Place the tree base on the ground
        float y = groundY - treeMinY * scale;

        // Create tree drawable object
        objects.push_back(
            std::make_unique<DrawableObject>(
                treeModel,
                treeShaderProgram,
                Transformation(
                    position.x,
                    y,
                    position.y,
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
                bushZ(generator)
            );

            validPosition = true;

            // Check distance from existing bushes
            for (const glm::vec2& other : bushPositions)
            {
                if (glm::distance(position, other) < 0.35f)
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

        if (!validPosition)
        {
            continue;
        }

        bushPositions.push_back(position);

        // Calculate scale from the desired bush height
        float height = bushHeight(generator);
        float scale = height / bushModelHeight;

        float rotation = bushRotation(generator);

        // Place the bush base on the ground
        float y = groundY - bushMinY * scale;

        // Create bush drawable object
        objects.push_back(
            std::make_unique<DrawableObject>(
                bushModel,
                bushShaderProgram,
                Transformation(
                    position.x,
                    y,
                    position.y,
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


    if (sceneNumber == 3)
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

void Scene::draw(
    const Camera& camera,
    const Camera& overlayCamera)
{
    if (sceneNumber == 3 && !objects.empty())
    {
        // Draw the forest using the movable camera
        for (size_t i = 0; i + 1 < objects.size(); i++)
        {
            objects[i]->draw(camera);
        }

        // Draw the login using the static camera
        glDisable(GL_DEPTH_TEST);

        objects.back()->draw(overlayCamera);

        glEnable(GL_DEPTH_TEST);

        return;
    }

    // Draw all objects in other scenes normally
    for (const auto& object : objects)
    {
        object->draw(camera);
    }
}