#pragma once

#include "./SceneRenderer.h"

namespace LUNA
{
    class SceneSaver
    {
    public:
        void loadSceneFile(const char *path);
        void loadSceneFile(string path);

        void saveSceneFile(const char *path);
        void saveSceneFile(string path);
    };
} // namespace LUNA
