// temporary option for load OpenGL's Buffer Result
#pragma once
#include "../ViewComponent.h"
namespace LUNA::Editor {
class ExposedCamera : public ViewComponent {
   public:
    virtual bool Enter() const { return false; }
    virtual bool Draw() const { return false; }
    virtual bool Close() const { return false; }
    virtual ~ExposedCamera() = default;
};

}  // namespace LUNA::Editor
