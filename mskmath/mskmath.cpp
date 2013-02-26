// mskmath.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "mskmath.h"
#include "UIApplication.h"

int APIENTRY _tWinMain(HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPTSTR    lpCmdLine,
					 int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	IMSK1Framework* pFramework = NULL;

	if (SUCCEEDED(MSK1Create(&pFramework))) {
		pFramework->Initialize(new CUIApplication());
		
		return pFramework->Run();
	}

	return 0;
}