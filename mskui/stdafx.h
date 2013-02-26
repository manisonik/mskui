// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

// Disable warning messages 4507 and 4034.
#pragma warning( disable : 4250 )

#include "targetver.h"

// Windows Header Files:
#include <windows.h>
#include <WindowsX.h>
#include <list>
#include <vector>
#include <commctrl.h>
#include <dwmapi.h>
#include <Uxtheme.h>
#include <vssym32.h>
#include <Wincodec.h>

// Direct2D Header Files:
#include <d2d1.h>
#include <d2d1_1.h>
#include <d2d1Helper.h>
#include <dwrite.h>

// External Variables
extern long g_nComObjsInUse;

#if !defined(PAGE_SIZE)
#define PAGE_SIZE 4096
#endif

#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif


template<class Interface>
inline void
SAFE_RELEASE(
    Interface **ppInterfaceToRelease
    )
{
    if (*ppInterfaceToRelease != NULL)
    {
        (*ppInterfaceToRelease)->Release();

        (*ppInterfaceToRelease) = NULL;
    }
}

template<class Class>
inline void
SAFE_DELETE(
	Class **ppClassToDelete
	)
{
	if (*ppClassToDelete != NULL)
	{
		delete (*ppClassToDelete);
		(*ppClassToDelete) = NULL;
	}
}

template<typename Variable>
inline void
SAFE_UNINITIALIZE(
	Variable VariableToUnInitialize
	)
{
	if (VariableToUnInitialize != NULL)
	{
		(VariableToUnInitialize) = NULL;
	}
}

#ifndef Assert
#if defined( DEBUG ) || defined( _DEBUG )
#define Assert(b) if (!(b)) {OutputDebugStringA("Assert: " #b "\n");}
#else
#define Assert(b)
#endif //DEBUG || _DEBUG
#endif