#include <Editor/Scene/Scene.h>
#include <Editor/Scene/AllCmpts.h>
#include <functional>
using namespace LUNA;
using namespace LUNA::Editor;
using namespace KTKR;
using namespace std;

void Scene::SetWriteLock(bool isLock)
{
    if (isLock)
        writeLock.lock();
    else
        writeLock.unlock();
}
bool Scene::GenID()
{
    name2ID.clear();
    ID2name.clear();

    std::function<bool(Ptr<SObj>)> genID;

    genID = [this, &genID](Ptr<SObj> sobj) -> bool {
        auto target = name2ID.find(sobj->name);
        if (target != name2ID.end())
        {
            printf("ERROR: two sobjs have same name.\n");
            return false;
        }
        name2ID[sobj->name] = 0; //tmp invalid ID
        for (auto child : sobj->GetChildren())
        {
            if (!genID(child))
                return false;
        }
        return true;
    };

    if (!genID(root))
    {
        name2ID.clear();
        ID2name.clear();
        return false;
    }

    int curID = 1;
    for (auto &pair : name2ID)
    {
        pair.second = curID;
        ++curID;
    }

    for (auto &pair : name2ID)
        ID2name[pair.second] = pair.first;

    return true;
}

int Scene::GetID(Ptr<SObj> sobj) const
{
    auto target = name2ID.find(sobj->name);
    if (target == name2ID.cend())
        return 0;

    return target->second;
}

const string Scene::GetName(int ID) const
{
    auto target = ID2name.find(ID);
    if (target == ID2name.cend())
        return "";

    return target->second;
}

void Scene::AddSobj(KTKR::Ptr<SObj> sobj)
{
    if (!sobj->HaveComponent<CmptTransform>())
    {
        sobj->AddComponent<CmptTransform>();
    }
    root->AddChild(sobj);
}