#include "StdAfx.h"
#include "resource.h"
#include "mskframework.h"
#include "msk1winapp.h"

// Global Variables (only global variable)
long g_nComObjsInUse;

CMSK1Framework::CMSK1Framework(void) : 
	m_cRef(1),
	m_pD2D1Factory(0),
	m_fDIPScaleX(1.0f),
	m_fDIPScaleY(1.0f),
	m_pD2D1RenderTarget(0),
	m_pImagingFactory(0)
{
	// Initalize Common Controls
	INITCOMMONCONTROLSEX ccex;
	ccex.dwICC = ICC_BAR_CLASSES;
	ccex.dwSize = sizeof(INITCOMMONCONTROLSEX);

	InitCommonControlsEx(&ccex);

	// Increase Object Reference count
	InterlockedIncrement(&g_nComObjsInUse);
}

CMSK1Framework::~CMSK1Framework(void)
{
	SAFE_RELEASE(&m_pWindow);
	SAFE_RELEASE(&m_pImagingFactory);
	SAFE_RELEASE(&m_pD2D1RenderTarget);
	SAFE_RELEASE(&m_pD2D1Factory);

	InterlockedDecrement(&g_nComObjsInUse);
}

int CMSK1Framework::Run()
{
	return OnMessageLoop((MSK1_MESSAGELOOP_FLAG) 0, (LPMSG) NULL);
}

STDMETHODIMP CMSK1Framework::Destroy()
{
	ULONG cRef;

	cRef = InterlockedDecrement(&m_cRef);

	if (cRef == 0) {
		delete this;
	}

	return cRef;
}

HRESULT CMSK1Framework::WICLoadResourceBitmap(
	ID2D1RenderTarget *pRenderTarget,
	IWICImagingFactory *pIWICFactory,
	PCWSTR resourceName,
	PCWSTR resourceType,
	UINT destinationWidth,
	UINT destinationHeight,
	ID2D1Bitmap **ppBitmap
	)
{
	IWICBitmapDecoder *pDecoder = NULL;
	IWICBitmapFrameDecode *pSource = NULL;
	IWICStream *pStream = NULL;
	IWICFormatConverter *pConverter = NULL;
	IWICBitmapScaler *pScaler = NULL;

	HRSRC imageResHandle = NULL;
	HGLOBAL imageResDataHandle = NULL;
	void *pImageFile = NULL;
	DWORD imageFileSize = 0;

	// Locate the resource.
	imageResHandle = FindResource(HINST_THISCOMPONENT, resourceName, resourceType);

	HRESULT hr = imageResHandle ? S_OK : E_FAIL;

	if (SUCCEEDED(hr))
	{
		// Load the resource.
		imageResDataHandle = LoadResource(HINST_THISCOMPONENT, imageResHandle);

		hr = imageResDataHandle ? S_OK : E_FAIL;
	}

	if (SUCCEEDED(hr))
	{
		// Lock it to get a system memory pointer.
		pImageFile = LockResource(imageResDataHandle);

		hr = pImageFile ? S_OK : E_FAIL;
	}

	if (SUCCEEDED(hr))
	{
		// Calculate the size.
		imageFileSize = SizeofResource(HINST_THISCOMPONENT, imageResHandle);

		hr = imageFileSize ? S_OK : E_FAIL;

	}

	if (SUCCEEDED(hr))
	{
		// Create a WIC stream to map onto the memory.
		hr = pIWICFactory->CreateStream(&pStream);
	}

	if (SUCCEEDED(hr))
	{
		// Initialize the stream with the memory pointer and size.
		hr = pStream->InitializeFromMemory(
			reinterpret_cast<BYTE*>(pImageFile),
			imageFileSize
			);
	}

	if (SUCCEEDED(hr))
	{
		// Create a decoder for the stream.
		hr = pIWICFactory->CreateDecoderFromStream(
			pStream,
			NULL,
			WICDecodeMetadataCacheOnLoad,
			&pDecoder
			);
	}

	if (SUCCEEDED(hr))
	{
		// Create the initial frame.
		hr = pDecoder->GetFrame(0, &pSource);
	}

	if (SUCCEEDED(hr))
	{
		// Convert the image format to 32bppPBGRA
		// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
		hr = pIWICFactory->CreateFormatConverter(&pConverter);
	}

	if (SUCCEEDED(hr))
	{
		hr = pConverter->Initialize(
			pSource,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL,
			0.f,
			WICBitmapPaletteTypeMedianCut
			);
	}

	if (SUCCEEDED(hr))
	{
		//create a Direct2D bitmap from the WIC bitmap.
		hr = pRenderTarget->CreateBitmapFromWicBitmap(
			pConverter,
			NULL,
			ppBitmap
			);

	}

	SAFE_RELEASE(&pDecoder);
	SAFE_RELEASE(&pSource);
	SAFE_RELEASE(&pStream);
	SAFE_RELEASE(&pConverter);
	SAFE_RELEASE(&pScaler);

	return hr;
}

STDMETHODIMP CMSK1Framework::QueryInterface(
	REFIID   riid,
	LPVOID* ppvObj
	)
{
	if (riid == IID_IUnknown || riid == __uuidof(IMSK1Framework)) {
		*ppvObj = static_cast<IMSK1Framework*>(this);
	} else if (riid == __uuidof(IMSK1Application)) {
		*ppvObj = static_cast<IMSK1Application*>(this);
	} else {
		*ppvObj = NULL;
		return E_NOINTERFACE;
	}

	AddRef();
	return S_OK;
}

STDMETHODIMP CMSK1Framework::SetValue(
	MSK1_PROPERTY_KEY key, 
	DWORD value
	)
{
	return E_NOTIMPL;
}

ULONG CMSK1Framework::Release()
{
	// Decrement the object's internal counter.
	ULONG cRef = InterlockedDecrement(&m_cRef);

	if (cRef == 0) {
		delete this;
	}

	return cRef;
}

ULONG CMSK1Framework::AddRef()
{
	InterlockedIncrement(&m_cRef);

	return m_cRef;
}

STDMETHODIMP CMSK1Framework::OnCreateCommand(
	UINT cmdId,
	MSK1_COMMAND_TYPE cmdType,
	IMSK1CommandHandler** ppCommandHandler
	)
{
	return 	E_NOTIMPL;
}

STDMETHODIMP CMSK1Framework::OnDestroyCommand(void)
{
	return E_NOTIMPL;
}

STDMETHODIMP CMSK1Framework::CreateDeviceIndependentResources()
{
	HRESULT hr = S_OK;

	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2D1Factory);

	static const WCHAR msc_fontName[] = L"Calibri";
	static const FLOAT msc_fontSize = 12;

	// Create a Direct2D factory.
	if (SUCCEEDED(hr)) {

		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED, 
			__uuidof(m_pDWriteFactory),  
			reinterpret_cast<IUnknown **>(&m_pDWriteFactory)
			);
	}

	if (SUCCEEDED(hr)) {
		hr = m_pDWriteFactory->CreateTextFormat(
			msc_fontName,
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			msc_fontSize,
			L"", //locale
			&m_pTextFormat
			);
	}

	if (SUCCEEDED(hr)) {
		m_pTextFormat->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);

		IDWriteInlineObject *inlineObject = nullptr;

		m_pDWriteFactory->CreateEllipsisTrimmingSign(
			m_pTextFormat,
			&inlineObject
			);

		DWRITE_TRIMMING trimming = {
			DWRITE_TRIMMING_GRANULARITY_CHARACTER, 0, 0
		};

		m_pTextFormat->SetTrimming(&trimming, inlineObject);

		m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);

		m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}

	if (SUCCEEDED(hr))
	{
		hr = CoCreateInstance(
			CLSID_WICImagingFactory,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_PPV_ARGS(&m_pImagingFactory)
			);
	}

	return hr;
}

STDMETHODIMP CMSK1Framework::CreateDeviceResources()
{
	HRESULT hr = S_OK;

	// Create a DC render target.
	D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
		D2D1_RENDER_TARGET_TYPE_SOFTWARE,
		D2D1::PixelFormat(
		DXGI_FORMAT_B8G8R8A8_UNORM,
		D2D1_ALPHA_MODE_IGNORE),
		0,
		0,
		D2D1_RENDER_TARGET_USAGE_NONE,
		D2D1_FEATURE_LEVEL_DEFAULT
		);

	// Create a Direct2D render target.
	hr = m_pD2D1Factory->CreateDCRenderTarget(&props, &m_pD2D1RenderTarget);

	// Load Image Resources
	if (SUCCEEDED(hr)) {
		hr = WICLoadResourceBitmap(m_pD2D1RenderTarget, m_pImagingFactory, MAKEINTRESOURCE(IDB_CLOSE),	L"IMAGE", 0, 0, &m_pBitmapClose);
	}

	if (SUCCEEDED(hr)) {
		hr = WICLoadResourceBitmap(m_pD2D1RenderTarget, m_pImagingFactory, MAKEINTRESOURCE(IDB_MINIMIZE), L"IMAGE", 0, 0, &m_pBitmapMinimize);
	}

	if (SUCCEEDED(hr)) {
		hr = WICLoadResourceBitmap(m_pD2D1RenderTarget, m_pImagingFactory, MAKEINTRESOURCE(IDB_MAXIMIZE), L"IMAGE", 0, 0, &m_pBitmapMaximize);
	}

	if (SUCCEEDED(hr)) {
		hr = WICLoadResourceBitmap(m_pD2D1RenderTarget, m_pImagingFactory, MAKEINTRESOURCE(IDB_ICON), L"IMAGE", 0, 0, &m_pBitmapIcon);
	}

	if (SUCCEEDED(hr)) {
		hr = WICLoadResourceBitmap(m_pD2D1RenderTarget, m_pImagingFactory, MAKEINTRESOURCE(IDB_AUTO_HIDE), L"IMAGE", 0, 0, &m_pBitmapAutoHide);
	}

	if (SUCCEEDED(hr)) {
		hr = WICLoadResourceBitmap(m_pD2D1RenderTarget, m_pImagingFactory, MAKEINTRESOURCE(IDB_WINDOW_POS), L"IMAGE", 0, 0, &m_pBitmapWindowPos);
	}

	if (SUCCEEDED(hr)) {
		hr = WICLoadResourceBitmap(m_pD2D1RenderTarget, m_pImagingFactory, MAKEINTRESOURCE(IDB_CLOSE_SMALL), L"IMAGE", 0, 0, &m_pBitmapCloseSmall);
	}

	if (SUCCEEDED(hr)) {
		hr = WICLoadResourceBitmap(m_pD2D1RenderTarget, m_pImagingFactory, MAKEINTRESOURCE(IDB_RES16), L"IMAGE", 0, 0, &m_pBitmapRes16);
	}

	m_pD2D1RenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::SteelBlue), 
		&m_d2dTestColor
		);

	return hr;
}

STDMETHODIMP CMSK1Framework::Initialize(
	IMSK1Application* pApplication
	)
{
	HRESULT hr = S_OK;
	FLOAT dpiX, dpiY;

	// Initialize COM
	hr = CoInitialize(NULL);

	if (SUCCEEDED(hr)) {
		hr = CreateDeviceIndependentResources();
	}

	if (SUCCEEDED(hr)) {
		hr = CreateDeviceResources();
	}

	if (SUCCEEDED(hr))
	{
		// The factory returns the current system DPI. This is also the value it will use
		// to create its own windows.
		m_pD2D1Factory->GetDesktopDpi(&dpiX, &dpiY);

		// Set the DPI scale
		m_fDIPScaleX = dpiX/96.0f; m_fDIPScaleY = dpiY/96.0f;

		// Create Window Application
		m_pWindow = new CMSK1WindowApplication(this);

		hr = m_pWindow ? S_OK : E_FAIL;
	}

	// Initialize Default Parameters
	if (SUCCEEDED(hr)) {
		hr = m_pWindow->SetBorder(D2D1::ColorF(D2D1::ColorF::CadetBlue), 5);

		hr = m_pWindow->SetMargin(MSK1::MarginU(5, 5, 5, 5));
	}

	if (SUCCEEDED(hr)) {

		// Store Application Pointer
		m_pApplication = pApplication;

		// Store pointer to application
		m_pApplication->OnCreateCommand(
			0,
			MSK1_COMMAND_CREATE, 
			&m_pWindow->m_pHandler
			);

		// Create Universal Window Class
		WNDCLASSEX wcex;

		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style			= 0;
		wcex.lpfnWndProc	= CMSK1Window::StartWindowProc;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= HINST_THISCOMPONENT;
		wcex.hIcon			= NULL;
		wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground	= NULL;
		wcex.lpszMenuName	= NULL;
		wcex.lpszClassName	= L"MSK1_APP_CLASS";
		wcex.hIconSm		= NULL;

		// Register the main window class
		if (RegisterClassEx(&wcex)) 
		{
			// Create the window
			m_hWnd = CreateWindowEx(
				WS_EX_APPWINDOW,
				L"MSK1_APP_CLASS",
				L"Untitled",  
				WS_POPUP | WS_CLIPCHILDREN | 
				WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
				CW_USEDEFAULT,
				CW_USEDEFAULT, 
				static_cast<UINT>(ceil(1000.0f * m_fDIPScaleX)),
				static_cast<UINT>(ceil(600.0f  * m_fDIPScaleY)),
				NULL,
				NULL, 
				HINST_THISCOMPONENT, 
				m_pWindow
				);

			hr = m_hWnd ? S_OK : E_FAIL;
		}
	}

	if (SUCCEEDED(hr)) {
		ShowWindow(m_hWnd, SW_SHOW);
		UpdateWindow(m_hWnd);
	}

	return hr;
}

void CMSK1Framework::DiscardDeviceResources() 
{
	SAFE_RELEASE(&m_pD2D1RenderTarget);
}

int CMSK1Framework::OnMessageLoop(
	MSK1_MESSAGELOOP_FLAG flag,
	LPMSG msg
	)
{
	MSG message;
	BOOL bRet;

	while( (bRet = GetMessage(&message, NULL, 0, 0 )) != 0) { 
		if (bRet == -1) {
			// handle the error and possibly exit
		} else {
			m_pApplication->OnMessageLoop(
				MSK1_MESSAGELOOP_PREPROCESS, 
				&message
				);

			TranslateMessage(&message);
			DispatchMessage(&message);

			m_pApplication->OnMessageLoop(
				MSK1_MESSAGELOOP_POSTPROCESS, 
				&message
				);
		}
	}

	// Destroy all resources
	CoUninitialize();

	return m_pApplication->OnMessageLoop(MSK1_MESSAGELOOP_EXITPROCESS, &message);
}