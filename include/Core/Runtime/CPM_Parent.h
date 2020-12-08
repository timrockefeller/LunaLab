#pragma once

#include <Common/Ptr.h>
#include <Ikit/ECS/Entity.h>
namespace LUNA {
class CPM_Parent {
   public:
    KTKR::WPtr<KTKR::ECS::Entity> parent;
};
}  // namespace LUNA
