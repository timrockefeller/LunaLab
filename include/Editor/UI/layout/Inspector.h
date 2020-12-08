#pragma once

#include <Common/Common.h>
#include "../ViewComponent.h"

namespace LUNA::Editor {

class Inspector : public ViewComponent {
   public:
    virtual bool Enter() const { return false; }
    virtual bool Draw() const {
        ImGui::Begin("Inspector");


        
        ImGui::End();
        return false;
    }
    virtual bool Close() const { return false; }
    virtual ~Inspector() = default;
};

}  // namespace LUNA::Editor
