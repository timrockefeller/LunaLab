#include <Editor/UI/layout/Heirachy.h>
#include <Editor/UI/Attribute.h>
using namespace LUNA::Editor;

void Heirachy::IterChild(const KTKR::Ptr<SceneObject> root, long long &ptr_id)
{
    for (auto c : root->GetChildren())
    {
        ImGuiTreeNodeFlags node_flags = base_flags;
        if (ptr_id == nodeSel)
            node_flags |= ImGuiTreeNodeFlags_Selected;

        if (c->GetChildren().size())
        {
            bool node_open = ImGui::TreeNodeEx((void *)ptr_id, node_flags, c->name.c_str());
            if (ImGui::IsItemClicked())
            {
                nodeSel = ptr_id;
                Attribute::getInstance()->SetCurSObj(c);
            }
            ptr_id++;
            if (node_open)
            {
                IterChild(c, ptr_id);
                ImGui::TreePop();
            }
        }
        else
        {
            node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
            ImGui::TreeNodeEx((void *)ptr_id, node_flags, c->name.c_str());
            if (ImGui::IsItemClicked())
            {
                nodeSel = ptr_id;
                Attribute::getInstance()->SetCurSObj(c);
            }
            ptr_id++;
        }
    }
}

bool Heirachy::Draw()
{
    ImGui::Begin("Heirachy");
    nodeSum = 0;
    IterChild(GView::getInstance()->GetSceneRoot(), nodeSum);
    ImGui::End();
    return false;
}