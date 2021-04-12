#pragma once
#include <Common/Common.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>
#include <string>
namespace LUNA
{
    class Glfw : public KTKR::Singleton<Glfw>
    {
    public:
        //static Glfw* getInstance();
        bool Init(size_t width = 800, size_t height = 600, const std::string &title = "Title");

        void Run(KTKR::OpQueue *opList);
        void Run(KTKR::Ptr<KTKR::OpQueue> &opList);
        void CloseWindow();
        void Terminate();
        GLFWwindow *getWindow();
        void RunDemo();
        float deltaTime;

        std::function<void()> _startOp;
        std::function<void()> _endOp;
        Glfw() = default;
        ~Glfw() = default;

    private:
        float lastTime;
        // static Glfw* instance;
        GLFWwindow *window;
        static void updateViewport(GLFWwindow *window, int width, int height);
    };
} // namespace LUNA
