// temporary option for load OpenGL's Buffer Result
#pragma once
#include "ViewComponent.h"
namespace LUNA::Editor {
class ExploedCamera : public ViewComponent {
   public:
    bool Enter() override { return false; }
    bool Draw() override { return false; }
    bool Close() override { return false; }
};

}  // namespace LUNA::Editor
