#pragma once

#define RECTWIDTH(rc) (rc.right - rc.left)
#define RECTHEIGHT(rc) (rc.bottom - rc.top)

#pragma pack(push,1)
struct STDCALLTHUNK
{
	DWORD   m_mov;          // mov dword ptr [esp+0x4], pThis (esp+0x4 is hWnd)
	DWORD   m_this;         //
	BYTE    m_jmp;          // jmp WndProc
	DWORD   m_relproc;      // relative jmp

	void Init(DWORD proc, void* pThis)
	{
		// 0x042444C7 is the same as "mov dword ptr[esp+0x4]," on the x86 platform,
		// so the following statements are the same as "mov dword ptr [esp+0x4], pThis"
		// where [esp+0x4] is the hWnd argument pushed onto the call stack by the Win32
		// system. Here the this pointer overwrites the hWnd, but there is no harm 
		// because the hWnd has already been saved to the object to which the this 
		// pointer refers to.
		m_mov = 0x042444C7;  //C7 44 24 0C
		m_this = PtrToUlong(pThis);

		// After the this pointer has been added to the call stack, now jump to the 
		// actual callback (in this case, TurnCallbackIntoMember)
		m_jmp = 0xe9;
		m_relproc = DWORD((INT_PTR)proc - ((INT_PTR)this+sizeof(STDCALLTHUNK)));

		FlushInstructionCache(GetCurrentProcess(), this, sizeof(STDCALLTHUNK));
	}

	void* operator new(size_t)
	{
		return VirtualAlloc(NULL, PAGE_SIZE, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	}
	void operator delete(void* p)
	{
		VirtualFree(p, 0, MEM_RELEASE);
	}
};
#pragma pack(pop)
