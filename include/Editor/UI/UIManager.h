#pragma once
#include <Common/Ptr.h>
#include <Common/Singleton.h>
#include <Core/Runtime/LocalStorage.h>
#include <vector>
#include "AllLayouts.h"
#include "ViewComponent.h"
#include <3rdParty/nameof.hpp>
namespace LUNA::Editor
{

    class UIManager : public KTKR::Singleton<UIManager>
    {
    private:
        template <typename T>
        using enable_if_is_viewcomponent_t = std::enable_if_t<std::is_base_of_v<ViewComponent, T>>;

        std::vector<KTKR::UPtr<ViewComponent>> viewCmpts;
        LocalStorage<bool> ViewEnabled;

    public:
        template <typename T, typename = enable_if_is_viewcomponent_t<T>>
        void AddViewComponent(KTKR::UPtr<T> &&t)
        {
            viewCmpts.push_back(std::make_unique<ViewComponent>(static_cast<ViewComponent *>(t.release())));
            ViewEnabled.getPtr(nameof::nameof_type<T>(), true);
        }
        template <typename T, typename = enable_if_is_viewcomponent_t<T>>
        void AddViewComponent()
        {
            viewCmpts.push_back(KTKR::UPtr<ViewComponent>(new T));
        }

        bool InitDemo()
        {
            AddViewComponent<MenuBar>();

            AddViewComponent<Inspector>();
            AddViewComponent<DemoWindow>();
            for (auto const &cmpt : viewCmpts)
            {
                cmpt->Enter();
            }
            return true;
        }
        bool RunDemo()
        {
            for (auto const &cmpt : viewCmpts)
            {
                cmpt->Draw();
            }
            return true;
        }
    };

} // namespace LUNA::Editor
