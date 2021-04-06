#pragma once

#include <Common/Common.h>
#include "../ViewComponent.h"
#include <Core/Runtime/GlobalStorage.h>
namespace LUNA::Editor {

class Inspector : public ViewComponent {
   public:
    virtual bool Enter() const { return false; }
    virtual bool Draw() const {
        ImGui::Begin("Inspector");

        auto c = _GS<float>::getInstance()->Register("rtx",12.7f);
        
        ImGui::End();
        return false;
    }
    virtual bool Close() const { return false; }
    virtual ~Inspector() = default;
};

}  // namespace LUNA::Editor
