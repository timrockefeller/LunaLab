#pragma once
#include <Common/Ptr.h>
#include <Common/Singleton.h>
#include <vector>
#include "AllLayouts.h"
#include "ViewComponent.h"
namespace LUNA::Editor {

class UIManager : public KTKR::Singleton<UIManager> {
   private:
    template <typename T>
    using enable_if_is_viewcomponent_t = std::enable_if_t<std::is_base_of_v<ViewComponent, T>>;

    std::vector<KTKR::UPtr<ViewComponent>> viewCmpts;

   public:
    template <typename T, typename = enable_if_is_viewcomponent_t<T>>
    void AddViewComponent(KTKR::UPtr<T>&& t) {
        viewCmpts.push_back(std::make_unique<ViewComponent>(static_cast<ViewComponent*>(t.release())));
    }
    template <typename T, typename = enable_if_is_viewcomponent_t<T>>
    void AddViewComponent() {
        viewCmpts.push_back(KTKR::UPtr<ViewComponent>(new T));
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
