#include "stdafx.h"
#include "msk1dockcontainer.h"


CMSK1DockContainer::CMSK1DockContainer(void)
{
	// Create Universal Window Class
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= 0;
	wcex.lpfnWndProc	= CMSK1DockContainer::DockContainerProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= HINST_THISCOMPONENT;
	wcex.hIcon			= NULL;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= NULL;
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= L"MSK1_DOCK_CONTAINER";
	wcex.hIconSm		= NULL;
}

LRESULT CMSK1DockContainer::DockContainerProc(
	HWND hWnd, 
	UINT msg, 
	WPARAM wParam, 
	LPARAM lParam
	)
{
	static CMSK1Window* pWindow = NULL;

	if (pWindow)
	{
		switch (msg)
		{
		case WM_SIZE:
			break;
		}

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	if (msg == WM_NCCREATE) {
		LPCREATESTRUCT createStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);  
		pWindow = reinterpret_cast<CMSK1Window *>(createStruct->lpCreateParams);

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return 0;
}

CMSK1DockContainer::~CMSK1DockContainer(void)
{
}

STDMETHODIMP CMSK1DockContainer::Initialize(
	CMSK1Window* pParentWnd
	)
{
	RECT rc;
	GetClientRect(pParentWnd->m_hWnd, &rc);

	CreateWindow(L"MSK1_DOCK_CONTAINER", L"DockContainer", WS_VISIBLE | WS_CHILD, 
		0, 0, RECTWIDTH(rc), RECTHEIGHT(rc), pParentWnd->m_hWnd, 0, HINST_THISCOMPONENT, pParentWnd);

	return S_OK;
}