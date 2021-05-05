#pragma once

#include <Common/Common.h>
#include "../ViewComponent.h"
#include <Core/OpenGL/Shader.h>
namespace LUNA::Editor
{

    class KTKR_IKMvs : public ViewComponent
    {
    protected:
        KTKR::Ptr<LUNA::Shader> plyshader;

    public:
        virtual bool Enter();
        virtual bool Draw();
        virtual bool Close() { return false; }
        virtual ~KTKR_IKMvs() = default;
    };

} // namespace LUNA::Editor
