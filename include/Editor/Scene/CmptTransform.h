#pragma once

#include "./Component.h"
#include <Core/IKMath/IKMath.hpp>
namespace LUNA::Editor
{
	class CmptTransform final : public Component
	{
	public:
		static KTKR::Ptr<CmptTransform> Create(KTKR::Ptr<SceneObject> sceneObject)
		{
			return KTKR::Create<CmptTransform>(sceneObject);
		}

	public:
		CmptTransform(KTKR::Ptr<SceneObject> sceneObject) : Component{sceneObject}
		{

			position = {0, 0, 0};
			rotation = {0, 0, 0, 1};
			scale = {1, 1, 1};
			dirtyTransform = true;
		}

		const pointf3 &GetPosition() const { return position; }
		pointf3 *GetPositionPtr() { return &position; }
		const quatf &GetRotation() const { return rotation; }
		quatf *GetRotationPtr() { return &rotation; }
		const eulerf GetRotationEuler() const { return glm::eulerAngles(rotation); }
		const scalef3 &GetScale() const { return scale; }
		scalef3 *GetScalePtr() { return &scale; }
		const transformf GetTransform() const
		{
			transformf rsl = glm::mat4(1.0f);
			rsl = glm::translate(rsl, position);
			rsl = glm::mat4_cast(rotation) * rsl;
			rsl = glm::scale(rsl, scale);
			return rsl;
		}
		// =================================================

		void SetPosition(const pointf3 &position);
		void Translate(const vecf3 &delta)
		{
			SetPosition(position + delta);
		}

		void SetRotation(const quatf &rotation);
		void SetRotation(const vecf3 &axis, float angle)
		{
			SetRotation(glm::angleAxis(angle, axis));
		}
		void SetRotation(const eulerf &euler)
		{
			SetRotation(glm::quat(euler));
		}

		void Rotate(const quatf &rot)
		{
			SetRotation(rot * rotation);
		}
		/**
		 *
		 * @param axis
		 * @param angle
		 */
		void Rotate(const vecf3 &axis, float angle)
		{
			Rotate(glm::angleAxis(angle, axis));
		}
		void Rotate(const eulerf &euler)
		{
			Rotate(glm::quat(euler) * rotation);
		}

		void SetScale(const scalef3 &xyz);
		void Scale(const scalef3 &scale)
		{
			SetScale(this->scale * scale);
		}
		// =================================================

	private:
		void CmptTransform::UpdateMat() const;

		pointf3 position;
		quatf rotation;
		scalef3 scale;

		mutable bool dirtyTransform;
	};

} // namespace LUNA::Editor
