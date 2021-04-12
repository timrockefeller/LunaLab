#include <Common/Common.h>
#include <Editor/Glfw.h>
#include <Editor/UI/UIManager.h>
#include <Editor/Scene/SceneRenderer.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
using namespace KTKR;
using namespace LUNA;
using namespace std;

int main()
{
    if (!Glfw::getInstance()->Init(1920ui64, 1080ui64, "LunaLab"))
        return 1;

    Editor::UIManager::getInstance()->InitDemo();

    Demo::CubeMapRenderer::getInstance()->Init();

    auto preFrameProc = []() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    };

    auto renderFrame = []() {
        // Scene

        Demo::CubeMapRenderer::getInstance()->Update();

        // GUI
        Editor::UIManager::getInstance()->RunDemo();
        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    };

    auto postFrameProc = []() {

    };

    OpQueue operations;
    operations << preFrameProc << renderFrame << postFrameProc;
    Glfw::getInstance()->Run(&operations);
    return 0;
}