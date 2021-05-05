#pragma once
#include <glm/glm.hpp>
namespace LUNA
{

    template <typename T>
    using transform = glm::mat<4, 4, T>;

    using transformf = transform<float>;
} // namespace LUNA
