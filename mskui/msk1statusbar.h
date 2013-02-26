#pragma once
#include "mskwindow.h"

class CMSK1StatusBar :
	public CMSK1Window,
	public IMSK1StatusBarCtrl
{
public:
	CMSK1StatusBar(CMSK1Framework* pFramework);
	virtual ~CMSK1StatusBar(void);

	STDMETHOD_(ULONG, AddRef());
	STDMETHOD_(ULONG, Release());
	STDMETHOD(QueryInterface)(
		REFIID   riid,
		LPVOID * ppvObj
		);

	// IMSK1CommandHandler
	STDMETHOD(OnProcessMessage)(
		UINT msg,
		WPARAM wParam,
		LPARAM lParam,
		IMSK1Window* pWnd
		);

	STDMETHOD_(BOOL, GetBorders(
		MSK1_STATUSBAR_BORDERSIZE_U borderSizes
		));

	STDMETHOD_(HICON, GetIcon(
		UINT iPart
		));

	STDMETHOD_(UINT, GetParts(
		UINT nParts,
		UINT* Parts
		));

	STDMETHOD_(BOOL, GetRect(
		UINT nPane,
		LPRECT lpRect
		));

	STDMETHOD_(UINT, GetText(
		LPCTSTR lpszText, 
		UINT nPane,
		UINT* pType = NULL
		));

	STDMETHOD_(UINT, GetTextLength(
		UINT nPane,
		UINT* pType = NULL
		));

	STDMETHOD_(LPCTSTR, GetTipText(
		UINT nPane
		));

	STDMETHOD_(BOOL, IsSimple(
		));

	STDMETHOD_(BOOL, SetBkColor(
		COLORREF cr,
		BOOL bRedraw = FALSE
		));

	STDMETHOD_(BOOL, SetIcon(
		UINT nPane, 
		HICON hIcon
		));

	STDMETHOD_(void, SetMinHeight(
		UINT nHeight
		));

	STDMETHOD_(BOOL, SetParts(
		UINT nParts, 
		UINT* pWidths
		));

	STDMETHOD_(BOOL, SetSimple(
		BOOL bSimple = TRUE
		));

	STDMETHOD_(BOOL, SetText(
		LPCTSTR lpszText, 
		UINT nPane, 
		UINT nType,
		COLORREF bgColor = CLR_DEFAULT
		));

	STDMETHOD_(void, SetTipText(
		int nPane, 
		LPCTSTR pszTipText 
		));

	STDMETHOD(OnCreateDeviceIndependentResources)();
	STDMETHOD(OnCreateDeviceResources)();
	STDMETHOD_(void, OnDiscardDeviceResources());

	BOOL		m_isOwnerDraw;
	COLORREF	m_bgColor;
};

