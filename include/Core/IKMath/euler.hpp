#pragma once

#include <glm/glm.hpp>
namespace LUNA
{
	template <typename T>
	using euler = glm::vec<3, T>;

	using eulerf = euler<float>;
} // namespace LUNA
