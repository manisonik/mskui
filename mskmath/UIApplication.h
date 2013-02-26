#pragma once
#include "stdafx.h"
#include "Resource.h"


class CUIApplication :
	public IMSK1Application,
	public IMSK1CommandHandler
{
public:
	CUIApplication();
	virtual ~CUIApplication(void);

	// IUnknown Methods
	STDMETHOD_(ULONG, AddRef());
	STDMETHOD_(ULONG, Release());
	STDMETHOD(QueryInterface)(
		REFIID   riid,
		LPVOID * ppvObj
		);

	// IMSKCommandHandler
	STDMETHOD(OnProcessMessage)(
		UINT msg,
		WPARAM wParam,
		LPARAM lParam,
		IMSK1Window* pWnd
		);

	// IUIApplication Methods
	STDMETHOD(OnCreateCommand)(
		UINT cmdId,
		MSK1_COMMAND_TYPE cmdType,
		IMSK1CommandHandler** ppCommandHandler
		);

	STDMETHOD(OnDestroyCommand)(void);

	STDMETHOD_(int, OnMessageLoop)(
		MSK1_MESSAGELOOP_FLAG flag,
		LPMSG msg
		);

protected:
	void OnDestroy(void);
	int OnCreate(LPCREATESTRUCT lpCreateStruct, IMSK1Window* pWnd);

private:
	IMSK1Window* m_pPanel;
	HWND m_hWnd;
	UINT m_cRef;
};

