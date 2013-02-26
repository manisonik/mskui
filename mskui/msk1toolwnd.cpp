#include "stdafx.h"
#include "msk1toolwnd.h"

CMSK1ToolWindow::CMSK1ToolWindow(CMSK1Framework* pFramework) : 
	CMSK1Window(pFramework)
{
	m_nCaptionHeight = 16;
	m_d2dCaptionBarColor->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
}

CMSK1ToolWindow::~CMSK1ToolWindow(void)
{
}

void CMSK1ToolWindow::OnPaint(const PAINTSTRUCT &ps)
{
	m_pFramework->m_pD2D1RenderTarget
		->BindDC(ps.hdc, &ps.rcPaint);

	m_pFramework->m_pD2D1RenderTarget
		->BeginDraw();

	m_pFramework->m_pD2D1RenderTarget
		->Clear(D2D1::ColorF(D2D1::ColorF::White));

	m_pFramework->m_pD2D1RenderTarget
		->EndDraw();
}

int	CMSK1ToolWindow::OnCreate(
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

LRESULT CMSK1ToolWindow::OnNcHitTest(POINT pt)
{
	return CMSK1Window::OnNcHitTest(pt);
}

void CMSK1ToolWindow::OnNcCalcSize(
	BOOL bCalcValidRects, 
	NCCALCSIZE_PARAMS* lpncsp
	)
{
	if (bCalcValidRects) {
		InflateRect(&lpncsp->rgrc[0], -m_nBorderSize, -m_nBorderSize);

		lpncsp->rgrc[0].left		+= m_rcMargin.left;
		lpncsp->rgrc[0].top			+= m_rcMargin.top + m_nCaptionHeight;
		lpncsp->rgrc[0].right		-= m_rcMargin.right;
		lpncsp->rgrc[0].bottom		-= m_rcMargin.bottom;
	}
}

void CMSK1ToolWindow::OnNcLButtonDblClk(
	UINT nHitTest,
	LPPOINTS pts
	)
{
}

void CMSK1ToolWindow::OnActivateApp(
	BOOL bActive,
	DWORD dwThreadID
	)
{
}

void CMSK1ToolWindow::OnNcPaint(
	HRGN hRgn
	)
{
	HRESULT hr = S_OK;
	FLOAT fBorderSizeX, fBorderSizeY;
	FLOAT fLeft, fRight, fTop, fBottom;
	FLOAT fCaptionHeight;
	FLOAT fCaptionButtonSizeX;
	FLOAT fCaptionButtonSizeY;
	HDC hdc;
	PSTR pszMem;

	// Get the window coordinates in screen coodinates
	GetWindowRect(m_hWnd, &m_rcAdjustedWindowRect);
	MapWindowRect(NULL, m_hWnd, &m_rcAdjustedWindowRect);

	// Retrieve the windows text
	int cTextLength = GetWindowTextLength(m_hWnd);

	pszMem = (PSTR) VirtualAlloc((LPVOID) NULL, 
		(DWORD) (cTextLength + 1), MEM_COMMIT, 
		PAGE_READWRITE);

	GetWindowText(m_hWnd, (LPWSTR) pszMem, cTextLength + 1);

	// Adjust the window rect to compensate for the margin
	m_rcAdjustedWindowRect.top		+= m_nBorderSize	+ m_rcMargin.top	+ m_nCaptionHeight;
	m_rcAdjustedWindowRect.bottom	+= m_rcMargin.top	+ m_nBorderSize		+ m_nCaptionHeight;
	m_rcAdjustedWindowRect.left		+= m_nBorderSize	+ m_rcMargin.left;
	m_rcAdjustedWindowRect.right	+= m_rcMargin.left	+ m_nBorderSize;

	// Convert coordinates to DIP scale
	fBorderSizeX		= PixeltoDipX(m_nBorderSize);
	fBorderSizeY		= PixeltoDipY(m_nBorderSize);
	fLeft				= PixeltoDipX(m_rcAdjustedWindowRect.left);
	fRight				= PixeltoDipX(m_rcAdjustedWindowRect.right);
	fTop				= PixeltoDipY(m_rcAdjustedWindowRect.top);
	fBottom				= PixeltoDipY(m_rcAdjustedWindowRect.bottom);
	fCaptionHeight		= PixeltoDipY(m_nCaptionHeight);
	fCaptionButtonSizeX	= PixeltoDipX(16);
	fCaptionButtonSizeY	= PixeltoDipY(16);

	if (hRgn == (HRGN) 1) {
		hdc = GetWindowDC(m_hWnd);
	} else {
		hdc = GetDCEx(
			m_hWnd, 
			hRgn, 
			DCX_WINDOW | DCX_INTERSECTRGN | DCX_CACHE
			);
	}

	m_pFramework->m_pD2D1RenderTarget 
		->BindDC(hdc, &m_rcAdjustedWindowRect);

	m_pFramework->m_pD2D1RenderTarget
		->BeginDraw();

	m_pFramework->m_pD2D1RenderTarget
		->Clear(D2D1::ColorF(D2D1::ColorF::White));

	///////////////////////////////////////////////////////////////////////////////
	// Draw Border

	D2D1_RECT_F rf = D2D1::RectF(
		fLeft,
		fTop,
		fRight - fLeft,
		fBottom - fTop
		);

	m_pFramework->m_pD2D1RenderTarget->DrawRectangle(
		&rf,
		m_d2dBorderColor,
		(m_nBorderSize << 1) / m_pFramework->m_fDIPScaleX
		);

	///////////////////////////////////////////////////////////////////////////////
	// Draw Caption Bar

	D2D1_RECT_F rf2 = D2D1::RectF(
		fLeft	+ fBorderSizeX,
		fTop	+ fBorderSizeY,
		fRight	- fLeft			- fBorderSizeX,
		fTop	+ fBorderSizeY	+ fCaptionHeight
		);

	m_pFramework->m_pD2D1RenderTarget->FillRectangle(
		&rf2,
		m_d2dCaptionBarColor
		);

	///////////////////////////////////////////////////////////////////////////////
	// Draw Caption: Text & Buttons

	D2D1_RECT_F destRect = D2D1::RectF(
		fRight	- fBorderSizeX - fCaptionButtonSizeX,
		fTop	+ fBorderSizeY,
		fRight	- fBorderSizeX,
		fTop	+ fBorderSizeY + fCaptionButtonSizeY
		);

	D2D1_RECT_F sourceRect = D2D1::RectF(
		32,
		0,
		48,
		16
		);


	m_pFramework->m_pD2D1RenderTarget
		->DrawBitmap(m_pFramework->m_pBitmapRes16, &destRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &sourceRect);


	destRect.left		-= fCaptionButtonSizeX;
	destRect.right		-= fCaptionButtonSizeX;
	sourceRect.left		-= fCaptionButtonSizeX;
	sourceRect.right	-= fCaptionButtonSizeX;

	
	m_pFramework->m_pD2D1RenderTarget
		->DrawBitmap(m_pFramework->m_pBitmapRes16, &destRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &sourceRect);

	destRect.left		-= fCaptionButtonSizeX;
	destRect.right		-= fCaptionButtonSizeX;
	sourceRect.left		-= fCaptionButtonSizeX;
	sourceRect.right	-= fCaptionButtonSizeX;
	
	m_pFramework->m_pD2D1RenderTarget
		->DrawBitmap(m_pFramework->m_pBitmapRes16, &destRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &sourceRect);

	rf2.right	= destRect.left;
	rf2.left	+= PixeltoDipX(5);

	// Draw Text
	m_pFramework->m_pD2D1RenderTarget->DrawText(
		(WCHAR*) pszMem,
		cTextLength + 1,
		m_pFramework->m_pTextFormat,
		rf2,
		m_d2dCaptionTextColor
		);

	m_pFramework->m_pD2D1RenderTarget
		->EndDraw();

	// Release Resources
	ReleaseDC(m_hWnd, hdc);
	VirtualFree(pszMem, 0, MEM_RELEASE); 
}

void CMSK1ToolWindow::OnGetMinMaxInfo(
	MINMAXINFO* lpMMI
	)
{
	RECT rc;
	SystemParametersInfo( SPI_GETWORKAREA, 0, (VOID *) &rc, 0);

	lpMMI->ptMaxSize.x = rc.right;
	lpMMI->ptMaxSize.y = rc.bottom;
	lpMMI->ptMinTrackSize.x = m_rcMargin.left + m_rcMargin.right + 55 * m_pvWindows.size();
	lpMMI->ptMinTrackSize.y = 100;
}

STDMETHODIMP CMSK1ToolWindow::OnCreateDeviceIndependentResources()
{
	return CMSK1Window::OnCreateDeviceIndependentResources();
}

STDMETHODIMP CMSK1ToolWindow::OnCreateDeviceResources()
{
	return CMSK1Window::OnCreateDeviceResources();
}

void CMSK1ToolWindow::OnDiscardDeviceResources()
{
	return CMSK1Window::OnDiscardDeviceResources();
}

STDMETHODIMP CMSK1ToolWindow::QueryInterface(
	REFIID   riid,
	LPVOID* ppvObj
	)
{
	if (riid == IID_IUnknown || riid == __uuidof(IMSK1Window))
	{
		*ppvObj = static_cast<IMSK1Window*>(this);
	}
	else if (riid == __uuidof(IMSK1CommandHandler))
	{
		*ppvObj = static_cast<IMSK1CommandHandler*>(this);
	}
	else if (riid == __uuidof(IMSK1ToolWindow))
	{
		*ppvObj = static_cast<IMSK1ToolWindow*>(this);
	}
	else 
	{
		*ppvObj = NULL;
		return E_NOINTERFACE;
	}

	AddRef();
	return S_OK;
}

ULONG CMSK1ToolWindow::Release()
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

ULONG CMSK1ToolWindow::AddRef()
{
	InterlockedIncrement(&m_cRef);
	return m_cRef;
}

STDMETHODIMP CMSK1ToolWindow::SetStyle(
	MSK1_TOOLWINDOW_STYLE Style
	)
{
	return S_OK;
}