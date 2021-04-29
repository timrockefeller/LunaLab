#include <Editor/GView.h>

using namespace LUNA::Editor;

GView::GView()
{
    scene = Scene::Create(std::make_shared<SceneObject>());
    auto a = SObj::Create("aaa");
    auto b = SObj::Create("bbb");
    auto c = SObj::Create("ccc");
    auto d = SObj::Create("ddd");
    auto e = SObj::Create("eee");
    auto f = SObj::Create("fff");

    a->AddChild(c);
    a->AddChild(d);
    a->AddChild(e);
    b->AddChild(f);
    b->AddChild(a);

    scene->GetRoot()->AddChild(b);
}