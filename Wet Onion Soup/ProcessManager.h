#pragma once

typedef unsigned long DWORD;
typedef void* LPVOID;
typedef const void* LPCVOID;
typedef void* HANDLE;

class ProcessManager
{
public:
	ProcessManager(const wchar_t* executable_name, bool should_begin_obtaining_handle = true);
	~ProcessManager();
	bool Write(LPVOID memory_location, LPCVOID value, size_t size);
	bool Read(LPCVOID memory_location, LPVOID value, size_t size);
	bool IsRunning();
	void ObtainHandle();

private:
	HANDLE m_Handle;
	bool getProcessHandle();
	const wchar_t* m_ProcName;
};