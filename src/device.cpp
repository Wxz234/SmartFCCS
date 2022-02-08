#include "device.h"
#include "texture.h"
namespace SmartFCCS {
	Device::Device() {
		UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)  
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
		};
		D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevels, 2, D3D11_SDK_VERSION, m_Device.GetAddressOf(), nullptr, m_DeviceContext.GetAddressOf());
	}

	RenderTextureUniquePtr Device::CreateRenderTexture(uint32_t width, uint32_t height, DXGI_FORMAT format) {

		D3D11_TEXTURE2D_DESC desc = { width ,height,1,1,format,{1,0},D3D11_USAGE_DEFAULT,D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE,0,0 };
		Microsoft::WRL::ComPtr<ID3D11Texture2D> Texture;
		m_Device->CreateTexture2D(&desc, nullptr, &Texture);

		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.Format = format;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MostDetailedMip = 0;
		srvDesc.Texture2D.MipLevels = -1;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Srv;
		m_Device->CreateShaderResourceView(Texture.Get(), &srvDesc, &Srv);

		D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
		rtvDesc.Format = format;
		rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		rtvDesc.Texture2D.MipSlice = 0;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> Rtv;
		m_Device->CreateRenderTargetView(Texture.Get(), &rtvDesc, &Rtv);

		return RenderTextureUniquePtr(new RenderTexture(Texture.Get(), Srv.Get(), Rtv.Get()), [](IRenderTexture* p) { DestroyObject(p); });
	}

	FCCS_API DeviceUniquePtr CreateDevice() {
		return DeviceUniquePtr(new Device, [](IDevice* p) { DestroyObject(p); });
	}
}