#pragma once

#include <Common/Heap.h>

namespace LUNA {
class SceneObject;
class Component : public KTKR::HeapObj {
   protected:
    Component(KTKR::Ptr<SceneObject> sceneObject)
        : wSceneObject(sceneObject) {}
    virtual ~Component() = default;
    virtual void LateInit() override;
    Component(const Component& other)
        : wSceneObject{other.wSceneObject} {}
    Component& operator=(const Component& other) {
        wSceneObject = other.wSceneObject;
        return *this;
    }

   public:
    const KTKR::WPtr<SceneObject> GetSceneObject() const { return wSceneObject.lock(); }

   private:
    friend SceneObject;
    KTKR::WPtr<SceneObject> wSceneObject;
};
}  // namespace LUNA
