#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
namespace LUNA
{

	template <typename T>
	using quat = glm::qua<T>;

	using quatf = quat<float>;
} // namespace LUNA
