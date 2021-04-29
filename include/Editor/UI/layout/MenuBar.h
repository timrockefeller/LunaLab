#pragma once

#include <Common/Common.h>
#include "../ViewComponent.h"
#include "../UIManager.h"
namespace LUNA::Editor
{
	class UIManager;
	class MenuBar : public ViewComponent
	{
	public:
		virtual bool Enter() { return false; }
		virtual bool Draw();
		virtual bool Close() { return false; }
		virtual ~MenuBar() = default;
	};

} // namespace LUNA::Editor
