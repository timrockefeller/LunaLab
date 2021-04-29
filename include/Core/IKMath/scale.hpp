#pragma once
#include <glm/glm.hpp>
namespace LUNA
{

    template <int N, typename T>
    using scale = glm::vec<N, T>;

    template <int N>
    using scalef = scale<N, float>;

    using scalef2 = scalef<2>;
    using scalef3 = scalef<3>;
} // namespace LUNA
