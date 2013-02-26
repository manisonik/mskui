#pragma once
#include "mskwindow.h"

class CMSK1ToolWindow :
	public CMSK1Window,
	public IMSK1ToolWindow
{
public:
	CMSK1ToolWindow(CMSK1Framework* pFramework);
	virtual ~CMSK1ToolWindow(void);

	STDMETHOD_(ULONG, AddRef());
	STDMETHOD_(ULONG, Release());
	STDMETHOD(QueryInterface)(
		REFIID   riid,
		LPVOID * ppvObj
		);

	STDMETHOD_(int,	OnCreate(
		LPCREATESTRUCT lpCreateStruct
		));

	STDMETHOD_(void, OnNcCalcSize(
		BOOL bCalcValidRects, 
		NCCALCSIZE_PARAMS* lpncsp
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

	STDMETHOD_(LRESULT, 
		OnNcHitTest(
		POINT pt
		));

	STDMETHOD(OnCreateDeviceIndependentResources)();
	STDMETHOD(OnCreateDeviceResources)();
	STDMETHOD_(void, OnDiscardDeviceResources());

	STDMETHOD(SetStyle)(
		MSK1_TOOLWINDOW_STYLE Style
		);
};
