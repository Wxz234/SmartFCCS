#pragma once
#include "Core.h"
namespace SmartFCCS {
	struct Camera {
		Camera(
			const DirectX::XMFLOAT3 & pos, 
			const DirectX::XMFLOAT3& focus,
			const DirectX::XMFLOAT3& up, 
			float FovAngleY, 
			float AspectRatio, 
			float NearZ, 
			float FarZ)
		{
			this->pos = pos;
			this->focus = focus;
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
		DirectX::XMMATRIX GetVP() {
			auto _pos = DirectX::XMLoadFloat3(&pos);
			auto _focus = DirectX::XMLoadFloat3(&focus);
			auto _up = DirectX::XMLoadFloat3(&up);
			return DirectX::XMMatrixTranspose(DirectX::XMMatrixLookAtLH(_pos, _focus, _up)* DirectX::XMMatrixPerspectiveFovLH(FovAngleY, AspectRatio, NearZ, FarZ));	
		}
	private:
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 focus;
		DirectX::XMFLOAT3 up;
		float FovAngleY;
		float AspectRatio;
		float NearZ;
		float FarZ;
	};
}