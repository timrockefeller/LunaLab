/*
    display main class
*/

#pragma once

#include <Common/Common.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

namespace LUNA::Editor {

class ViewComponent {
   public:
    ViewComponent() = default;
    virtual ~ViewComponent() = default;
    short instanceID = 0xFF;

    // implement these function in every UI module.

    virtual bool Enter() const = 0;
    virtual bool Draw() const = 0;
    virtual bool Close() const = 0;
};

}  // namespace LUNA::Editor
