/*
    display main class
*/

#pragma once

#include <Common/Common.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

namespace LUNA {
namespace Editor {

class ViewComponent {
   public:
    short instanceID = 0xFF;

    // implement these function in every UI module.
    
    virtual bool Enter() = 0;
    virtual bool Draw() = 0;
    virtual bool Close() = 0;

   protected:
    ViewComponent() = default;
    ~ViewComponent() = default;
};

}  // namespace Editor
}  // namespace LUNA
