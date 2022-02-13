#pragma once
#include "Core.h"

namespace SmartFCCS {
	struct Camera {
		Camera() {
			pos = DirectX::XMFLOAT3(0, 0, 0);
			dir = DirectX::XMFLOAT3(0, 0, 1);
			up = DirectX::XMFLOAT3(0, 1, 0);
			FovAngleY = DirectX::XMConvertToRadians(45.f);
			AspectRatio = 1.f;
			NearZ = 0.1f;
			FarZ = 100.f;
		}

		Camera(const Camera& camera) = default;
		Camera& operator=(const Camera& camera) = default;
		Camera(Camera&& camera) noexcept = default;
		Camera& operator=(Camera&& camera) noexcept = default;

		void SetAspectRatio(float aspectRatio) { AspectRatio = aspectRatio; }
		void SetFov(float fov) { FovAngleY = fov; }
		void SetNearZ(float nearZ) { NearZ = nearZ; }
		void SetFarZ(float farZ) { FarZ = farZ; }

		DirectX::XMMATRIX GetViewMatrix() const {
			auto _pos = DirectX::XMLoadFloat3(&pos);
			auto _dir = DirectX::XMLoadFloat3(&dir);
			auto _up = DirectX::XMLoadFloat3(&up);
			return DirectX::XMMatrixLookToLH(_pos, _dir, _up);
		}

		DirectX::XMMATRIX GetProjectionMatrix() const {
			return DirectX::XMMatrixPerspectiveFovLH(FovAngleY, AspectRatio, NearZ, FarZ);
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