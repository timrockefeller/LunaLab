#include <Editor/UI/UIManager.h>

using namespace LUNA::Editor;
using namespace KTKR;
using namespace std;

bool UIManager::InitDemo()
{
    
    // =================================================
    
    AddViewComponent<MenuBar>();
    AddViewComponent<Heirachy>();
    AddViewComponent<Inspector>();

#ifdef _DEBUG
    // demo
    AddViewComponent<DemoWindow>();
#endif

    // =================================================

    AddViewComponent<KTKR_IKMvs>();
    // =================================================

    for (auto const &cmpt : viewCmpts)
    {
        cmpt.second->Enter();
    }
    return true;
}

bool UIManager::RunDemo()
{
    for (auto const &cmpt : viewCmpts)
    {
        if (cmpt.second->enabled)
            cmpt.second->Draw();
    }
    return true;
}