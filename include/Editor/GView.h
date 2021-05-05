#pragma once

#include <Common/Common.h>

#include "Scene/Scene.h"
namespace LUNA::Editor
{
	class GView : public KTKR::Singleton<GView>
	{

	public:
		GView();

		KTKR::Ptr<Scene> scene;

		KTKR::Ptr<SObj> GetSceneRoot() { return scene->GetRoot(); }

		void AddSobjToTop(KTKR::Ptr<SObj> sobj)
		{
			scene->AddSobj(sobj);
		}
	};
}