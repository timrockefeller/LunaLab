#include <Editor/Scene/SceneRenderer.h>
#include <Editor/Scene/AllCmpts.h>
#include <Editor/Glfw.h>
#include <Core/Runtime/GlobalStorage.h>
using namespace LUNA;
using namespace LUNA::Editor;
using namespace KTKR;
using namespace std;

void SceneRenderer::Init()
{
    enableFPS = false;
    camera = std::make_shared<Camera>(glm::vec3{5.0f, 0.0f, 0.0f}, glm::vec3{0, 1, 0});

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

    glEnable(GL_DEPTH_TEST);
}

void SceneRenderer::RenderChild(KTKR::Ptr<SceneObject> sobj)
{
    for (auto child : sobj->GetChildren())
    {
        auto c_transform = child->GetComponent<CmptTransform>();
        auto c_geometry = child->GetComponent<CmptGeometry>();

        if (c_geometry != nullptr && c_geometry->enabled)
        {
            glPointSize(static_cast<float>(c_geometry->pointSize));
            glm::mat4 model = child->GetLocalToWorldMatrix();
            // glm::mat4 model = glm::mat4(1.0f);
            glm::mat4 view = camera->GetViewMatrix();
            glm::mat4 projection = glm::perspective(
                glm::radians(camera->GetZoom()),
                (float)width / (float)height, 0.1f, 100.0f);
            c_geometry->shader->Use();
            c_geometry->shader->setMat4f("view", view);
            c_geometry->shader->setMat4f("projection", projection);
            c_geometry->shader->setMat4f("model", model);
            c_geometry->geometry->Draw();
        }
    }
}
void SceneRenderer::Update()
{
    if (scene == nullptr)
        return;
    glfwGetWindowSize(Glfw::getInstance()->getWindow(), &width, &height);

    processCameraInput(Glfw::getInstance()->getWindow(), camera,
                       Glfw::getInstance()->deltaTime);
    glPointSize(*_GS<int>::getInstance()->getPtr("pointsize"));
    glEnable(GL_DEPTH_TEST);

    RenderChild(scene->GetRoot());
}
void SceneRenderer::Close()
{
}

void SceneRenderer::processCameraInput(GLFWwindow *window, KTKR::Ptr<Camera> camera, float deltaTime)
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