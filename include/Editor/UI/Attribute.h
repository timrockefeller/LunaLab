#pragma once
#include <Common/Ptr.h>
#include <Ikit/STL/Singleton.h>
#include "../Scene/SceneObject.h"
#include "../Scene/AllCmpts.h"
#include <Common/Visitor.h>

namespace LUNA::Editor
{
    using AllComponent = std::tuple<
        CmptTransform,
        CmptGeometry>;

    class ComponentVisitor : public KTKR::SharedVisitor<ComponentVisitor, Component, AllComponent, void()>
    {
    public:
        ComponentVisitor() = default;
        void ImplVisit(KTKR::Ptr<CmptTransform>);
        void ImplVisit(KTKR::Ptr<CmptGeometry>);
    };

    class Attribute final : public KTKR::Singleton<Attribute>
    {
        friend class KTKR::Singleton<Attribute>;

    protected:
        ComponentVisitor visitor;
        const KTKR::Ptr<SObj> GetCurSObj() const { return curSObj; }
        KTKR::Ptr<SObj> curSObj;
        Attribute() = default;
        Attribute(KTKR::Ptr<SObj> curSObj) : curSObj{curSObj} {}

    public:
        void SetCurSObj(KTKR::Ptr<SObj> p) { curSObj = p; }
        void ImplInspector();
    };

} // namespace LUNA::Editor
