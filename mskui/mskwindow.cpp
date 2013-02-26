#include "StdAfx.h"
#include "resource.h"
#include "mskwindow.h"
#include "msk1winapp.h"
#include "msk1toolwnd.h"
#include "msk1button.h"
#include "msk1statusbar.h"

CMSK1Window::CMSK1Window(CMSK1Framework* pFramework) : 
	m_pHandler(NULL), 
	m_pWindow(NULL),
	m_d2dBorderColor(NULL),
	m_d2dCaptionBarColor(NULL),
	m_d2dCaptionTextColor(NULL),
	m_cRef(1),
	m_hWnd(0), 
	m_pThunk(NULL), 
	m_nBorderSize(5),
	m_wpFlags(MSK1_WINDOWPLACEMENT_NONE),
	m_nCaptionHeight(32),
	m_OldWndProc(NULL)
{
	// Store framework pointer
	m_pFramework = pFramework;

	// Zeroize
	ZeroMemory(&m_rcMargin,	sizeof(RECT));
	ZeroMemory(&m_rcAdjustedWindowRect, sizeof(RECT));
	ZeroMemory(&m_rcMarginOffset, sizeof(RECT));

	// Load Independent Device Resources
	OnCreateDeviceIndependentResources();

	// Load Device Resources
	OnCreateDeviceResources();

	// Increase Object Reference count
	InterlockedIncrement(&g_nComObjsInUse);
}

CMSK1Window::~CMSK1Window(void)
{
	// Release Interface pointer to window
	SAFE_RELEASE(&m_pWindow);

	// Delete Thunk
	SAFE_DELETE(&m_pThunk);

	// Discard Resources
	OnDiscardDeviceResources();

	// Decrease Object Count
	InterlockedDecrement(&g_nComObjsInUse);
}

STDMETHODIMP CMSK1Window::OnCreateDeviceIndependentResources()
{
	HRESULT hr = S_OK;

	return hr;
}

STDMETHODIMP CMSK1Window::OnCreateDeviceResources()
{
	HRESULT hr = S_OK;

	hr = m_pFramework->m_pD2D1RenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Black), 
		&m_d2dBorderColor
		);

	if (SUCCEEDED(hr)) {
		hr = m_pFramework->m_pD2D1RenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::CadetBlue), 
			&m_d2dCaptionBarColor
			);
	}

	if (SUCCEEDED(hr)) {
		hr = m_pFramework->m_pD2D1RenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::White), 
			&m_d2dCaptionTextColor
			);
	}

	return hr;
}

void CMSK1Window::OnDiscardDeviceResources()
{
	SAFE_RELEASE(&m_d2dBorderColor);
	SAFE_RELEASE(&m_d2dCaptionBarColor);
	SAFE_RELEASE(&m_d2dCaptionTextColor);
}

STDMETHODIMP  CMSK1Window::PlaceWindow(
		UINT id,
		MSK1_WINDOWPLACEMENT_FLAGS dock
		)
{
	return 0;
}


HINSTANCE CMSK1Window::GetModuleInstance()
{
	return HINST_THISCOMPONENT;
}

int CMSK1Window::OnCreate(LPCREATESTRUCT lpCreateStruct)
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

void CMSK1Window::OnNcCalcSize(
	BOOL bCalcValidRects,
	NCCALCSIZE_PARAMS* lpncsp
	)
{

}

LRESULT CMSK1Window::OnNcHitTest(POINT pt)
{
	return HitTestNCA(m_hWnd, pt);
}

void CMSK1Window::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
}

void CMSK1Window::OnNcPaint(HRGN hRgn) 
{
}

void CMSK1Window::OnNcMouseMove(
	UINT nHitTest,
	LPPOINTS point
	)
{
}

STDMETHODIMP CMSK1Window::OnProcessMessage(
	UINT msg,
	WPARAM wParam,
	LPARAM lParam,
	IMSK1Window* pWnd
	)
{
	HRESULT hr = S_OK;
	HDC hdc;
	PAINTSTRUCT ps;

	if (msg == WM_CREATE) {
		OnCreate(reinterpret_cast<LPCREATESTRUCT>(lParam));
	} else if (msg == WM_CREATE) {
		OnNcMouseMove(wParam, reinterpret_cast<LPPOINTS>(lParam));
	} else if (msg == WM_MOVE) {
		OnMove(LOWORD(lParam), HIWORD(lParam));
	} else if (msg == WM_SIZE) {
		OnSize(wParam, LOWORD(lParam), HIWORD(lParam));
	} else if (msg == WM_NCHITTEST) {
		POINT ptMouse = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};
		return OnNcHitTest(ptMouse);
	} else if (msg == WM_NCCALCSIZE) {
		OnNcCalcSize(wParam, reinterpret_cast<NCCALCSIZE_PARAMS*>(lParam));
	} else if (msg == WM_NCPAINT) {
		OnNcPaint((HRGN) wParam);
	} else if (msg == WM_NCRBUTTONDOWN) {
	} else if (msg == WM_PAINT) {
		hdc = BeginPaint(m_hWnd, &ps);
			OnPaint(ps);
		EndPaint(m_hWnd, &ps);
	} else if (msg == WM_NCLBUTTONDBLCLK) {
		//OnNcLButtonDblClk(wParam, reinterpret_cast<LPPOINTS>(lParam));
	} else if (msg == WM_GETMINMAXINFO) {
		OnGetMinMaxInfo(reinterpret_cast<LPMINMAXINFO> (lParam));
	} else if (msg == WM_LBUTTONDOWN) {
		OnLButtonDown(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
	} else if (msg == WM_DRAWITEM) {
		OnDrawItem((LPDRAWITEMSTRUCT)lParam);
	}

	// Call the User's OnProcessMessage; m_pHandler is passed onto OnCreateCommand
	if (m_pHandler) {
		m_pHandler->OnProcessMessage(msg, wParam, lParam, m_pWindow);
	}

	// Add error support here.

	return hr;
}

void CMSK1Window::OnDrawItem(
	LPDRAWITEMSTRUCT lpDIS
	)
{
	m_pFramework->m_pD2D1RenderTarget->BindDC(lpDIS->hDC, &lpDIS->rcItem);

	m_pFramework->m_pD2D1RenderTarget->BeginDraw();

	m_pFramework->m_pD2D1RenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::CadetBlue));

	D2D1_RECT_F rf = D2D1::RectF(
		PixeltoDipX(lpDIS->rcItem.left),
		PixeltoDipY(lpDIS->rcItem.top),
		PixeltoDipX(lpDIS->rcItem.right),
		PixeltoDipY(lpDIS->rcItem.bottom)
		);

	m_pFramework->m_pD2D1RenderTarget->DrawText(
		(LPCWSTR) lpDIS->itemData,
		wcslen((WCHAR*) lpDIS->itemData) + 1,
		m_pFramework->m_pTextFormat,
		rf,
		m_d2dCaptionTextColor
		);

	m_pFramework->m_pD2D1RenderTarget->EndDraw();
}

// Hit test the frame for resizing and moving.
LRESULT CMSK1Window::HitTestNCA(HWND hWnd, const POINT& ptMouse)
{
	// Get the window rectangle.
	RECT rcWindow;
	GetWindowRect(hWnd, &rcWindow);

	// Determine if the hit test is for resizing. Default middle (1,1).
	USHORT uRow = 1; USHORT uCol = 1; bool fOnResizeBorder = false;

	// Determine if the point is at the top or bottom of the window.
	if (ptMouse.y >= rcWindow.top && ptMouse.y < rcWindow.top + (m_nCaptionHeight + m_nBorderSize)) {
		fOnResizeBorder = (ptMouse.y < (rcWindow.top + m_nBorderSize));
		uRow = 0;
	} else if (ptMouse.y < rcWindow.bottom && ptMouse.y >= rcWindow.bottom - m_nBorderSize){
		uRow = 2;
	}

	// Determine if the point is at the left or right of the window.
	if (ptMouse.x >= rcWindow.left && ptMouse.x < rcWindow.left + m_nBorderSize) {
		uCol = 0; // left side
	}
	else if (ptMouse.x < rcWindow.right && ptMouse.x >= rcWindow.right - m_nBorderSize) {
		uCol = 2; // right side
	}

	// Adjust client rect for new client area
	rcWindow.left	+= m_nBorderSize + m_rcMargin.left	 + m_rcMarginOffset.left;
	rcWindow.right	-= m_nBorderSize + m_rcMargin.right  + m_rcMarginOffset.right;
	rcWindow.top	+= m_nBorderSize + m_rcMargin.top	 + m_rcMarginOffset.top + m_nCaptionHeight;
	rcWindow.bottom	-= m_nBorderSize + m_rcMargin.bottom + m_rcMarginOffset.bottom;

	// Determine if the point is in the client area
	if (PtInRect(&rcWindow, ptMouse)) {
		return HTCLIENT;
	}

	LRESULT hitTests[3][3] = 
	{
		{ HTTOPLEFT,    fOnResizeBorder ? HTTOP : HTCAPTION,    HTTOPRIGHT },
		{ HTLEFT,       HTNOWHERE,     HTRIGHT },
		{ HTBOTTOMLEFT, HTBOTTOM, HTBOTTOMRIGHT },
	};

	return hitTests[uRow][uCol];
}

void CMSK1Window::OnLButtonDown(
	UINT nFlags,
	int x,
	int y
	)
{

}

void CMSK1Window::OnNcLButtonDblClk(
	UINT nHitTest,
	LPPOINTS pts
	)
{

}

FLOAT CMSK1Window::PixeltoDipX(int x)
{
	return static_cast<FLOAT>(x) / m_pFramework->m_fDIPScaleX;
}

FLOAT CMSK1Window::PixeltoDipY(int y)
{
	return static_cast<FLOAT>(y) / m_pFramework->m_fDIPScaleY;
}

void CMSK1Window::OnMove(int x, int y)
{
	InvalidateRect(m_hWnd, NULL, TRUE);
}

STDMETHODIMP CMSK1Window::QueryInterface(
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
	else 
	{
		*ppvObj = NULL;
		return E_NOINTERFACE;
	}

	AddRef();
	return S_OK;
}

ULONG CMSK1Window::Release()
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

ULONG CMSK1Window::AddRef()
{
	InterlockedIncrement(&m_cRef);
	return m_cRef;
}

HRESULT CMSK1Window::AddToolTip(
	HWND hWndTarget,
	LPWSTR lpszText,
	BOOL bBallon
	)
{
	HWND hWndToolTip = CreateWindowEx(0, TOOLTIPS_CLASS, NULL, WS_POPUP, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, hWndTarget, NULL, HINST_THISCOMPONENT, NULL);

	// Associate the tooltip with the tool.
	TOOLINFO toolInfo = { 0 };
	toolInfo.cbSize = sizeof(toolInfo);
	toolInfo.hwnd = hWndTarget;
	toolInfo.uFlags = TTF_IDISHWND | TTF_SUBCLASS;
	toolInfo.uId = (UINT_PTR) hWndTarget;
	toolInfo.lpszText = lpszText;

	SendMessage(hWndToolTip, TTM_ACTIVATE,TRUE,0);
	SendMessage(hWndToolTip, TTM_ADDTOOL, 0, (LPARAM)&toolInfo);

	return S_OK;
}

HRESULT CMSK1Window::SuperclassWindow(
	LPCWSTR className, 
	LPCWSTR superClassName, 
	CMSK1Window* pWindow
	) 
{
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(WNDCLASS));

	GetClassInfo(NULL, className, &wc);
	pWindow->m_OldWndProc = wc.lpfnWndProc;

	wc.style = 0;
	wc.hInstance = NULL;
	wc.lpszClassName = superClassName;
	wc.lpfnWndProc = StartWindowProc;

	RegisterClass(&wc);

	return S_OK;
}

HWND CMSK1Window::GetWindowHandle()
{
	return m_hWnd;
}

LRESULT CMSK1Window::StartWindowProc(
	HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam
	)
{
	WNDPROC pProc;
	CMSK1Window* pWindow;

	if (msg == WM_NCCREATE) {
		// Get the "this" pointer from the call CreateWindow(...)
		LPCREATESTRUCT createStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);  
		pWindow = reinterpret_cast<CMSK1Window*>(createStruct->lpCreateParams);

		if (pWindow)
		{
			// Initalize thunk && store handle
			pWindow->m_pThunk = new STDCALLTHUNK();
			pWindow->m_pThunk->Init((DWORD) Router, pWindow);
			pWindow->m_hWnd = hWnd;

			// Obtain a pointer to IMSKWindow interface
			pWindow->QueryInterface(IID_PPV_ARGS(&pWindow->m_pWindow));

			// Set the thunk procedure
			pProc = (WNDPROC) pWindow->m_pThunk;

			// Set the window's procedure
			SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG)pProc);

			// Finally, call the thunk procedure
			return pProc(hWnd, msg, wParam, lParam);
		}
	}

	// Return the DefWindowProc
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

STDMETHODIMP CMSK1Window::SetMargin(
	MSK1_MARGIN_U margin
	)
{
	m_rcMargin.left		= margin.left;
	m_rcMargin.right	= margin.right;
	m_rcMargin.top		= margin.top;
	m_rcMargin.bottom	= margin.bottom;

	return S_OK;
}

void CMSK1Window::OnPaint(const PAINTSTRUCT &ps)
{
	if (m_pFramework->m_pD2D1RenderTarget)
	{
		// Bind the DC to the render target.
		m_pFramework->m_pD2D1RenderTarget->BindDC(ps.hdc, &ps.rcPaint);

		m_pFramework->m_pD2D1RenderTarget->BeginDraw();
		m_pFramework->m_pD2D1RenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::AliceBlue));
		m_pFramework->m_pD2D1RenderTarget->EndDraw();
	}
}

void CMSK1Window::OnActivateApp(
	BOOL bActive,
	DWORD dwThreadID
	)
{
	if (bActive) {
	}
}

STDMETHODIMP CMSK1Window::SetBorder(
	D2D1_COLOR_F color,
	LONG size
	)
{
	// Set Border Size
	m_nBorderSize = size;

	// Set Border Color
	m_d2dBorderColor->SetColor(color);

	return S_OK;
}

void CMSK1Window::OnSize(
	UINT nType, 
	int cx, 
	int cy
	)
{
}

LRESULT CMSK1Window::Router(
	HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam
	)
{
	HRESULT hr = S_OK;

	CMSK1Window* pWindow = (CMSK1Window*) hWnd;

	hr = pWindow->OnProcessMessage(msg, wParam, lParam, pWindow->m_pWindow);

	return (hr) ? hr : DefWindowProc(pWindow->m_hWnd, msg, wParam, lParam);
}

STDMETHODIMP CMSK1Window::CreateStatusBar(
	MSK1_POINT_U position,
	MSK1_SIZE_U size,
	MSK1_SBARSTYLE_FLAGS sbarStyle,
	MSK1_WINDOWPLACEMENT_FLAGS dockType,
	IMSK1StatusBarCtrl** ppStatusbarCtrl
	)
{
	CMSK1StatusBar* pStatusBar = new CMSK1StatusBar(m_pFramework);
	pStatusBar->m_nWidth	= size.width;
	pStatusBar->m_nHeight	= size.height;

	// Superclass window
	SuperclassWindow(STATUSCLASSNAME, L"SC_STATUSBAR", pStatusBar);

	// Create the statusbar
	HWND hWndStatus = CreateWindowEx(0, L"SC_STATUSBAR", L"", WS_POPUP | WS_VISIBLE,
		0, 0, 0, 0, m_hWnd, 0, NULL, pStatusBar);

	// Disable Themes
	SetWindowTheme (hWndStatus, L"", L"");

	// Adjust non-client area
	m_rcMarginOffset.bottom += size.height;

	// Set initialize size
	SendMessage(hWndStatus, SB_SETMINHEIGHT, size.height, 0);

	m_pvWindows.push_back(pStatusBar);

	// Return pointer to user
	*ppStatusbarCtrl = pStatusBar;

	return S_OK;
}

STDMETHODIMP CMSK1Window::CreateScrollBar(
	MSK1_POINT_U position,
	MSK1_SIZE_U size,
	MSK1_SBSTYLE_FLAGS sbStyle,
	MSK1_WINDOWPLACEMENT_FLAGS dockType,
	IMSK1ScrollBarCtrl** ppScrollbarCtrl
	)
{
	return S_OK;
}

STDMETHODIMP CMSK1Window::CreateProgressBar(
	MSK1_POINT_U position,
	MSK1_SIZE_U size,
	MSK1_PBSTYLE_FLAGS pbStyle,
	MSK1_WINDOWPLACEMENT_FLAGS dockType,
	IMSK1ProgressBarCtrl** ppProgressBarCtrl
	)
{
	return S_OK;
}

STDMETHODIMP CMSK1Window::CreateReBar(
	MSK1_POINT_U position,
	MSK1_SIZE_U size,
	MSK1_RBSTYLE_FLAGS rbStyle,
	MSK1_WINDOWPLACEMENT_FLAGS dockType,
	IMSK1ReBarCtrl** ppReBarCtrl
	)
{
	return S_OK;
}

STDMETHODIMP CMSK1Window::CreateToolBar(
	MSK1_POINT_U position,
	MSK1_SIZE_U size,
	MSK1_TBSTYLE_FLAGS tbStyle,
	MSK1_WINDOWPLACEMENT_FLAGS dockType,
	IMSK1ToolBarCtrl** ppToolBarCtrl
	)
{
	return S_OK;
}

STDMETHODIMP CMSK1Window::CreateTextBox(
	MSK1_POINT_U position,
	MSK1_SIZE_U size,
	MSK1_ESTYLE_FLAGS eStyle,
	MSK1_WINDOWPLACEMENT_FLAGS dockType,
	IMSK1TextBoxCtrl** ppTextBoxCtrl
	)
{
	return S_OK;
}

STDMETHODIMP CMSK1Window::CreateListBox(
	MSK1_POINT_U position,
	MSK1_SIZE_U size,
	MSK1_LBSTYLE_FLAGS lbStyle,
	MSK1_WINDOWPLACEMENT_FLAGS dockType,
	IMSK1ListBoxCtrl** ppListBoxCtrl
	)
{
	return S_OK;
}

STDMETHODIMP CMSK1Window::CreateComboBox(
	MSK1_POINT_U position,
	MSK1_SIZE_U size,
	MSK1_CBSTYLE_FLAGS cbStyle,
	MSK1_WINDOWPLACEMENT_FLAGS dockType,
	IMSK1ComboBoxCtrl** ppComboBoxCtrl
	)
{
	return S_OK;
}

STDMETHODIMP CMSK1Window::CreateRichTextBox(
	MSK1_POINT_U position,
	MSK1_SIZE_U size,
	MSK1_RESTYLE_FLAGS reStyle,
	MSK1_WINDOWPLACEMENT_FLAGS dockType,
	IMSK1RichTextBoxCtrl** ppRichTextBoxCtrl
	)
{
	return S_OK;
}

STDMETHODIMP CMSK1Window::CreateTabView(
	MSK1_POINT_U position,
	MSK1_SIZE_U size,
	MSK1_RESTYLE_FLAGS reStyle,
	MSK1_WINDOWPLACEMENT_FLAGS dockType,
	IMSK1TabViewCtrl** ppTabViewCtrl
	)
{
	return S_OK;
}

STDMETHODIMP CMSK1Window::CreateTreeView(
	MSK1_POINT_U position,
	MSK1_SIZE_U size,
	MSK1_TVSTYLE_FLAGS tvStyle,
	MSK1_WINDOWPLACEMENT_FLAGS dockType,
	IMSK1TreeViewCtrl** ppTreeViewCtrl
	)
{
	return S_OK;
}

STDMETHODIMP CMSK1Window::CreatePropertySheetDialog(
	MSK1_POINT_U position,
	MSK1_SIZE_U size,
	IMSK1PropertySheetDialog** ppPropertySheetDialog
	)
{
	return S_OK;
}

STDMETHODIMP CMSK1Window::CreateTaskDialog(
	MSK1_POINT_U position,
	MSK1_SIZE_U size,
	IMSK1TaskDialog** ppTaskDialog
	)
{
	return S_OK;
}

STDMETHODIMP CMSK1Window::CreateDateTimePicker(
	MSK1_POINT_U position,
	MSK1_SIZE_U size,
	MSK1_DTSTYLE_FLAGS dtStyle,
	MSK1_WINDOWPLACEMENT_FLAGS dockType,
	IMSK1DateTimePickerCtrl** ppDateTimePickerCtrl
	)
{
	return S_OK;
}

STDMETHODIMP CMSK1Window::CreateHeader(
	MSK1_POINT_U position,
	MSK1_SIZE_U size,
	MSK1_HDSTYLE_FLAGS hdStyle,
	MSK1_WINDOWPLACEMENT_FLAGS dockType,
	IMSK1HeaderCtrl** ppHeaderCtrl
	)
{
	return S_OK;
}

STDMETHODIMP CMSK1Window::CreateAnimation(
	MSK1_POINT_U position,
	MSK1_SIZE_U size,
	MSK1_ANISTYLE_FLAGS aniStyle,
	MSK1_WINDOWPLACEMENT_FLAGS dockType,
	IMSK1AnimationCtrl** ppAnimationCtrl
	)
{
	return S_OK;
}

STDMETHODIMP CMSK1Window::CreateUpDown(
	MSK1_POINT_U position,
	MSK1_SIZE_U size,
	MSK1_UDSTYLE_FLAGS udStyle,
	MSK1_WINDOWPLACEMENT_FLAGS dockType,
	IMSK1UpDownCtrl** ppUpDownCtrl
	)
{
	return S_OK;
}

STDMETHODIMP CMSK1Window::CreateButton(
	MSK1_POINT_U position,
	MSK1_SIZE_U size,
	MSK1_BTNSTYLE_FLAGS btnStyle,
	MSK1_WINDOWPLACEMENT_FLAGS dockType,
	IMSK1ButtonCtrl** ppButtonCtrl
	)
{

	CMSK1Button* pButton = new CMSK1Button(m_pFramework);
	pButton->m_nWidth	= size.width;
	pButton->m_nHeight	= size.height;

	// Superclass window
	SuperclassWindow(WC_BUTTON, L"SC_BUTTON", pButton);

	HWND hWndButton = CreateWindowEx(0, L"SC_BUTTON", L"Test", WS_CHILD | WS_VISIBLE, 
		0, 0, size.width, size.height, m_hWnd, 0, HINST_THISCOMPONENT, pButton);

	// Add tooltip
	AddToolTip(hWndButton, L"This is a button control.", FALSE);

	m_pvWindows.push_back(pButton);

	// Return pointer to user
	*ppButtonCtrl = pButton;

	return S_OK;
}

STDMETHODIMP CMSK1Window::CreateMonthCalendar(
	MSK1_POINT_U position,
	MSK1_SIZE_U size,
	MSK1_MCSTYLE_FLAGS mcStyle,
	MSK1_WINDOWPLACEMENT_FLAGS dockType,
	IMSK1MonthCalendarCtrl** ppMonthCalendarCtrl
	)
{
	return S_OK;
}

STDMETHODIMP CMSK1Window::CreateToolTip(
	MSK1_POINT_U position,
	MSK1_SIZE_U size,
	MSK1_TTSTYLE_FLAGS ttStyle,
	MSK1_WINDOWPLACEMENT_FLAGS dockType,
	IMSK1ToolTipCtrl** ppToolTipCtrl
	)
{
	return S_OK;
}

STDMETHODIMP CMSK1Window::CreateHotKey(
	MSK1_POINT_U position,
	MSK1_SIZE_U size,
	IMSK1HotKeyCtrl** ppHotKeyCtrl
	)
{
	return S_OK;
}

STDMETHODIMP CMSK1Window::CreateImageList(
	MSK1_POINT_U position,
	MSK1_SIZE_U size,
	IMSK1ImageListCtrl** ppImageListCtrl
	)
{
	return S_OK;
}

STDMETHODIMP CMSK1Window::CreatePager(
	MSK1_POINT_U position,
	MSK1_SIZE_U size,
	MSK1_PGSTYLE_FLAGS pgrStyle,
	MSK1_WINDOWPLACEMENT_FLAGS dockType,
	IMSK1PagerCtrl** ppPagerCtrl
	)
{
	return S_OK;
}

STDMETHODIMP CMSK1Window::CreateStatic(
	MSK1_POINT_U position,
	MSK1_SIZE_U size,
	MSK1_WINDOWPLACEMENT_FLAGS dockType,
	IMSK1StaticCtrl** ppStaticCtrl
	)
{
	return S_OK;
}

STDMETHODIMP CMSK1Window::CreateSysLink(
	MSK1_POINT_U position,
	MSK1_SIZE_U size,
	IMSK1SysLinkCtrl** ppSysLinkCtrl
	)
{
	return S_OK;
}

STDMETHODIMP CMSK1Window::CreateTrackBar(
	MSK1_POINT_U position,
	MSK1_SIZE_U size,
	MSK1_TKBSTYLE_FLAGS tkbStyle,
	MSK1_WINDOWPLACEMENT_FLAGS wpFlags,
	IMSK1TrackBarCtrl** ppTrackBarCtrl
	)
{
	return S_OK;
}

STDMETHODIMP CMSK1Window::CreateToolWindow(
	MSK1_POINT_U position,
	MSK1_SIZE_U size,
	MSK1_WINDOWPLACEMENT_FLAGS wpFlags,
	IMSK1ToolWindow** ppToolWindowCtrl
	)
{
	CMSK1ToolWindow* pToolWnd = new CMSK1ToolWindow(m_pFramework);
	pToolWnd->m_wpFlags		= wpFlags;
	pToolWnd->m_nWidth		= size.width;
	pToolWnd->m_nHeight		= size.height;

	CreateWindowEx(WS_EX_TOOLWINDOW, L"MSK1_WINDOW_CLASS", L"Tool Window", WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, m_hWnd, 0, HINST_THISCOMPONENT, pToolWnd);

	// Insert window
	m_pvWindows.push_back(pToolWnd);

	// Return pointer to client
	*ppToolWindowCtrl = pToolWnd;

	return S_OK;
}