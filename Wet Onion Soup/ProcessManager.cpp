#include "ProcessManager.h"
#include <Windows.h>
#include <TlHelp32.h>

ProcessManager::~ProcessManager() { CloseHandle(m_Handle); }

ProcessManager::ProcessManager(const wchar_t* exe, bool should_begin_obtaining_handle) : m_ProcName(exe), m_Handle{nullptr}
{
    if (should_begin_obtaining_handle) {
        ObtainHandle();
    }
}

void ProcessManager::ObtainHandle()
{
    while (!getProcessHandle()) {
        Sleep(3000);
    }
}

bool ProcessManager::getProcessHandle()
{
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (Process32First(snapshot, &entry) == TRUE) {
        while (Process32Next(snapshot, &entry) == TRUE) {
            if (wcscmp(entry.szExeFile, m_ProcName) == 0) {
                m_Handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);
                CloseHandle(snapshot);
                return true;
            }
        }
    }
    CloseHandle(snapshot);
    return false;
}

bool ProcessManager::IsRunning()
{
    DWORD exit_code{ 0 };
    GetExitCodeProcess(m_Handle, &exit_code);
    return (exit_code == STILL_ACTIVE);
}

bool ProcessManager::Write(LPVOID memory_location, LPCVOID value, size_t size) { return WriteProcessMemory(m_Handle, memory_location, value, size, NULL); }
bool ProcessManager::Read(LPCVOID memory_location, LPVOID value, size_t size) { return ReadProcessMemory(m_Handle, memory_location, value, size, NULL); }