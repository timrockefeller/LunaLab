#pragma once

#include <Common/Common.h>
#include "../ViewComponent.h"
#include <Editor/Scene/SceneObject.h>
#include <Editor/GView.h>
namespace LUNA::Editor
{

    class Heirachy : public ViewComponent
    {

    private:
        ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;

        long long nodeSum;
        // only one node selected once;
        long long nodeSel;

    private:
        void IterChild(const KTKR::Ptr<SceneObject> root, long long &ptr_id);

    public:
        virtual bool Enter() { return false; }

        virtual bool Draw();
        virtual bool Close() { return false; }
        virtual ~Heirachy() = default;
    };

} // namespace LUNA::Editor
