#include <Editor/Scene/CmptTransform.h>
using namespace LUNA;
using namespace LUNA::Editor;
using namespace KTKR;
using namespace std;

void CmptTransform::SetPosition(const pointf3 &position)
{
    dirtyTransform = true;
    this->position = position;
}
void CmptTransform::SetRotation(const quatf &rotation)
{
    dirtyTransform = true;
    this->rotation = rotation;
}
