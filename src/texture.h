#pragma once
#include "pch.h"
#include <SmartFCCS/RHI.h>
namespace SmartFCCS {
	struct RenderTexture : public IRenderTexture {
		ID3D11ShaderResourceView* GetShaderResourceView() const noexcept;
		ID3D11RenderTargetView* GetRenderTargetView() const noexcept;
	};
}