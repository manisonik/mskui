// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "msk1.h"
#include "mskframework.h"
#include "mskfactory.h"

#include <InitGuid.h>

DEFINE_GUID(IID_IMSK1Framework,			0xd7eaa557,0xf4a0,0x41e1,0xad,0x0a,0x58,0xb1,0x0e,0x58,0xfc,0xf0);
DEFINE_GUID(IID_IMSK1Application,		0xd7eaa557,0xf4a0,0x41e1,0xad,0x0a,0x58,0xb1,0x0e,0x58,0xfc,0xf1);
DEFINE_GUID(IID_IMSK1CommandHandler,	0xd7eaa557,0xf4a0,0x41e1,0xad,0x0a,0x58,0xb1,0x0e,0x58,0xfc,0xf2);
DEFINE_GUID(IID_IMSK1Window,			0xd7eaa557,0xf4a0,0x41e1,0xad,0x0a,0x58,0xb1,0x0e,0x58,0xfc,0xf3);
DEFINE_GUID(IID_IMSK1Panel,				0xd7eaa557,0xf4a0,0x41e1,0xad,0x0a,0x58,0xb1,0x0e,0x58,0xfc,0xf4);

HMODULE g_hInstThisDll;
CMSK1Factory* pFactory = NULL;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		// Store hModule into global variable
		g_hInstThisDll = hModule;
		DisableThreadLibraryCalls ( hModule );
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		DllCanUnloadNow();
		break;
	}
	return TRUE;
}

__declspec(dllexport) HRESULT WINAPI MSK1Create(
	IMSK1Framework** pFramework
	)
{
	CMSK1Framework* pObject = new CMSK1Framework();

	*pFramework = pObject;

	return S_OK;
}

STDAPI DllGetClassObject(
	const CLSID& clsid,
	const IID& iid,
	void** ppv
	)
{
	if (clsid == IID_IMSK1Framework)
	{
		pFactory = new CMSK1Factory();

		if (pFactory == NULL)
		{
			return E_OUTOFMEMORY;
		}
		else
		{
			return pFactory->QueryInterface(iid, ppv);
		}
	}

	return CLASS_E_CLASSNOTAVAILABLE;
}

STDAPI DllCanUnloadNow()
{
	if (g_nComObjsInUse == 0)
	{
		if (pFactory)
		{
			pFactory->Release();
			pFactory = NULL;
		}

		return S_OK;
	}
	
	return E_FAIL;
}

STDAPI DllRegisterServer()
{
	HKEY hCLSIDKey = NULL;
	HKEY hInProcSvrKey = NULL;
	LONG lRet;
	TCHAR szModulePath [MAX_PATH];
	TCHAR szClassDescription[] = L"Manisonik Framework";
	TCHAR szThreadingModel[]   = L"Apartment";

	__try
	{
		// Create a key under CLSID for our COM server.
		lRet = RegCreateKeyEx ( HKEY_CLASSES_ROOT, L"CLSID\\{d7eaa557-f4a0-41e1-ad0a-58b10e58fcc9}",
			0, NULL, REG_OPTION_NON_VOLATILE, KEY_SET_VALUE | KEY_CREATE_SUB_KEY,
			NULL, &hCLSIDKey, NULL );

		if ( ERROR_SUCCESS != lRet ) 
			return HRESULT_FROM_WIN32(lRet);

		// The default value of the key is a human-readable description of the coclass.

		lRet = RegSetValueEx ( hCLSIDKey, NULL, 0, REG_SZ, (const BYTE*) szClassDescription,
			sizeof(szClassDescription) );

		if ( ERROR_SUCCESS != lRet )
			return HRESULT_FROM_WIN32(lRet);

		// Create the InProcServer32 key, which holds info about our coclass.

		lRet = RegCreateKeyEx ( hCLSIDKey, L"InProcServer32", 0, NULL, REG_OPTION_NON_VOLATILE,
			KEY_SET_VALUE, NULL, &hInProcSvrKey, NULL );

		if ( ERROR_SUCCESS != lRet )
			return HRESULT_FROM_WIN32(lRet);

		// The default value of the InProcServer32 key holds the full path to our DLL.

		GetModuleFileName ( g_hInstThisDll, szModulePath, MAX_PATH );

		lRet = RegSetValueEx ( hInProcSvrKey, NULL, 0, REG_SZ, (const BYTE*) szModulePath, 
			sizeof(TCHAR) * (lstrlen(szModulePath)+1) );

		if ( ERROR_SUCCESS != lRet )
			return HRESULT_FROM_WIN32(lRet);

		// The ThreadingModel value tells COM how it should handle threads in our DLL.
		// The concept of apartments is beyond the scope of this article, but for
		// simple, single-threaded DLLs, use Apartment.

		lRet = RegSetValueEx ( hInProcSvrKey, L"ThreadingModel", 0, REG_SZ,
			(const BYTE*) szThreadingModel, 
			sizeof(szThreadingModel) );

		if ( ERROR_SUCCESS != lRet )
			return HRESULT_FROM_WIN32(lRet);
	}   
	__finally
	{
		if ( NULL != hCLSIDKey )
			RegCloseKey ( hCLSIDKey );

		if ( NULL != hInProcSvrKey )
			RegCloseKey ( hInProcSvrKey );
	}

	return S_OK;
}

STDAPI DllUnregisterServer()
{
    // Delete our registry entries.  Note that you must delete from the deepest
    // key and work upwards, because on NT/2K, RegDeleteKey() doesn't delete 
    // keys that have subkeys on NT/2K.

    RegDeleteKey ( HKEY_CLASSES_ROOT, L"CLSID\\{d7eaa557-f4a0-41e1-ad0a-58b10e58fcc9}\\InProcServer32");
    RegDeleteKey ( HKEY_CLASSES_ROOT, L"CLSID\\{d7eaa557-f4a0-41e1-ad0a-58b10e58fcc9}");

    return S_OK;
}