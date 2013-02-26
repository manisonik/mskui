#include "StdAfx.h"
#include "UIApplication.h"

CUIApplication::CUIApplication() : 
	m_cRef(1), 
	m_hWnd(NULL)
{
}

CUIApplication::~CUIApplication(void)
{
}

int CUIApplication::OnMessageLoop(
	MSK1_MESSAGELOOP_FLAG flag,
	LPMSG msg
	)
{
	if (flag == MSK1_MESSAGELOOP_PREPROCESS)
	{
		// TODO: Do something here.
	} else if (flag == MSK1_MESSAGELOOP_POSTPROCESS)
	{
		// TODO: Do somthing here.
	}

	return flag == MSK1_MESSAGELOOP_EXITPROCESS ? msg->wParam : 0;
}

int CUIApplication::OnCreate(LPCREATESTRUCT lpCreateStruct, IMSK1Window* pWnd)
{
	HRESULT hr = S_OK;

	IMSK1StatusBarCtrl* pStatusBarCtrl = NULL;

	pWnd->CreateStatusBar(MSK1::PointU(0, 0), MSK1::SizeU(0, 20), MSK1_SBARSTYLE_TOOLTIP, MSK1_WINDOWPLACEMENT_DOCK_BOTTOM, &pStatusBarCtrl);

	RECT client_rect;
	GetClientRect(pWnd->GetWindowHandle(), &client_rect);

	UINT status_parts[2] = { client_rect.right-client_rect.left-170,   
		client_rect.right-client_rect.left };

	pStatusBarCtrl->SetParts(1, status_parts);
	pStatusBarCtrl->SetBkColor(RGB(95, 158, 160));
	pStatusBarCtrl->SetText(L"Ready", 0, SBT_NOBORDERS, RGB(95, 158, 160));
	pStatusBarCtrl->SetTipText(0, L"Test");
	pStatusBarCtrl->SetMinHeight(25);

	return 0;
}

void CUIApplication::OnDestroy()
{
	PostQuitMessage(1);
}

STDMETHODIMP CUIApplication::OnProcessMessage(
	UINT msg,
	WPARAM wParam,
	LPARAM lParam,
	IMSK1Window* pWnd
	)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (msg)
	{
	case WM_CREATE:
		OnCreate((LPCREATESTRUCT) lParam, pWnd);
		break;
	case WM_PAINT:
		hdc = BeginPaint(m_hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(m_hWnd, &ps);
		break;
	case WM_SIZE:
		break;
	case WM_DESTROY:
		OnDestroy();
		break;
	}

	return 0;
}

STDMETHODIMP CUIApplication::OnCreateCommand(
	UINT cmdId,
	MSK1_COMMAND_TYPE cmdType,
	IMSK1CommandHandler** ppCommandHandler
	)
{

	if (cmdType == MSK1_COMMAND_CREATE) {
		if (cmdId == 0) {
			return QueryInterface(IID_PPV_ARGS(ppCommandHandler));
		}
	}

	return 	E_NOTIMPL;
}

STDMETHODIMP CUIApplication::OnDestroyCommand(void)
{
	// TODO: OnDestroy, Add code here.

	return E_NOTIMPL;
}

STDMETHODIMP CUIApplication::QueryInterface(
	REFIID   riid,
	LPVOID* ppvObj
	)
{
	if (riid == __uuidof(IUnknown) || riid == __uuidof(IMSK1Application))
	{
		*ppvObj = static_cast<IMSK1Application*>(this);
	}
	else if (riid == __uuidof(IMSK1CommandHandler))
	{
		*ppvObj = static_cast<IMSK1CommandHandler*>(this);
	}
	else 
	{
		*ppvObj = NULL;
		return E_NOINTERFACE;
	}

	AddRef();
	return S_OK;
}

ULONG CUIApplication::Release()
{
	// Decrement the object's internal counter.
	ULONG cRef = InterlockedDecrement(&m_cRef);

	if (cRef == 0)
	{
		delete this;
	}

	return cRef;
}

ULONG CUIApplication::AddRef()
{
	InterlockedIncrement(&m_cRef);
	return m_cRef;
}