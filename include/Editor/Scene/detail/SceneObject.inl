#include "../SceneObject.h"

bool LUNA::SceneObject::DetachComponent(KTKR::Ptr<LUNA::Component> component) {
    auto target = components.find(typeid(*component));
    if (target == components.end())
        return false;
    if (target->second != component)
        return false;
    target->second->wSceneObject.reset();
    components.erase(target);
    return true;
}
