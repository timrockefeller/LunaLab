#pragma once
#include <string>
#include <Common/Ptr.h>
#include "../VAO.h"
namespace LUNA
{
    class FmtPLY : public VAO
    {
    private:
#ifdef DEPRECATED_FEATURE
        // deprecated
        static KTKR::Ptr<FmtPLY> _create(const std::string filePath);
#endif
    public:
        struct PLYVert
        {
            double x, y, z, w;// 0
            double nx, ny, nz;// 32
            unsigned char r, g, b, a;// 56
            double u, v;// 64
        };
        FmtPLY() = default;
        FmtPLY(std::vector<PLYVert> data);

        static KTKR::Ptr<FmtPLY> create(const std::string filePath);
    };
}