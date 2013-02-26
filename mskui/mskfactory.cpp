#include "StdAfx.h"
#include "mskfactory.h"
#include "mskframework.h"

CMSK1Factory::CMSK1Factory(void) : m_cRef(1)
{

}


CMSK1Factory::~CMSK1Factory(void)
{

}

STDMETHODIMP CMSK1Factory::QueryInterface(
	REFIID   riid,
	LPVOID* ppvObj
	)
{
    if (riid == IID_IUnknown)
    {
        *ppvObj = static_cast<IUnknown*>(this);
    }
	else if (riid == IID_IClassFactory)
    {
        *ppvObj = static_cast<IClassFactory*>(this);
    }
    else 
    {
        *ppvObj = NULL;
        return E_NOINTERFACE;
    }

    AddRef();
	return S_OK;
}

ULONG CMSK1Factory::Release()
{
	// Decrement the object's internal counter.
	ULONG cRef = InterlockedDecrement(&m_cRef);

	if (cRef == 0)
	{
		delete this;
	}

	return cRef;
}

ULONG CMSK1Factory::AddRef()
{
	InterlockedIncrement(&m_cRef);
	return m_cRef;
}

STDMETHODIMP CMSK1Factory::CreateInstance(
		IUnknown* pUnknownOuter,
		const IID& iid,
		void** ppv
		)
{
	 if (pUnknownOuter != NULL) {        
		 return CLASS_E_NOAGGREGATION;
	 }

	 if (iid == IID_IMSK1Framework) {
		 CMSK1Framework* pObject = new CMSK1Framework(); 

		 if (pObject == NULL)  {        
			 return E_OUTOFMEMORY;   
		 } else {
			 ppv = (void**) &pObject;
		 }
	 }

	return S_OK;
}
	
STDMETHODIMP CMSK1Factory::LockServer(
		BOOL bLock
		)
{
	return E_NOTIMPL;
}