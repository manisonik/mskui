#pragma once
#include "unknwn.h"

class CMSK1Factory :
	public IClassFactory
{
public:
	CMSK1Factory(void);
	virtual ~CMSK1Factory(void);

	// IUnknown Methods
	STDMETHOD_(ULONG, AddRef());
	STDMETHOD_(ULONG, Release());
	STDMETHOD(QueryInterface)(
		REFIID   riid,
		LPVOID * ppvObj
		);

	// IClassFactory Methods
	STDMETHOD(CreateInstance)(
		IUnknown* pUnknownOuter,
		const IID& iid,
		void** ppv
		);   
	
	STDMETHOD(LockServer)(
		BOOL bLock
		);

private:
	LONG m_cRef;
};

