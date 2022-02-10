#pragma once
#include "Core.h"
namespace SmartFCCS {
	struct Camera {
		Camera() {}
		Camera(const Camera& camera) = default; 
		Camera& operator=(const Camera& camera) = default;
		Camera(Camera&& camera) noexcept = default;
		Camera& operator=(Camera&& camera) noexcept = default;

		DirectX::XMFLOAT4 pos;
	};
}