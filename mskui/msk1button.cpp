#include "stdafx.h"
#include "msk1button.h"


CMSK1Button::CMSK1Button(CMSK1Framework* pFramework) :
	CMSK1Window(pFramework)
{
}


CMSK1Button::~CMSK1Button(void)
{
}

STDMETHODIMP CMSK1Button::OnProcessMessage(
	UINT msg,
	WPARAM wParam,
	LPARAM lParam,
	IMSK1Window* pWnd
	)
{
	if (msg == WM_NCCREATE) {
	} else if (msg == WM_PAINT) {
	} else if (msg == WM_NCPAINT) {

	}

	CallWindowProc(m_OldWndProc, m_hWnd, msg, wParam, lParam);

	return 0;
}