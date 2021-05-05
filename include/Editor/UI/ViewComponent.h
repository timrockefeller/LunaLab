/*
    display main class
*/

#pragma once

#include <Common/Common.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

namespace LUNA::Editor
{
    
    static void HelpMarker(const char *desc)
    {
        ImGui::TextDisabled("(?)");
        if (ImGui::IsItemHovered())
        {
            ImGui::BeginTooltip();
            ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
            ImGui::TextUnformatted(desc);
            ImGui::PopTextWrapPos();
            ImGui::EndTooltip();
        }
    }
    
    
    class ViewComponent
    {
    public:
        ViewComponent() = default;
        virtual ~ViewComponent() = default;
        size_t instanceID = 0xFF;
        bool enabled = true;
        // implement these function in every UI module.

        virtual bool Enter() = 0;
        virtual bool Draw() = 0;
        virtual bool Close() = 0;
    };

} // namespace LUNA::Editor
