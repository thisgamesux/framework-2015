#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9")
#pragma comment(lib, "d3dx9")

struct D3D
{
	static IDirect3D9* direct;
	static IDirect3DDevice9* device;
	static ID3DXLine* line;
	static ID3DXFont* font;

	static bool Init(HWND hWnd)
	{
		direct = Direct3DCreate9(D3D_SDK_VERSION);

		if (direct == NULL)
			return false;

		D3DDISPLAYMODE displayMode;

		direct->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode);

		D3DPRESENT_PARAMETERS presentParams;

		memset(&presentParams, 0, sizeof(presentParams));

		presentParams.BackBufferWidth = 0;
		presentParams.BackBufferHeight = 0;
		presentParams.BackBufferCount = 1;
		presentParams.BackBufferFormat = displayMode.Format;
		presentParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
		presentParams.Windowed = TRUE;
		presentParams.EnableAutoDepthStencil = TRUE;
		presentParams.AutoDepthStencilFormat = D3DFMT_D16;
		presentParams.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		presentParams.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

		if (FAILED(direct->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &presentParams, &device)))
		{
			return false;
		}

		if (FAILED(D3DXCreateLine(device, &line)))
		{
			return false;
		}

		if (FAILED(D3DXCreateFontA(device, 14, 0, FW_NORMAL, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &font)))
		{
			return false;
		}

		return true;
	}

	static void BeginFrame()
	{
		device->BeginScene();
		device->Clear(0, 0, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	}

	static void EndFrame()
	{
		device->EndScene();
		device->Present(NULL, NULL, NULL, NULL);
	}

	static void Close()
	{
		if (device)
		{
			device->Release();
			device = NULL;
		}

		if (direct)
		{
			direct->Release();
			direct = NULL;
		}
	}

	class D3D9Renderer : public FWSDK::IRenderer
	{
	public:
		void drawRect(int x, int y, int w, int h, FWSDK::Color color)
		{
			D3DXVECTOR2 vLine[2];

			line->SetWidth((FLOAT)w);
			line->SetAntialias(FALSE);
			line->SetGLLines(TRUE);

			D3DXVECTOR2 lineVector[2];

			lineVector[0].x = (FLOAT)(x + w / 2);
			lineVector[0].y = (FLOAT)(y);
			lineVector[1].x = (FLOAT)(x + w / 2);
			lineVector[1].y = (FLOAT)(y + h);

			line->Begin();
			line->Draw(lineVector, 2, D3DCOLOR_RGBA(color.r, color.g, color.b, color.a));
			line->End();
		}

		void drawString(int x, int y, std::string text, FWSDK::Color color)
		{
			RECT rr = { x, y, x + 1024, y + 1024 };

			font->DrawText(NULL, text.c_str(), -1, &rr, DT_NOCLIP, D3DCOLOR_RGBA(color.r, color.g, color.b, color.a));
		}
	};
};