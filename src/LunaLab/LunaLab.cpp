#include <Common/Common.h>
#include <Editor/Glfw.h>
#include <Editor/GView.h>
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
    if (!Glfw::Get()->Init(1920ui64, 1080ui64, "LunaLab"))
        return 1;

    // =================================================
    // GS

    _GS<std::vector<KTKR::Ptr<Shader>>>::getInstance()->Register(RES_SHADER, {});
    // =================================================

    Editor::UIManager::Get()->InitDemo();
    auto renderer = Editor::SceneRenderer::Create(Editor::GView::Get()->scene);

#ifdef _DEBUG
    // Demo::PLYRenderer::Get()->Init();
#endif

    auto preFrameProc = []() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    };

    auto renderFrame = [&]() {

#ifdef _DEBUG
        // Scene
        // Demo::PLYRenderer::Get()->Update();
#endif
        renderer->Update();
        // GUI
        Editor::UIManager::Get()->RunDemo();

        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    };

    auto postFrameProc = []() {

    };

    OpQueue operations;
    operations << preFrameProc << renderFrame << postFrameProc;
    Glfw::Get()->Run(&operations);
    return 0;
}