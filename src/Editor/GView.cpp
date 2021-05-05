#include <Editor/GView.h>

using namespace LUNA::Editor;

GView::GView()
{
    scene = Scene::Create(std::make_shared<SceneObject>());
}