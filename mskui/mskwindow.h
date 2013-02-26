#pragma once
#include "msk1.h"
#include "mskhelper.h"
#include "mskframework.h"

// Foward Declaration
class CMSK1Framework;

using namespace std;

class CMSK1Window :
	public virtual IMSK1Window,
	public IMSK1CommandHandler
{
public:
	CMSK1Window(CMSK1Framework* pFramework);
	~CMSK1Window(void);

	// IUnknown Methods
	STDMETHOD_(ULONG, AddRef());

	STDMETHOD_(ULONG, Release());

	STDMETHOD(QueryInterface)(
		REFIID   riid,
		LPVOID * ppvObj
		);

	// IMSKWindow
	STDMETHOD(CreateStatusBar)(
		MSK1_POINT_U position,
		MSK1_SIZE_U size,
		MSK1_SBARSTYLE_FLAGS sbarStyle,
		MSK1_WINDOWPLACEMENT_FLAGS dockType,
		IMSK1StatusBarCtrl** ppStatusbarCtrl
		);

	STDMETHOD(CreateScrollBar)(
		MSK1_POINT_U position,
		MSK1_SIZE_U size,
		MSK1_SBSTYLE_FLAGS sbStyle,
		MSK1_WINDOWPLACEMENT_FLAGS dockType,
		IMSK1ScrollBarCtrl** ppScrollbarCtrl
		);

	STDMETHOD(CreateProgressBar)(
		MSK1_POINT_U position,
		MSK1_SIZE_U size,
		MSK1_PBSTYLE_FLAGS pbStyle,
		MSK1_WINDOWPLACEMENT_FLAGS dockType,
		IMSK1ProgressBarCtrl** ppProgressBarCtrl
		);

	STDMETHOD(CreateReBar)(
		MSK1_POINT_U position,
		MSK1_SIZE_U size,
		MSK1_RBSTYLE_FLAGS rbStyle,
		MSK1_WINDOWPLACEMENT_FLAGS dockType,
		IMSK1ReBarCtrl** ppReBarCtrl
		);

	STDMETHOD(CreateToolBar)(
		MSK1_POINT_U position,
		MSK1_SIZE_U size,
		MSK1_TBSTYLE_FLAGS tbStyle,
		MSK1_WINDOWPLACEMENT_FLAGS dockType,
		IMSK1ToolBarCtrl** ppToolBarCtrl
		);

	STDMETHOD(CreateTextBox)(
		MSK1_POINT_U position,
		MSK1_SIZE_U size,
		MSK1_ESTYLE_FLAGS eStyle,
		MSK1_WINDOWPLACEMENT_FLAGS dockType,
		IMSK1TextBoxCtrl** ppTextBoxCtrl
		);

	STDMETHOD(CreateListBox)(
		MSK1_POINT_U position,
		MSK1_SIZE_U size,
		MSK1_LBSTYLE_FLAGS lbStyle,
		MSK1_WINDOWPLACEMENT_FLAGS dockType,
		IMSK1ListBoxCtrl** ppListBoxCtrl
		);

	STDMETHOD(CreateComboBox)(
		MSK1_POINT_U position,
		MSK1_SIZE_U size,
		MSK1_CBSTYLE_FLAGS cbStyle,
		MSK1_WINDOWPLACEMENT_FLAGS dockType,
		IMSK1ComboBoxCtrl** ppComboBoxCtrl
		);

	STDMETHOD(CreateRichTextBox)(
		MSK1_POINT_U position,
		MSK1_SIZE_U size,
		MSK1_RESTYLE_FLAGS reStyle,
		MSK1_WINDOWPLACEMENT_FLAGS dockType,
		IMSK1RichTextBoxCtrl** ppRichTextBoxCtrl
		);

	STDMETHOD(CreateTabView)(
		MSK1_POINT_U position,
		MSK1_SIZE_U size,
		MSK1_RESTYLE_FLAGS reStyle,
		MSK1_WINDOWPLACEMENT_FLAGS dockType,
		IMSK1TabViewCtrl** ppTabViewCtrl
		);

	STDMETHOD(CreateTreeView)(
		MSK1_POINT_U position,
		MSK1_SIZE_U size,
		MSK1_TVSTYLE_FLAGS tvStyle,
		MSK1_WINDOWPLACEMENT_FLAGS dockType,
		IMSK1TreeViewCtrl** ppTreeViewCtrl
		);

	STDMETHOD(CreatePropertySheetDialog)(
		MSK1_POINT_U position,
		MSK1_SIZE_U size,
		IMSK1PropertySheetDialog** ppPropertySheetDialog
		);

	STDMETHOD(CreateTaskDialog)(
		MSK1_POINT_U position,
		MSK1_SIZE_U size,
		IMSK1TaskDialog** ppTaskDialog
		);

	STDMETHOD(CreateDateTimePicker)(
		MSK1_POINT_U position,
		MSK1_SIZE_U size,
		MSK1_DTSTYLE_FLAGS dtStyle,
		MSK1_WINDOWPLACEMENT_FLAGS dockType,
		IMSK1DateTimePickerCtrl** ppDateTimePickerCtrl
		);

	STDMETHOD(CreateHeader)(
		MSK1_POINT_U position,
		MSK1_SIZE_U size,
		MSK1_HDSTYLE_FLAGS hdStyle,
		MSK1_WINDOWPLACEMENT_FLAGS dockType,
		IMSK1HeaderCtrl** ppHeaderCtrl
		);

	STDMETHOD(CreateAnimation)(
		MSK1_POINT_U position,
		MSK1_SIZE_U size,
		MSK1_ANISTYLE_FLAGS aniStyle,
		MSK1_WINDOWPLACEMENT_FLAGS dockType,
		IMSK1AnimationCtrl** ppAnimationCtrl
		);

	STDMETHOD(CreateUpDown)(
		MSK1_POINT_U position,
		MSK1_SIZE_U size,
		MSK1_UDSTYLE_FLAGS udStyle,
		MSK1_WINDOWPLACEMENT_FLAGS dockType,
		IMSK1UpDownCtrl** ppUpDownCtrl
		);

	STDMETHOD(CreateButton)(
		MSK1_POINT_U position,
		MSK1_SIZE_U size,
		MSK1_BTNSTYLE_FLAGS btnStyle,
		MSK1_WINDOWPLACEMENT_FLAGS dockType,
		IMSK1ButtonCtrl** ppButtonCtrl
		);

	STDMETHOD(CreateMonthCalendar)(
		MSK1_POINT_U position,
		MSK1_SIZE_U size,
		MSK1_MCSTYLE_FLAGS mcStyle,
		MSK1_WINDOWPLACEMENT_FLAGS dockType,
		IMSK1MonthCalendarCtrl** ppMonthCalendarCtrl
		);

	STDMETHOD(CreateToolTip)(
		MSK1_POINT_U position,
		MSK1_SIZE_U size,
		MSK1_TTSTYLE_FLAGS ttStyle,
		MSK1_WINDOWPLACEMENT_FLAGS dockType,
		IMSK1ToolTipCtrl** ppToolTipCtrl
		);

	STDMETHOD(CreateHotKey)(
		MSK1_POINT_U position,
		MSK1_SIZE_U size,
		IMSK1HotKeyCtrl** ppHotKeyCtrl
		);

	STDMETHOD(CreateImageList)(
		MSK1_POINT_U position,
		MSK1_SIZE_U size,
		IMSK1ImageListCtrl** ppImageListCtrl
		);

	STDMETHOD(CreatePager)(
		MSK1_POINT_U position,
		MSK1_SIZE_U size,
		MSK1_PGSTYLE_FLAGS pgrStyle,
		MSK1_WINDOWPLACEMENT_FLAGS dockType,
		IMSK1PagerCtrl** ppPagerCtrl
		);

	STDMETHOD(CreateStatic)(
		MSK1_POINT_U position,
		MSK1_SIZE_U size,
		MSK1_WINDOWPLACEMENT_FLAGS dockType,
		IMSK1StaticCtrl** ppStaticCtrl
		);

	STDMETHOD(CreateSysLink)(
		MSK1_POINT_U position,
		MSK1_SIZE_U size,
		IMSK1SysLinkCtrl** ppSysLinkCtrl
		);

	STDMETHOD(CreateTrackBar)(
		MSK1_POINT_U position,
		MSK1_SIZE_U size,
		MSK1_TKBSTYLE_FLAGS tkbStyle,
		MSK1_WINDOWPLACEMENT_FLAGS dockType,
		IMSK1TrackBarCtrl** ppTrackBarCtrl
		);

	STDMETHOD(CreateToolWindow)(
		MSK1_POINT_U position,
		MSK1_SIZE_U size,
		MSK1_WINDOWPLACEMENT_FLAGS wpFlags,
		IMSK1ToolWindow** ppToolWindowCtrl
		);

	STDMETHOD(PlaceWindow)(
		UINT id,
		MSK1_WINDOWPLACEMENT_FLAGS dock
		);

	STDMETHOD_(HINSTANCE, GetModuleInstance());

	STDMETHOD_(HWND, GetWindowHandle());

	STDMETHOD(SetMargin)(
		MSK1_MARGIN_U margin
		);

	STDMETHOD(SetBorder)(
		D2D1_COLOR_F color,
		LONG size
		);

	STDMETHOD_(FLOAT, PixeltoDipX(int x));

	STDMETHOD_(FLOAT, PixeltoDipY(int y));

	// IMSKControlHandler Methods
	STDMETHOD(OnProcessMessage)(
		UINT msg,
		WPARAM wParam,
		LPARAM lParam,
		IMSK1Window* pWnd
		);

	// CMSKWindow Methods
	static LRESULT CALLBACK Router(
		HWND hWnd,
		UINT msg,
		WPARAM wParam,
		LPARAM lParam
		);

	static LRESULT CALLBACK StartWindowProc(
		HWND hWnd,
		UINT msg,
		WPARAM wParam,
		LPARAM lParam
		);

	static HRESULT SuperclassWindow(
		LPCWSTR className, 
		LPCWSTR superClassName, 
		CMSK1Window* pWindow
		);

	static HRESULT AddToolTip(
		HWND hWndTarget,
		LPWSTR lpszText,
		BOOL bBallon
		);

	LRESULT HitTestNCA(
		HWND hWnd, 
		const POINT& ptMouse
		);

	STDMETHOD_(void, OnSize(
		UINT nType, 
		int cx, 
		int cy
		));

	STDMETHOD_(void, OnLButtonDown(
		UINT nFlags,
		int x,
		int y
		));

	STDMETHOD_(void, OnMove(
		int x, 
		int y
		));

	STDMETHOD_(void, OnDrawItem(
		LPDRAWITEMSTRUCT lpDIS
		));

	STDMETHOD_(int,	OnCreate(
		LPCREATESTRUCT lpCreateStruct
		));

	STDMETHOD_(void, OnNcCalcSize(
		BOOL bCalcValidRects, 
		NCCALCSIZE_PARAMS* lpncsp
		));

	STDMETHOD_(LRESULT, 
		OnNcHitTest(
		POINT pt
		));

	STDMETHOD_(void, 
		OnNcLButtonDblClk(
		UINT nHitTest,
		LPPOINTS pts
		));

	STDMETHOD_(void, 
		OnActivateApp(
		BOOL bActive,
		DWORD dwThreadID
		));

	STDMETHOD_(void, OnNcPaint(
		HRGN hRgn
		));

	STDMETHOD_(void, OnPaint(
		const PAINTSTRUCT &ps
		));

	STDMETHOD_(void, OnGetMinMaxInfo(
		MINMAXINFO* lpMMI
		));

	STDMETHOD_(void, OnNcMouseMove(
		UINT nHitTest,
		LPPOINTS point
		));

	STDMETHOD(OnCreateDeviceIndependentResources)();

	STDMETHOD(OnCreateDeviceResources)();

	STDMETHOD_(void, OnDiscardDeviceResources());

	CMSK1Framework*				m_pFramework;
	IMSK1CommandHandler*		m_pHandler;
	IMSK1Window*				m_pWindow;
	ID2D1SolidColorBrush*		m_d2dBorderColor;
	ID2D1SolidColorBrush*		m_d2dCaptionBarColor;
	ID2D1SolidColorBrush*		m_d2dCaptionTextColor;
	MSK1_WINDOWPLACEMENT_FLAGS	m_wpFlags;
	RECT						m_rcAdjustedWindowRect;
	RECT						m_rcMargin;
	RECT						m_rcMarginOffset;
	HWND						m_hWnd;
	LONG						m_nBorderSize;
	LONG						m_nCaptionHeight;
	LONG						m_nWidth;
	LONG						m_nHeight;
	WNDPROC						m_OldWndProc;

	vector<CMSK1Window*>		m_pvWindows;
	STDCALLTHUNK*				m_pThunk;
	LONG						m_cRef;
};

