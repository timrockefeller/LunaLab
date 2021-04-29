#pragma once
#include <glm/glm.hpp>
namespace LUNA
{

	template <int L, typename T>
	using vec = glm::vec<L, T>;

	template <int L>
	using vecf = vec<L, float>;

	using vecf2 = vecf<2>;
	using vecf3 = vecf<3>;
	using vecf4 = vecf<4>;

	// =================================================

	/*emplate <int L, typename T>
	struct point : public vec<L, T>
	{
	};*/

	template <int L>
	using pointf = vec<L, float>;

	using pointf2 = pointf<2>;
	using pointf3 = pointf<3>;
	using pointf4 = pointf<4>;
} // namespace LUNA
