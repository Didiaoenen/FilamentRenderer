#pragma once

#include <any>
#include <tuple>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace FR
{
	const static float kPI = glm::pi<float>();

	static std::any AlignValue(std::any& pAny0, std::any pAny1, const float pEpsilon = 0.01F)
	{
		if (pAny0.type() == typeid(float) && pAny1.type() == typeid(float))
		{
			auto& f0 = reinterpret_cast<float&>(pAny0);
			auto& f1 = reinterpret_cast<float&>(pAny1);
			f0 = glm::abs(f0 - f1) < pEpsilon ? f1 : f0;
			return f0;
		}
		else if (pAny0.type() == typeid(glm::vec2) && pAny1.type() == typeid(glm::vec2))
		{
			auto& f0 = reinterpret_cast<glm::vec2&>(pAny0);
			auto& f1 = reinterpret_cast<glm::vec2&>(pAny1);
			f0.x = glm::abs(f0.x - f1.x) < pEpsilon ? f1.x : f0.x;
			f0.y = glm::abs(f0.y - f1.y) < pEpsilon ? f1.y : f0.y;
			return f0;
		}
		else if (pAny0.type() == typeid(glm::vec3) && pAny1.type() == typeid(glm::vec3))
		{
			auto& f0 = reinterpret_cast<glm::vec3&>(pAny0);
			auto& f1 = reinterpret_cast<glm::vec3&>(pAny1);
			f0.x = glm::abs(f0.x - f1.x) < pEpsilon ? f1.x : f0.x;
			f0.y = glm::abs(f0.y - f1.y) < pEpsilon ? f1.y : f0.y;
			f0.z = glm::abs(f0.z - f1.z) < pEpsilon ? f1.z : f0.z;
			return f0;
		}
		else if (pAny0.type() == typeid(glm::vec4) && pAny1.type() == typeid(glm::vec4))
		{
			auto& f0 = reinterpret_cast<glm::vec4&>(pAny0);
			auto& f1 = reinterpret_cast<glm::vec4&>(pAny1);
			f0.x = glm::abs(f0.x - f1.x) < pEpsilon ? f1.x : f0.x;
			f0.y = glm::abs(f0.y - f1.y) < pEpsilon ? f1.y : f0.y;
			f0.z = glm::abs(f0.z - f1.z) < pEpsilon ? f1.z : f0.z;
			f0.w = glm::abs(f0.w - f1.w) < pEpsilon ? f1.w : f0.w;
			return f0;
		}
		return std::make_any<bool>(false);
	}

	static void SanitizeEuler(glm::vec3& euler)
	{
		const float negativeFlip = -0.0001F;
		const float positiveFlip = (kPI * 2.0F) - 0.0001F;

		if (euler.x < negativeFlip)
		{
			euler.x += 2.0 * kPI;
		}
		else if (euler.x > positiveFlip)
		{
			euler.x -= 2.0 * kPI;
		}

		if (euler.y < negativeFlip)
		{
			euler.y += 2.0 * kPI;
		}
		else if (euler.y > positiveFlip)
		{
			euler.y -= 2.0 * kPI;
		}

		if (euler.z < negativeFlip)
		{
			euler.z += 2.0 * kPI;
		}
		else if (euler.z > positiveFlip)
		{
			euler.z -= 2.0 * kPI;
		}
	}

	static glm::vec3 MatrixToEuler(const glm::mat4& matrixMat4)
	{
		glm::mat3 matrixMat3 = glm::mat3(
			matrixMat4[0].x, matrixMat4[1].x, matrixMat4[2].x,
			matrixMat4[0].y, matrixMat4[1].y, matrixMat4[2].y,
			matrixMat4[0].z, matrixMat4[1].z, matrixMat4[2].z);

		glm::vec3 v;

		// YXZ order
		if (matrixMat3[1][2] < 0.999F) // some fudge for imprecision
		{
			if (matrixMat3[1][2] > -0.999F) // some fudge for imprecision
			{
				v.x = asin(-matrixMat3[1][2]);
				v.y = atan2(matrixMat3[0][2], matrixMat3[2][2]);
				v.z = atan2(matrixMat3[1][0], matrixMat3[1][1]);
				//SanitizeEuler(v);
			}
			else
			{
				// WARNING.  Not unique.  YA - ZA = atan2(r01,r00)
				v.x = kPI * 0.5F;
				v.y = atan2(matrixMat3[0][1], matrixMat3[0][0]);
				v.z = 0.0F;
				//SanitizeEuler(v);
			}
		}
		else
		{
			// WARNING.  Not unique.  YA + ZA = atan2(-r01,r00)
			v.x = -kPI * 0.5F;
			v.y = atan2(-matrixMat3[0][1], matrixMat3[0][0]);
			v.z = 0.0F;
			//SanitizeEuler(v);
		}

		return v;
	}
}