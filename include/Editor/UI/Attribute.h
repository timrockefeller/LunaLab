#pragma once
#include <Common/Ptr.h>
#include <Common/Singleton.h>
#include "../Scene/SceneObject.h"
#include "../Scene/AllCmpts.h"

namespace LUNA::Editor
{
    class Attribute final : public KTKR::Singleton<Attribute>
    {
    protected:
        Attribute();
        const KTKR::Ptr<SObj> GetCurSObj() const { return curSObj.lock(); }
        KTKR::WPtr<SObj> curSObj;
    };

} // namespace LUNA::Editor
