// impl to a Tree?
#pragma once
#include <Common/Node.h>
#include <Common/TypeMap.h>
#include <string>
namespace LUNA {
class Component;
class SceneObject : public KTKR::Node<SceneObject> {
   private:
    template <typename T>
    using enable_if_is_component_t = std::enable_if_t<std::is_base_of_v<Component, T>>;

   public:
    SceneObject(KTKR::Ptr<SceneObject> parent = nullptr, const std::string& name = "SceneObject")
        : Node(parent), name(name) {}

   protected:
    virtual ~SceneObject() = default;

    // component handle
    template <typename T, typename = enable_if_is_component_t<T>>
    const KTKR::Ptr<T> GetComponent() const {
        auto target = components.find(typeid(T));
        return target == components.end()
                   ? nullptr
                   : KTKR::CastTo<T>(target->second);
    }

    template <typename T, typename = enable_if_is_component_t<T>>
    bool HaveComponent() const { return components.find(typeid(T)) != components.cend(); }

    const std::vector<KTKR::Ptr<Component>> GetAllComponents() const {
        std::vector<KTKR::Ptr<Component>> rsl;
        for (auto& cmp : components)
            rsl.push_back(cmp.second);
        return rsl;
    }

    template <typename T, typename... Args, typename = enable_if_is_component_t<T>>
    const KTKR::Ptr<T> AddComponent(Args&&... args) {
        if (HaveComponent<T>())
            return nullptr;
        auto cmpt = T::New(This<SceneObject>(), std::forward<Args>(args)...);
        return cmpt;
    }

    void AttachComponent(KTKR::Ptr<Component> component) {
        auto target = components.find(typeid(*component));

        if (target != components.end()) {
            target->second->wSceneObject.reset();
            component->wSceneObject = This<SceneObject>();
            components[typeid(*component)] = component;
        }
    }

    template <typename T, typename = enable_if_is_component_t<T>>
    bool DetachComponent() {
        auto tarcmp = components.find(typeid(T));
        if (tarcmp == components.end())
            return false;
        tarcmp->second->wSceneObject.reset();
        return true;
    }
    bool DetachComponent(KTKR::Ptr<Component> component) {
        auto target = components.find(typeid(*component));
        if (target == components.end())
            return false;
        if (target->second != component)
            return false;
        target->second->wSObj.reset();
        components.erase(target);
        return true;
    }

    template <typename T, typename = enable_if_is_component_t<T>>
    const KTKR::Ptr<T> GetComponentInChildren();

    template <typename T, typename = enable_if_is_component_t<T>>
    const std::vector<KTKR::Ptr<T>> GetComponentsInChildren();

   private:
    KTKR::TypeMap<KTKR::Ptr<Component>> components;

   public:
    std::string name;
};
}  // namespace LUNA
