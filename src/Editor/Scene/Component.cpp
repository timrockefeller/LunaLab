#include <Editor/Scene/Component.h>
using namespace LUNA;
using namespace std;
using namespace KTKR;
void Component::LateInit()
{
    auto sobj = GetSceneObject();
    if (sobj)
        sobj->AttachComponent(This<Component>());
}