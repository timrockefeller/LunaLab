#pragma once
#include <Common/Common.h>
#include <Core/OpenGL/Common.h>
#include <Core/OpenGL/Camera.h>
#include <Core/OpenGL/VAO.h>
#include <Core/OpenGL/Obj/FmtPLY.h>
#include <Core/OpenGL/Shader.h>
#include <Core/OpenGL/Texture.h>
#include "./Scene.h"
#include <GLFW/glfw3.h>
#include <vector>
#include <fstream>
#include <iostream>
namespace LUNA
{
    namespace Editor
    {
        class SceneRenderer : public KTKR::HeapObj
        {
            int width;
            int height;
            KTKR::Ptr<Scene> scene;
            KTKR::Ptr<Camera> camera;
            void RenderChild(KTKR::Ptr<SceneObject> sobj);
            bool enableFPS;
            void processCameraInput(GLFWwindow *window, KTKR::Ptr<Camera> camera, float deltaTime);

        public:
            static KTKR::Ptr<SceneRenderer> Create(KTKR::Ptr<Scene> scene)
            {
                auto rsl = KTKR::Create<SceneRenderer>(scene);
                rsl->Init();
                return rsl;
            }
            SceneRenderer(KTKR::Ptr<Scene> scene) : scene{scene} {}
            void Init();
            void Update();
            void Close();
        };
    } // namespace LUNA::Editor
#ifdef _DEBUG
    namespace Demo
    {

        class CubeMapRenderer : public KTKR::Singleton<CubeMapRenderer>
        {
        public:
            Camera *camera;
            VAO *cubeVAO;
            VAO *pointVAO;
            Shader *cubeShader;
            Shader *pointShader;
            bool enableFPS;

            KTKR::Ptr<FmtPLY> ply, ply2;

            void Init();
            void Update();
            void processCameraInput(GLFWwindow *window, Camera *camera, float deltaTime);
        };

        class PLYRenderer : public KTKR::Singleton<PLYRenderer>
        {
        protected:
            Camera *camera;
            Shader *plyShader;
            bool enableFPS;

            KTKR::Ptr<FmtPLY> ply, ply2;

        public:
            void Init();
            void Update();
            void processCameraInput(GLFWwindow *window, Camera *camera, float deltaTime);
        };

    } // namespace LUNA::Demo
#endif
} // namespace LUNA