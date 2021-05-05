#include <Editor/Scene/SceneRenderer.h>
#include <Core/Runtime/GlobalStorage.h>
#include <Editor/Glfw.h>
using namespace LUNA::Editor;
using namespace KTKR;
using namespace std;
#ifdef _DEBUG
void LUNA::Demo::CubeMapRenderer::Init()
{

    ply = FmtPLY::create("../assets/pointcloud/06_result_points.ply");

    ply2 = FmtPLY::create("../assets/pointcloud/06_result_sanae_2_points.ply");
    enableFPS = false;
    camera = new Camera{glm::vec3(0.0f, 0.0f, 3.0f)};
    camera->DisableFPS();

    float cubeVertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,

        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f};
    cubeVAO = new VAO{&(cubeVertices[0]), sizeof(cubeVertices), {3, 2, 3}};
    cubeVAO->SetRenderMode(GL_POINTS);

    cubeShader = new Shader{"../assets/shader/vert_fixed.vs",
                            "../assets/shader/frag_color.fs"};

    // read point cloud
    std::vector<float> pointsXYZ;
    std::ifstream fin("../assets/pointcloud/match_result.txt");
    double buff;
    while (!fin.eof())
    {
        fin >> buff;
        pointsXYZ.emplace_back(static_cast<float>(buff));
    }
    pointVAO = new VAO{&(pointsXYZ[0]), pointsXYZ.size() * sizeof(float), {3, 3}};
    pointVAO->SetRenderMode(GL_POINTS);
    pointShader = new Shader{"../assets/shader/vert_point.vs",
                             "../assets/shader/frag_point.fs"};
    KTKR::EventListener::getInstance()
        ->bind(KTKR::EventListener::Event_Type::MOUSE_SCROLL,
               [&]() {
                   if (!enableFPS)
                       return;
                   float *r =
                       _GS<float>::getInstance()->getPtr(strMouseScrollY);
                   if (r)
                       camera->ProcessMouseScroll(*r);
               })
        ->bind(
            KTKR::EventListener::Event_Type::MOUSE_MOVE,
            [&]() {
                if (!enableFPS)
                    return;
                float *xoffset =
                          _GS<float>::getInstance()->getPtr(strMousePosX),
                      *yoffset =
                          _GS<float>::getInstance()->getPtr(strMousePosY);
                if (xoffset && yoffset)
                    camera->ProcessMouseMovement(*xoffset, *yoffset);
            })
        ->bind(KTKR::EventListener::KEYBOARD_PRESS | GLFW_KEY_ESCAPE,
               [&]() { Glfw::getInstance()->CloseWindow(); })
        ->bind(KTKR::EventListener::Event_Type::MOUSE_PRESS | GLFW_MOUSE_BUTTON_RIGHT,
               [&]() { enableFPS = true; })
        ->bind(KTKR::EventListener::Event_Type::MOUSE_RELEASE | GLFW_MOUSE_BUTTON_RIGHT,
               [&]() { enableFPS = false; });

    // =================================================

    glEnable(GL_DEPTH_TEST);
}

void LUNA::Demo::CubeMapRenderer::Update()
{

    processCameraInput(Glfw::getInstance()->getWindow(), camera,
                       Glfw::getInstance()->deltaTime);
    glPointSize(*_GS<int>::getInstance()->getPtr("pointsize"));
    glEnable(GL_DEPTH_TEST);
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = camera->GetViewMatrix();
    glm::mat4 projection = glm::perspective(
        glm::radians(camera->GetZoom()),
        (float)DEFAULT_WIDTH / (float)DEFAULT_HEIGHT, 0.1f, 100.0f);

    cubeShader->Use();
    model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
    cubeShader->setMat4f("view", view);
    cubeShader->setMat4f("projection", projection);
    cubeShader->setMat4f("model", model);
    cubeShader->setVec3f("camPos", camera->GetPosition());
    cubeVAO->Draw();

    pointShader->Use();
    pointShader->setMat4f("view", view);
    pointShader->setMat4f("projection", projection);
    pointShader->setMat4f("model", model);
    pointVAO->Draw();
}

void LUNA::Demo::CubeMapRenderer::processCameraInput(GLFWwindow *window, Camera *camera, float deltaTime)
{

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        Glfw::getInstance()->CloseWindow();

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->ProcessKeyboard(CAM_FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->ProcessKeyboard(CAM_BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->ProcessKeyboard(CAM_LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->ProcessKeyboard(CAM_RIGHT, deltaTime);
}

void LUNA::Demo::PLYRenderer::Init()
{

    ply = FmtPLY::create("../assets/pointcloud/06_result_sanae_1_points.ply");
    ply2 = FmtPLY::create("../assets/pointcloud/06_result_sanae_3_points.ply");

    enableFPS = false;
    camera = new Camera{glm::vec3(0.0f, 0.0f, 3.0f)};
    camera->DisableFPS();

    plyShader = new Shader{"../assets/shader/ply.vs",
                           "../assets/shader/ply.fs"};

    KTKR::EventListener::getInstance()
        ->bind(KTKR::EventListener::Event_Type::MOUSE_SCROLL,
               [&]() {
                   if (!enableFPS)
                       return;
                   float *r =
                       _GS<float>::getInstance()->getPtr(strMouseScrollY);
                   if (r)
                       camera->ProcessMouseScroll(*r);
               })
        ->bind(
            KTKR::EventListener::Event_Type::MOUSE_MOVE,
            [&]() {
                if (!enableFPS)
                    return;
                float *xoffset =
                          _GS<float>::getInstance()->getPtr(strMousePosX),
                      *yoffset =
                          _GS<float>::getInstance()->getPtr(strMousePosY);
                if (xoffset && yoffset)
                    camera->ProcessMouseMovement(*xoffset, *yoffset);
            })
        ->bind(KTKR::EventListener::KEYBOARD_PRESS | GLFW_KEY_ESCAPE,
               [&]() { Glfw::getInstance()->CloseWindow(); })
        ->bind(KTKR::EventListener::Event_Type::MOUSE_PRESS | GLFW_MOUSE_BUTTON_RIGHT,
               [&]() { enableFPS = true; })
        ->bind(KTKR::EventListener::Event_Type::MOUSE_RELEASE | GLFW_MOUSE_BUTTON_RIGHT,
               [&]() { enableFPS = false; });

    // =================================================

    glEnable(GL_DEPTH_TEST);
}

void LUNA::Demo::PLYRenderer::Update()
{

    processCameraInput(Glfw::getInstance()->getWindow(), camera,
                       Glfw::getInstance()->deltaTime);
    glPointSize(*_GS<int>::getInstance()->getPtr("pointsize"));
    glEnable(GL_DEPTH_TEST);
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = camera->GetViewMatrix();
    glm::mat4 projection = glm::perspective(
        glm::radians(camera->GetZoom()),
        (float)DEFAULT_WIDTH / (float)DEFAULT_HEIGHT, 0.1f, 100.0f);

    plyShader->Use();
    plyShader->setMat4f("view", view);
    plyShader->setMat4f("projection", projection);
    plyShader->setMat4f("model", model);

    if (*_GS<bool>::getInstance()->getPtr("ply1"))
        ply->Draw();
    if (*_GS<bool>::getInstance()->getPtr("ply2"))
        ply2->Draw();
}

void LUNA::Demo::PLYRenderer::processCameraInput(GLFWwindow *window, Camera *camera, float deltaTime)
{

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        Glfw::getInstance()->CloseWindow();

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->ProcessKeyboard(CAM_FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->ProcessKeyboard(CAM_BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->ProcessKeyboard(CAM_LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->ProcessKeyboard(CAM_RIGHT, deltaTime);
}
#endif