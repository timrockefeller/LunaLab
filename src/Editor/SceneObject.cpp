#include <Editor/Scene/SceneObject.h>
#include <Editor/Scene/AllCmpts.h>
using namespace LUNA;
using namespace LUNA::Editor;
using namespace std;
const transformf SceneObject::GetLocalToWorldMatrix()
{
    auto tsfm = glm::mat4(1.0f);
    for (auto cur = This<SObj>(); cur != nullptr; cur = cur->GetParent())
    {
        auto cmpt = cur->GetComponent<CmptTransform>();
        if (cmpt)
            tsfm = cmpt->GetTransform() * tsfm;
    }
    return tsfm;
}

const std::vector<KTKR::Ptr<Component>> SceneObject::GetAllComponents() const
{
    std::vector<KTKR::Ptr<Component>> rsl;
    for (auto &cmp : components)
        rsl.push_back(cmp.second);
    return rsl;
}
void SceneObject::AttachComponent(KTKR::Ptr<Component> component)
{
    auto target = components.find(typeid(*component));

    if (target != components.end())
    {
        target->second->wSceneObject.reset();
    }
    component->wSceneObject = This<SceneObject>();
    components[typeid(*component)] = component;
}

bool SceneObject::DetachComponent(KTKR::Ptr<Component> component)
{
    auto target = components.find(typeid(*component));
    if (target == components.end())
        return false;
    if (target->second != component)
        return false;
    target->second->wSceneObject.reset();
    components.erase(target);
    return true;
}