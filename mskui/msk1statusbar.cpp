#include "stdafx.h"
#include "msk1statusbar.h"


CMSK1StatusBar::CMSK1StatusBar(CMSK1Framework* pFramework) :
	CMSK1Window(pFramework),
	m_isOwnerDraw(FALSE),
	m_bgColor(CLR_DEFAULT)
{
}


CMSK1StatusBar::~CMSK1StatusBar(void)
{
}

STDMETHODIMP CMSK1StatusBar::OnCreateDeviceIndependentResources()
{
	HRESULT hr = S_OK;

	return hr;
}

STDMETHODIMP CMSK1StatusBar::OnCreateDeviceResources()
{
	HRESULT hr = S_OK;

	return hr;
}

void CMSK1StatusBar::OnDiscardDeviceResources()
{
}

STDMETHODIMP CMSK1StatusBar::QueryInterface(
	REFIID   riid,
	LPVOID* ppvObj
	)
{
	if (riid == IID_IUnknown || riid == __uuidof(IMSK1StatusBarCtrl))
	{
		*ppvObj = static_cast<IMSK1StatusBarCtrl*>(this);
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

ULONG CMSK1StatusBar::Release()
{
	SAFE_RELEASE(&m_pHandler);

	// Decrement the object's internal counter.
	ULONG cRef = InterlockedDecrement(&m_cRef);

	if (cRef == 0)
	{
		delete this;
	}

	return cRef;
}

ULONG CMSK1StatusBar::AddRef()
{
	InterlockedIncrement(&m_cRef);
	return m_cRef;
}

STDMETHODIMP CMSK1StatusBar::OnProcessMessage(
	UINT msg,
	WPARAM wParam,
	LPARAM lParam,
	IMSK1Window* pWnd
	)
{
	switch(msg)
	{
	case WM_SIZE:
		InvalidateRect(m_hWnd, NULL, TRUE);
		return 0;
	case WM_ERASEBKGND:
		{
			RECT rc;
			GetClientRect(m_hWnd, &rc);

			m_pFramework->m_pD2D1RenderTarget->BindDC((HDC) wParam, &rc);
			m_pFramework->m_pD2D1RenderTarget->BeginDraw();

			// Clear Window
			m_pFramework->m_pD2D1RenderTarget->Clear(D2D1::ColorF(m_bgColor, 1.0f));

			m_pFramework->m_pD2D1RenderTarget->EndDraw();
			return -1;
		}
	default:
		CallWindowProc(m_OldWndProc, m_hWnd, msg, wParam, lParam);
	}

	return 0;
}

BOOL CMSK1StatusBar::GetBorders(
	MSK1_STATUSBAR_BORDERSIZE_U borderSizes
	)
{
	return (BOOL) SendMessage(m_hWnd, SB_GETBORDERS, NULL, (LPARAM) &borderSizes); 
}

HICON CMSK1StatusBar::GetIcon(
	UINT iPart
	)
{
	return (HICON) SendMessage(m_hWnd, SB_GETICON, iPart, NULL);
}

UINT CMSK1StatusBar::GetParts(
	UINT nParts,
	UINT* Parts
	)
{
	return SendMessage(m_hWnd, SB_GETPARTS, nParts, (LPARAM) &Parts);
}

BOOL CMSK1StatusBar::GetRect(
	UINT nPane,
	LPRECT lpRect
	)
{
	return SendMessage(m_hWnd, SB_GETRECT, nPane, (LPARAM) &lpRect);
}

UINT CMSK1StatusBar::GetText(
	LPCTSTR lpszText, 
	UINT nPane,
	UINT* pType
	)
{
	DWORD retVal = SendMessage(m_hWnd, SB_GETTEXT, nPane, (LPARAM) &lpszText);

	*pType = HIWORD(retVal);

	return LOWORD(retVal);
}

UINT CMSK1StatusBar::GetTextLength(
	UINT nPane,
	UINT* pType
	)
{
	DWORD retVal = SendMessage(m_hWnd, SB_GETTEXTLENGTH, nPane, NULL);

	*pType = HIWORD(retVal);

	return LOWORD(retVal);
}

LPCTSTR CMSK1StatusBar::GetTipText(
	UINT nPane
	)
{
	LPCTSTR str = NULL;

	UINT nBufferSize = SendMessage(m_hWnd, SB_GETTEXTLENGTH, nPane, NULL);

	SendMessage(m_hWnd, SB_GETTIPTEXT, LOWORD(nPane) | HIWORD(nBufferSize), (LPARAM) &str);

	return str;
}

BOOL CMSK1StatusBar::IsSimple(
	)
{
	return SendMessage(m_hWnd, SB_ISSIMPLE, NULL, NULL);
}

BOOL CMSK1StatusBar::SetBkColor(
	COLORREF cr,
	BOOL bRedraw
	)
{
	m_bgColor =  _byteswap_ulong(cr) >> 8;

	if (bRedraw) 
		InvalidateRect(m_hWnd, NULL, TRUE);

	return TRUE;
}

BOOL CMSK1StatusBar::SetIcon(
	UINT nPane, 
	HICON hIcon
	)
{
	return SendMessage(m_hWnd, SB_SETICON, nPane, (LPARAM) hIcon);
}

void CMSK1StatusBar::SetMinHeight(
	UINT nHeight
	)
{
	SendMessage(m_hWnd, SB_SETMINHEIGHT, nHeight, NULL);
}

BOOL CMSK1StatusBar::SetParts(
	UINT nParts,
	UINT* pWidths
	)
{
	return SendMessage(m_hWnd, SB_SETPARTS, nParts, (LPARAM) pWidths);
}

BOOL CMSK1StatusBar::SetSimple(
	BOOL bSimple
	)
{
	return SendMessage(m_hWnd, SB_SIMPLE, bSimple, NULL);
}

BOOL CMSK1StatusBar::SetText(
	LPCTSTR lpszText, 
	UINT nPane, 
	UINT nType,
	COLORREF bgColor
	)
{
	SendMessage(m_hWnd, SB_SETBKCOLOR, NULL, bgColor);

	return SendMessage(m_hWnd, SB_SETTEXT, LOBYTE(nPane) | nType, (LPARAM) lpszText);
}

void CMSK1StatusBar::SetTipText(
	int nPane, 
	LPCTSTR pszTipText 
	)
{
	SendMessage(m_hWnd, SB_SETTIPTEXT, LOBYTE(nPane), (LPARAM) pszTipText);
}