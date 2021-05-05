#include <string>
#include <imgui/imgui_stdlib.h>

#include <Core/Runtime/GlobalStorage.h>
#include <Core/OpenGL/Obj/FmtPLY.h>
#include <Core/OpenGL/Shader.h>

#include <Editor/UI/layout/KTKR_IKmvs.h>
#include <Editor/Scene/AllCmpts.h>
#include <Editor/GView.h>
using namespace std;
using namespace KTKR;
using namespace LUNA;
using namespace LUNA::Editor;

bool KTKR_IKMvs::Enter()
{
    plyshader = std::make_shared<Shader>("../assets/shader/ply.vs", "../assets/shader/ply.fs");
    _GS<std::string>::getInstance()->Register(IKMVS_PLY_LOAD_PATH, "");
    _GS<std::vector<KTKR::Ptr<Shader>>>::getInstance()->getPtr(RES_SHADER)->push_back(plyshader);
    return false;
}
bool KTKR_IKMvs::Draw()
{
    ImGui::Begin("IKMvs");
    ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
    if (ImGui::BeginTabBar("IKMvs_Tabbar", tab_bar_flags))
    {
        if (ImGui::BeginTabItem("PLY"))
        {
            ImGui::TextWrapped("Load .PLY directly to heirachy.");
            ImGui::Spacing();
            ImGui::InputTextWithHint("ply filepath", "( absolute )", _GS<std::string>::getInstance()->getPtr(IKMVS_PLY_LOAD_PATH));
            if (ImGui::Button("Load"))
            {
                auto filepath = _GS<std::string>::getInstance()->getPtr(IKMVS_PLY_LOAD_PATH);
                auto plyobj = FmtPLY::create(*filepath);
                if (plyobj != nullptr)
                {
                    // ./asset/example.ply -> example.ply
                    auto sobj = SceneObject::Create(plyobj->filePath.substr(plyobj->filePath.find_last_of("/") + 1));
                    sobj->AddComponent<CmptGeometry>(plyobj, plyshader);
                    Editor::GView::getInstance()->AddSobjToTop(sobj);
                }
            }
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Calib"))
        {
            ImGui::TextWrapped("Calibrate your camera.");
            ImGui::SameLine();
            HelpMarker("In this section you will get a .txt file contained several important parameter of your camera.");
            ImGui::Spacing();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Pipeline"))
        {
            ImGui::TextWrapped("Customable pipeline of SfM processing.");
            ImGui::Spacing();
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    ImGui::End();
    return false;
}