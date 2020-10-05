// impl to a Tree?
#pragma once
#include <Common/Common.h>
#include <string>
namespace LUNA {
class SceneObject : public KTKR::Node<SceneObject> {
   public:
    SceneObject(Ptr<SceneObject> parent = nullptr, const std::string& name = "SceneObject")
        : Node(parent), name(name) {}

protected:
 virtual ~SceneObject() = default;

private:
 std::string name;
};
}  // namespace LUNA
