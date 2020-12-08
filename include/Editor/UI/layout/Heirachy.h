#pragma once

#include <Common/Common.h>
#include "../ViewComponent.h"

namespace LUNA::Editor {

class Heirachy : public ViewComponent {
   public:
    virtual bool Enter() const { return false; }
    virtual bool Draw() const { return false; }
    virtual bool Close() const { return false; }
    virtual ~Heirachy() = default;
};

}  // namespace LUNA::Editor
