#include "stdafx.h"

IDirect3D9* D3D::direct = NULL;
IDirect3DDevice9* D3D::device = NULL;
ID3DXLine* D3D::line = NULL;
ID3DXFont* D3D::font = NULL;

D3D::D3D9Renderer* gRenderer = new D3D::D3D9Renderer();