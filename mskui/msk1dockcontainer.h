#pragma once

#include "mskwindow.h"

class CMSK1DockContainer
{
public:
	CMSK1DockContainer(void);
	virtual ~CMSK1DockContainer(void);

	static LRESULT DockContainerProc(
		HWND hWnd, 
		UINT msg, 
		WPARAM wParam, 
		LPARAM lParam
		);

	STDMETHOD(Initialize)(
		CMSK1Window* pParentWnd
		);

	CMSK1Window* pPrimaryWnd;
	CMSK1Window* pSecondaryWnd;
};