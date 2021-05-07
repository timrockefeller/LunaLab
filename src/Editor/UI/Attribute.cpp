#include <Editor/UI/Attribute.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

using namespace KTKR;
using namespace LUNA;
using namespace LUNA::Editor;

void ComponentVisitor::ImplVisit(Ptr<CmptTransform> cmpt)
{
    if (ImGui::TreeNode("Transform"))
    {
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
        ImGui::Columns(2);
        ImGui::Separator();

        ImGui::AlignTextToFramePadding();
        ImGui::Text("Position");
        ImGui::NextColumn();
        ImGui::SetNextItemWidth(-1);
        ImGui::DragFloat3("##Position", (float *)cmpt->GetPositionPtr(), 0.1f, 0, 0, "%.1f");
        ImGui::NextColumn();

        ImGui::AlignTextToFramePadding();
        ImGui::Text("Rotation");
        ImGui::NextColumn();
        ImGui::SetNextItemWidth(-1);
        auto _euler = cmpt->GetRotationEuler();
        _euler = glm::degrees(_euler);
        if (ImGui::DragFloat3("##Rotation", (float *)&_euler, 0.1f, 0, 0, "%.1f"))
            cmpt->SetRotation(glm::radians(_euler));
        ImGui::NextColumn();

        ImGui::AlignTextToFramePadding();
        ImGui::Text("Scale");
        ImGui::NextColumn();
        ImGui::SetNextItemWidth(-1);
        ImGui::DragFloat3("##Scale", (float *)cmpt->GetScalePtr(), 0.1f, 0, 0, "%.1f");
        ImGui::NextColumn();

        ImGui::Columns(1);
        ImGui::Separator();
        ImGui::PopStyleVar();
        ImGui::TreePop();
    }
}

void ComponentVisitor::ImplVisit(Ptr<CmptGeometry> cmpt)
{
    if (ImGui::TreeNode("Geometry"))
    {
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
        ImGui::Columns(2);
        ImGui::Separator();

        ImGui::AlignTextToFramePadding();
        ImGui::Text("Point Size");
        ImGui::NextColumn();
        ImGui::SetNextItemWidth(-1);
        ImGui::SliderInt("##PointSize", &cmpt->pointSize, 1, 10);
        ImGui::NextColumn();

        ImGui::Columns(1);
        ImGui::Separator();
        ImGui::PopStyleVar();
        ImGui::TreePop();
    }
}

// =================================================

void Attribute::ImplInspector()
{
    if (GetCurSObj() != nullptr)
        for (auto cmpt : GetCurSObj()->GetAllComponents())
            visitor.Visit(cmpt);
}
