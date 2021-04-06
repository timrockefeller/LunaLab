#pragma once

#include <Common/Common.h>
#include "../ViewComponent.h"

namespace LUNA::Editor
{

    class MenuBar : public ViewComponent
    {
    public:
        virtual bool Enter() const { return false; }
        virtual bool Draw() const
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
                }if (ImGui::BeginMenu("View"))
                {
                    if (ImGui::MenuItem("Inspector"))
                    {
                    }
                    ImGui::EndMenu();
                }
                ImGui::EndMainMenuBar();
            }
            return false;
        }
        virtual bool Close() const { return false; }
        virtual ~MenuBar() = default;
    };

} // namespace LUNA::Editor
