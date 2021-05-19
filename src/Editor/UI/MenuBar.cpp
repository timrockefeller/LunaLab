#include <Editor/UI/Layout/MenuBar.h>

using namespace LUNA::Editor;
using namespace KTKR;
using namespace std;

bool MenuBar::Draw()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", "CTRL+Z"))
            {
            }
            if (ImGui::MenuItem("Redo", "CTRL+Y", false, false))
            {
            } // Disabled item
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", "CTRL+X"))
            {
            }
            if (ImGui::MenuItem("Copy", "CTRL+C"))
            {
            }
            if (ImGui::MenuItem("Paste", "CTRL+V"))
            {
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("View"))
        {
            ImGui::MenuItem("Heirachy", "", &UIManager::Get()->GetViewComponent<Heirachy, void>()->enabled);
            ImGui::MenuItem("Inspector", "", &UIManager::Get()->GetViewComponent<Inspector, void>()->enabled);
#ifdef _DEBUG
            ImGui::MenuItem("DemoWindow", "", &UIManager::Get()->GetViewComponent<DemoWindow, void>()->enabled);
#endif
            ImGui::EndMenu();
        }


        if (ImGui::BeginMenu("Tools"))
        {
            ImGui::MenuItem("IKMvs", "", &UIManager::Get()->GetViewComponent<KTKR_IKMvs, void>()->enabled);
            
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
    return false;
}