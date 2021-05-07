#pragma once

#include "./Component.h"
#include <Core/IKMath/IKMath.hpp>
#include <Core/OpenGL/VAO.h>
#include <Core/OpenGL/Shader.h>
namespace LUNA::Editor
{

    class CmptGeometry : public Component
    {

    public:
        static KTKR::Ptr<CmptGeometry> Create(KTKR::Ptr<SceneObject> sceneObject,
                                              KTKR::Ptr<LUNA::VAO> geometry,
                                              KTKR::Ptr<LUNA::Shader> shader)
        {
            return KTKR::Create<CmptGeometry>(sceneObject, geometry, shader);
        }

    public:
        CmptGeometry(KTKR::Ptr<SceneObject> sceneObject,
                     KTKR::Ptr<LUNA::VAO> geometry,
                     KTKR::Ptr<LUNA::Shader> shader)
            : geometry{geometry},
              shader{shader},
              Component{sceneObject},
              enabled{true} {}
        CmptGeometry(KTKR::Ptr<SceneObject> sceneObject)
            : Component{sceneObject},
              enabled{true} {}
        KTKR::Ptr<LUNA::VAO> geometry;
        KTKR::Ptr<LUNA::Shader> shader;
        bool enabled;

        int pointSize = 5;
    };

}