#include "stdafx.h"
#include "msk1winapp.h"

#define CAPTION_HEIGHT 32

CMSK1WindowApplication::CMSK1WindowApplication(CMSK1Framework* pFramework) : 
	CMSK1Window(pFramework)
{ 
	m_nCaptionHeight = 32;
}


CMSK1WindowApplication::~CMSK1WindowApplication(void)
{
}

int	CMSK1WindowApplication::OnCreate(
	LPCREATESTRUCT lpCreateStruct
	)
{
	RECT rc;
	GetWindowRect(m_hWnd, &rc);

	SetWindowPos(
		m_hWnd, 
		NULL, 
		rc.left, rc.top, 
		RECTWIDTH(rc), RECTHEIGHT(rc), 
		SWP_FRAMECHANGED
		);

	return 0;
}

void CMSK1WindowApplication::OnNcCalcSize(
	BOOL bCalcValidRects, 
	NCCALCSIZE_PARAMS* lpncsp
	)
{
	if (bCalcValidRects) {
		InflateRect(&lpncsp->rgrc[0], -m_nBorderSize, -m_nBorderSize);

		lpncsp->rgrc[0].left		+= m_rcMargin.left		+ m_rcMarginOffset.left;
		lpncsp->rgrc[0].top			+= m_rcMargin.top		+ m_rcMarginOffset.top	+ CAPTION_HEIGHT;
		lpncsp->rgrc[0].right		-= m_rcMargin.right		+ m_rcMarginOffset.right;
		lpncsp->rgrc[0].bottom		-= m_rcMargin.bottom	+ m_rcMarginOffset.bottom;
	}
}

LRESULT CMSK1WindowApplication::OnNcHitTest(
	POINT pt
	)
{
	LRESULT lRet = HitTestNCA(m_hWnd, pt);

	// Determine whether the cursor is within the client area
	if (lRet == HTNOWHERE) {
		RECT rc;
		GetClientRect(m_hWnd, &rc);

		if (PtInRect(&rc, pt)){
			return HTCLIENT;
		}
	}

	return lRet;
}

void CMSK1WindowApplication::OnNcLButtonDblClk(
	UINT nHitTest,
	LPPOINTS pts
	)
{
}

void CMSK1WindowApplication::OnActivateApp(
	BOOL bActive,
	DWORD dwThreadID
	)
{
}

void CMSK1WindowApplication::OnSize(
	UINT nType, 
	int cx, 
	int cy
	)
{
	
	for (std::size_t i = 0; i < m_pvWindows.capacity(); i++)
	{
		RECT rc;
		GetWindowRect(m_hWnd, &rc);
	
		rc.left		+= m_nBorderSize;
		rc.bottom	-= m_nBorderSize;
		rc.right	-= m_nBorderSize;
		rc.top		+= m_nBorderSize;

		SetWindowPos(m_pvWindows[i]->m_hWnd, 0, rc.left, rc.bottom -  m_pvWindows[i]->m_nHeight, 
			RECTWIDTH(rc), m_pvWindows[i]->m_nHeight, SWP_DRAWFRAME);
	}
}

void CMSK1WindowApplication::OnMove(int x, int y)
{
	for (std::size_t i = 0; i < m_pvWindows.capacity(); i++)
	{
		RECT rc;
		GetWindowRect(m_hWnd, &rc);

		rc.left		+= m_nBorderSize;
		rc.bottom	-= m_nBorderSize;
		rc.right	-= m_nBorderSize;
		rc.top		+= m_nBorderSize;

		SetWindowPos(m_pvWindows[i]->m_hWnd, 0, rc.left, rc.bottom - m_pvWindows[i]->m_nHeight, 
			0, 0, SWP_DRAWFRAME | SWP_NOSIZE);
	}
}

void CMSK1WindowApplication::OnNcPaint(
	HRGN hRgn
	)
{
	HRESULT hr = S_OK;
	HDC hdc;
	RECT rcWindow;
	PSTR pszMem;

	// Get the window coordinates in screen coodinates
	GetWindowRect(m_hWnd, &rcWindow);
	MapWindowRect(NULL, m_hWnd, &rcWindow);

	// Get Windows Text
	int cTextLength = GetWindowTextLength(m_hWnd);

	pszMem = (PSTR) VirtualAlloc((LPVOID) NULL, 
		(DWORD) (cTextLength + 1), MEM_COMMIT, 
		PAGE_READWRITE);

	GetWindowText(m_hWnd, (LPWSTR) pszMem, cTextLength + 1);

	// Adjust the window rect to compensate for the margin
	rcWindow.top	+= m_nBorderSize	+ m_rcMargin.top		+ m_rcMarginOffset.top	+ CAPTION_HEIGHT;
	rcWindow.bottom += m_rcMargin.top	+ m_rcMarginOffset.top	+ m_nBorderSize			+ CAPTION_HEIGHT;
	rcWindow.left	+= m_nBorderSize	+ m_rcMargin.left		+ m_rcMarginOffset.left;
	rcWindow.right	+= m_rcMargin.left	+ m_rcMarginOffset.left + m_nBorderSize;

	if (hRgn == (HRGN) 1) {
		hdc = GetWindowDC(m_hWnd);
	} else {
		hdc = GetDCEx(
			m_hWnd, 
			hRgn, 
			DCX_WINDOW | DCX_INTERSECTRGN | DCX_CACHE
			);
	}

	m_pFramework->m_pD2D1RenderTarget->BindDC(hdc, &rcWindow);

	m_pFramework->m_pD2D1RenderTarget->BeginDraw();

	// Clear Window
	m_pFramework->m_pD2D1RenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::SteelBlue));

	// Draw border
	D2D1_RECT_F rf = D2D1::RectF(
		PixeltoDipX(rcWindow.left),
		PixeltoDipY(rcWindow.top),
		PixeltoDipX(rcWindow.right - rcWindow.left),
		PixeltoDipY(rcWindow.bottom - rcWindow.top)
	);

	m_pFramework->m_pD2D1RenderTarget->DrawRectangle(
		&rf,
		m_d2dBorderColor,
		(m_nBorderSize << 1) / m_pFramework->m_fDIPScaleX
		);

	D2D1_RECT_F rf2 = D2D1::RectF(
		PixeltoDipX(rcWindow.left + m_nBorderSize),
		PixeltoDipY(rcWindow.top + m_nBorderSize),
		PixeltoDipX(rcWindow.right - rcWindow.left - m_nBorderSize),
		PixeltoDipY(rcWindow.top + m_nBorderSize + CAPTION_HEIGHT)
		);

	m_pFramework->m_pD2D1RenderTarget->FillRectangle(
		&rf2,
		m_d2dCaptionBarColor
		);

	// Adjust to compenstate for the icon
	rf2.left += PixeltoDipX(36);
	rf2.right -= PixeltoDipX(24*3 + 3);

	D2D1_RECT_F rf3 = D2D1::RectF(
		PixeltoDipX(rcWindow.right - m_nBorderSize - 27),
		PixeltoDipY(rcWindow.top + m_nBorderSize + 3),
		PixeltoDipX(rcWindow.right - m_nBorderSize - 3),
		PixeltoDipY(rcWindow.top + m_nBorderSize + 27)
		);

	m_pFramework->m_pD2D1RenderTarget->DrawBitmap(m_pFramework->m_pBitmapClose, &rf3); 

	rf3.left -= PixeltoDipX(24);
	rf3.right -= PixeltoDipX(24);

	m_pFramework->m_pD2D1RenderTarget->DrawBitmap(m_pFramework->m_pBitmapMaximize, &rf3);

	rf3.left -= PixeltoDipX(24);
	rf3.right -= PixeltoDipX(24);

	m_pFramework->m_pD2D1RenderTarget->DrawBitmap(m_pFramework->m_pBitmapMinimize, &rf3);

	D2D1_RECT_F rf4 = D2D1::RectF(
		PixeltoDipX(rcWindow.left + m_nBorderSize + 3),
		PixeltoDipY(rcWindow.top + m_nBorderSize + 3),
		PixeltoDipX(rcWindow.left + m_nBorderSize + 27),
		PixeltoDipY(rcWindow.top + m_nBorderSize + 27)
		);

	m_pFramework->m_pD2D1RenderTarget->DrawBitmap(m_pFramework->m_pBitmapIcon, &rf4);

	m_pFramework->m_pD2D1RenderTarget->DrawText(
		(WCHAR*) pszMem,
		cTextLength + 1,
		m_pFramework->m_pTextFormat,
		rf2,
		m_d2dCaptionTextColor
		);

	m_pFramework->m_pD2D1RenderTarget->EndDraw();

	ReleaseDC(m_hWnd, hdc);

	VirtualFree(pszMem, 0, MEM_RELEASE); 
}

void CMSK1WindowApplication::OnPaint(
	const PAINTSTRUCT &ps
	)
{
	if (m_pFramework->m_pD2D1RenderTarget)
	{
		// Bind the DC to the render target.
		m_pFramework->m_pD2D1RenderTarget->BindDC(ps.hdc, &ps.rcPaint);

		m_pFramework->m_pD2D1RenderTarget->BeginDraw();
		m_pFramework->m_pD2D1RenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::SteelBlue));
		m_pFramework->m_pD2D1RenderTarget->EndDraw();
	}
}

void CMSK1WindowApplication::OnGetMinMaxInfo(
	MINMAXINFO* lpMMI
	)
{
	RECT rc = {0, 0, 0, 0};
	SystemParametersInfo( SPI_GETWORKAREA, 0, (VOID *) &rc, 0);

	lpMMI->ptMaxSize.x = rc.right;
	lpMMI->ptMaxSize.y = rc.bottom;
	lpMMI->ptMinTrackSize.x = m_rcMargin.left + m_rcMargin.right + 55 * m_pvWindows.size();
	lpMMI->ptMinTrackSize.y = 100;
}

STDMETHODIMP CMSK1WindowApplication::OnCreateDeviceIndependentResources()
{
	return CMSK1Window::OnCreateDeviceIndependentResources();
}

STDMETHODIMP CMSK1WindowApplication::OnCreateDeviceResources()
{
	return CMSK1Window::OnCreateDeviceResources();
}

void CMSK1WindowApplication::OnDiscardDeviceResources()
{
	return CMSK1Window::OnDiscardDeviceResources();
}