#pragma once
#include "Core.h"
namespace SmartFCCS {
	struct Camera {
		Camera() : pos(0, 0, 0), dir(0, 0, 1), up(0, 1, 0) {}
		Camera(const Camera& camera) = default; 
		Camera& operator=(const Camera& camera) = default;
		Camera(Camera&& camera) noexcept = default;
		Camera& operator=(Camera&& camera) noexcept = default;
		void f() {
			DirectX:: XMMatrixPerspectiveFovLH
		}
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 dir;
		DirectX::XMFLOAT3 up;
		float FovAngleY;
		float AspectRatio;
		float NearZ;
		float FarZ;
	};
}