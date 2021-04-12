#pragma once
#include <Common/Common.h>
#include <Core/OpenGL/Common.h>
#include <Core/OpenGL/Camera.h>
#include <Core/OpenGL/VAO.h>
#include <Core/OpenGL/Shader.h>
#include <Core/OpenGL/Texture.h>
#include "./Scene.h"
#include <vector>
#include <fstream>
namespace LUNA
{

    class SceneRenderer
    {
    public:
        // KTKR::Ptr<Scene> scene;
    };
    namespace Demo
    {

        class CubeMapRenderer : public KTKR::Singleton<CubeMapRenderer>
        {
        protected:
            Camera *camera;
            VAO *cubeVAO;
            VAO *pointVAO;
            Shader *cubeShader;
            Shader *pointShader;
            bool enableFPS;

        public:
            void Init()
            {
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
                pointVAO = new VAO{&(pointsXYZ[0]), pointsXYZ.size() * sizeof(float), {3,3}};
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
                glPointSize(5);
            }
            void Update()
            {

                processCameraInput(Glfw::getInstance()->getWindow(), camera,
                                   Glfw::getInstance()->deltaTime);
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

            void processCameraInput(GLFWwindow *window, Camera *camera, float deltaTime)
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
        };
    } // namespace LUNA::Demo
} // namespace LUNA