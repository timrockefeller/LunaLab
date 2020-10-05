#pragma once

#include <Common/Common.h>
#include <Editor/UI/Component.h>

namespace LUNA {
namespace Editor {

class Inspector : public Component {
    bool Enter() override { return false; }
    bool Draw() override { return false; }
    bool Close() override { return false; }
};

}  // namespace Editor
}  // namespace LUNA
