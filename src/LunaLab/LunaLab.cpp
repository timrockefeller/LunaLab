#include <Common/Common.h>
#include <Editor/Glfw.h>
#include <Editor/UI/UIManager.h>
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
    
    auto preFrameProc = []() {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    };

    auto renderFrame = []() {
        Editor::UIManager::getInstance()->RunDemo();
        // Rendering
        ImGui::Render();
    };

    auto postFrameProc = []() {
        int display_w, display_h;
        glfwGetFramebufferSize(Glfw::getInstance()->getWindow(), &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        auto clear_color = _GS<ImVec4>::getInstance()->getPtr("clear_color");
        if (clear_color)
            glClearColor(clear_color->x, clear_color->y, clear_color->z, clear_color->w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(Glfw::getInstance()->getWindow());
    };

    OpQueue operations;
    operations << preFrameProc << renderFrame << postFrameProc;
    Glfw::getInstance()->Run(&operations);
    return 0;
}