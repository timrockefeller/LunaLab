#pragma once

#include <Common/Common.h>
#include <Editor/UI/ViewComponent.h>

namespace LUNA::Editor {

class Inspector : public ViewComponent {
   public:
    bool Enter() override { return false; }
    bool Draw() override { return false; }
    bool Close() override { return false; }
};

}  // namespace LUNA::Editor
