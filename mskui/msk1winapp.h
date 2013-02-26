#pragma once
#include "mskwindow.h"

class CMSK1WindowApplication : 
	public CMSK1Window
{
public:
	CMSK1WindowApplication(CMSK1Framework* pFramework);
	virtual ~CMSK1WindowApplication(void);

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

	STDMETHOD_(void, OnMove(
		int x, 
		int y
		));

	STDMETHOD_(void, OnPaint(
		const PAINTSTRUCT &ps
		));

	STDMETHOD_(void, OnGetMinMaxInfo(
		MINMAXINFO* lpMMI
		));

	STDMETHOD_(void, OnSize(
		UINT nType, 
		int cx, 
		int cy
		));

	STDMETHOD(OnCreateDeviceIndependentResources)();
	STDMETHOD(OnCreateDeviceResources)();
	STDMETHOD_(void, OnDiscardDeviceResources());
};