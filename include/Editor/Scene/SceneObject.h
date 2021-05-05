// impl to a Tree?
#pragma once
#include <Common/Node.h>
#include "Component.h"
#include <Common/TypeMap.h>
#include <Core/IKMath/IKMath.hpp>
#include <string>
#include <vector>
namespace LUNA
{
    class Component;
    class SceneObject : public KTKR::Node<SceneObject>
    {
    private:
        template <typename T>
        using enable_if_is_component_t = std::enable_if_t<std::is_base_of_v<Component, T>>;

    public:
        static KTKR::Ptr<SceneObject> Create(const std::string &name = "new object")
        {
            return std::make_shared<SceneObject>(nullptr, name);
        }

        SceneObject(KTKR::Ptr<SceneObject> parent = nullptr, const std::string &name = "SceneObject")
            : Node(parent), name(name) {}

        virtual ~SceneObject() = default;

        // component handle
        template <typename T, typename = enable_if_is_component_t<T>>
        const KTKR::Ptr<T> GetComponent() const
        {
            auto target = components.find(typeid(T));
            return target == components.end()
                       ? nullptr
                       : KTKR::CastTo<T>(target->second);
        }

        template <typename T, typename = enable_if_is_component_t<T>>
        bool HaveComponent() const
        {
            return components.find(typeid(T)) != components.cend();
        }

        const std::vector<KTKR::Ptr<Component>> GetAllComponents() const;

        template <typename T, typename... Args, typename = enable_if_is_component_t<T>>
        const KTKR::Ptr<T> AddComponent(Args &&...args)
        {
            if (HaveComponent<T>())
                return nullptr;
            auto cmpt = T::Create(This<SceneObject>(), std::forward<Args>(args)...);
            return cmpt;
        }

        void AttachComponent(KTKR::Ptr<Component> component);

        template <typename T, typename = enable_if_is_component_t<T>>
        bool DetachComponent()
        {
            auto tarcmp = components.find(typeid(T));
            if (tarcmp == components.end())
                return false;
            tarcmp->second->wSceneObject.reset();
            return true;
        }
        bool DetachComponent(KTKR::Ptr<Component> component);

        // template <typename T, typename = enable_if_is_component_t<T>>
        // const KTKR::Ptr<T> GetComponentInChildren();

        // template <typename T, typename = enable_if_is_component_t<T>>
        // const std::vector<KTKR::Ptr<T>> GetComponentsInChildren();

        // 即时计算
        const transformf GetLocalToWorldMatrix();

    private:
        KTKR::TypeMap<KTKR::Ptr<Component>> components;

    public:
        std::string name;
    };
    using SObj = SceneObject;
} // namespace LUNA
