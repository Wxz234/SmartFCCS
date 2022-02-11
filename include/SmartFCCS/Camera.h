#pragma once
#include "Core.h"
namespace SmartFCCS {
	struct Camera {
		Camera(const DirectX::XMFLOAT3 & pos, const DirectX::XMFLOAT3& dir, const DirectX::XMFLOAT3& up, float FovAngleY, float AspectRatio, float NearZ, float FarZ)
		{
			this->pos = pos;
			this->dir = dir;
			this->up = up;
			this->FovAngleY = FovAngleY;
			this->AspectRatio = AspectRatio;
			this->NearZ = NearZ;
			this->FarZ = FarZ;
		}
		Camera(const Camera& camera) = default; 
		Camera& operator=(const Camera& camera) = default;
		Camera(Camera&& camera) noexcept = default;
		Camera& operator=(Camera&& camera) noexcept = default;
		void f() {
			//DirectX:: XMMatrixPerspectiveFovLH
				
		}
	private:
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 dir;
		DirectX::XMFLOAT3 up;
		float FovAngleY;
		float AspectRatio;
		float NearZ;
		float FarZ;
	};
}