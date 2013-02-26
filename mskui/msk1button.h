#pragma once
#include "mskwindow.h"

class CMSK1Button :
	public CMSK1Window,
	public IMSK1ButtonCtrl
{
public:
	CMSK1Button(CMSK1Framework* pFramework);
	virtual ~CMSK1Button(void);

	STDMETHOD(OnProcessMessage)(
		UINT msg,
		WPARAM wParam,
		LPARAM lParam,
		IMSK1Window* pWnd
		);
};

