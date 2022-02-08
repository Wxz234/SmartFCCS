#pragma once
#include "pch.h"
#include <SmartFCCS/RHI.h>
namespace SmartFCCS {
	struct RenderTexture : public IRenderTexture {
		RenderTexture(ID3D11Texture2D* pTexture, ID3D11ShaderResourceView* pSrv, ID3D11RenderTargetView* pRtv) :m_Texture(pTexture), m_Srv(pSrv), m_Rtv(pRtv) {}
		IUnknown* GetNativePointer() const noexcept { return m_Texture.Get(); }
		ID3D11ShaderResourceView* GetShaderResourceView() const noexcept { return m_Srv.Get(); }
		ID3D11RenderTargetView* GetRenderTargetView() const noexcept { return m_Rtv.Get(); }

		Microsoft::WRL::ComPtr<ID3D11Texture2D> m_Texture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_Srv;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_Rtv;
	};
}