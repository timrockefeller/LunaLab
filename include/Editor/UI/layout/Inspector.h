#pragma once

#include <Common/Common.h>
#include <Editor/Scene/Scene.h>

#include "../ViewComponent.h"
#include <Core/Runtime/GlobalStorage.h>

#include "../Attribute.h"

namespace LUNA::Editor
{

    class Inspector : public ViewComponent
    {
    public:
        virtual bool Enter()
        {
            // Scene::Create();

            return false;
        }
        virtual bool Draw()
        {
            ImGui::Begin("Inspector");

            Attribute::Get()->ImplInspector();
            
            ImGui::End();
            return false;
        }
        virtual bool Close() { return false; }
        virtual ~Inspector() = default;
    };

} // namespace LUNA::Editor
