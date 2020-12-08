#pragma once
#include <Common/Ptr.h>
#include <Common/Singleton.h>
#include <vector>
#include "AllLayouts.h"
#include "ViewComponent.h"
namespace LUNA::Editor {

class UIManager : public KTKR::Singleton<UIManager> {
   private:
    std::vector<std::unique_ptr<ViewComponent>> viewCmpts;

   public:
    template <typename T, typename = std::enable_if<std::is_base_of<ViewComponent, T>::value>>
    bool AddViewComponent(std::unique_ptr<T>&& t) {
        viewCmpts.push_back(std::make_unique<ViewComponent>(static_cast<ViewComponent*>(t.release())));
        return true;
    }
    template <typename T, typename = std::enable_if<std::is_base_of<ViewComponent, T>::value>>
    bool AddViewComponent() {
        viewCmpts.push_back(std::unique_ptr<ViewComponent>(new T));
        return true;
    }
    bool InitDemo() {
        AddViewComponent<Inspector>();
        AddViewComponent<DemoWindow>();
        for (auto const& cmpt : viewCmpts) {
            cmpt->Enter();
        }
        return true;
    }
    bool RunDemo() {
        for (auto const& cmpt : viewCmpts) {
            cmpt->Draw();
        }
        return true;
    }
};

}  // namespace LUNA::Editor
