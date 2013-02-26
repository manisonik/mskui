#pragma once
#include "msk1.h"
#include "mskhelper.h"
#include "mskwindow.h"

typedef class CMSK1Window CMSK1Window;

struct MSK1_WNDPROCEDURE_STRUCT
{
	WNDPROC	oldWndProc;
	CMSK1Window* pWindow;
};

class CMSK1Framework :
	public IMSK1Application,
	public IMSK1Framework
{
public:
	CMSK1Framework(void);
	virtual ~CMSK1Framework(void);

	// IUnknown Methods
	STDMETHOD_(ULONG, AddRef());
	STDMETHOD_(ULONG, Release());
	STDMETHOD(QueryInterface)(
		REFIID   riid,
		LPVOID * ppvObj
		);

	// IMSKFramework Methods
	STDMETHOD(Initialize)(
		IMSK1Application* pApplication
		);

	STDMETHOD(SetValue)(
		MSK1_PROPERTY_KEY key, 
		DWORD value
		);

	STDMETHOD_(int, Run)(void);

	STDMETHOD(Destroy)();

	// IMSKApplication
	STDMETHOD(OnCreateCommand)(
		UINT cmdId,
		MSK1_COMMAND_TYPE cmdType,
		IMSK1CommandHandler** ppControlHandler
		);

	STDMETHOD(OnDestroyCommand)(void);

	STDMETHOD_(int, OnMessageLoop)(
		MSK1_MESSAGELOOP_FLAG flag,
		LPMSG msg
		);

	// CMSKFramework Methods
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

	static HRESULT WICLoadResourceBitmap(
		ID2D1RenderTarget *pRenderTarget,
		IWICImagingFactory *pIWICFactory,
		PCWSTR resourceName,
		PCWSTR resourceType,
		UINT destinationWidth,
		UINT destinationHeight,
		ID2D1Bitmap **ppBitmap
		);


	STDMETHOD(CreateDeviceIndependentResources)();
	STDMETHOD(CreateDeviceResources)();
	STDMETHOD_(void, DiscardDeviceResources());

public:	
	FLOAT m_fDIPScaleX;
	FLOAT m_fDIPScaleY;
	ID2D1Factory* m_pD2D1Factory;
	ID2D1DCRenderTarget* m_pD2D1RenderTarget;
	IDWriteFactory* m_pDWriteFactory;
	IDWriteTextFormat* m_pTextFormat;
	IWICImagingFactory* m_pImagingFactory;
	IMSK1Application* m_pApplication;
	ID2D1Bitmap* m_pBitmapClose;
	ID2D1Bitmap* m_pBitmapMinimize;
	ID2D1Bitmap* m_pBitmapMaximize;
	ID2D1Bitmap* m_pBitmapIcon;
	ID2D1Bitmap* m_pBitmapAutoHide;
	ID2D1Bitmap* m_pBitmapWindowPos;
	ID2D1Bitmap* m_pBitmapCloseSmall;
	ID2D1Bitmap* m_pBitmapRes16;
	ID2D1SolidColorBrush* m_d2dTestColor;
	CMSK1Window* m_pWindow;
	HWND m_hWnd;

private:
	CRITICAL_SECTION m_Cs;
	LONG m_cRef;
};

