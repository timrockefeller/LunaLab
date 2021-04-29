#pragma once
#include <Common/Ptr.h>
#include <Common/TypeMap.h>
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
		KTKR::TypeMap<KTKR::Ptr<ViewComponent>> viewCmpts;

	public:
		template <typename T>
		using enable_if_is_viewcomponent_t = std::enable_if_t<std::is_base_of_v<ViewComponent, T>>;

		template <typename T, typename = enable_if_is_viewcomponent_t<T>>
		void AddViewComponent(KTKR::Ptr<T>&& t)
		{
			viewCmpts.insert({ typeid(T), std::make_shared<ViewComponent>(static_cast<ViewComponent*>(t.release())) });
		}

		template <typename T, typename = enable_if_is_viewcomponent_t<T>>
		void AddViewComponent()
		{
			viewCmpts.insert({ typeid(T), KTKR::Ptr<ViewComponent>(new T) });
		}

		template <typename T, typename = enable_if_is_viewcomponent_t<T>>
		KTKR::Ptr<T> GetViewComponent()
		{
			auto target = viewCmpts.find(typeid(T));
			return target == viewCmpts.end()
				? nullptr
				: KTKR::CastTo<T>(target->second);
		}

		bool InitDemo();
		bool RunDemo();
	};

} // namespace LUNA::Editor
