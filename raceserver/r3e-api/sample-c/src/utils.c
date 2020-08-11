#include "utils.h"

#include <TlHelp32.h>
#include <tchar.h>

BOOL is_process_running(const TCHAR* name)
{
    BOOL result = FALSE;
    HANDLE snapshot = NULL;
    PROCESSENTRY32 entry;

    ZeroMemory(&entry, sizeof(entry));
    entry.dwSize = sizeof(PROCESSENTRY32);

    snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (snapshot != INVALID_HANDLE_VALUE)
	{
		if (Process32First(snapshot, &entry))
		{
			do
			{
				if (_tcscmp(entry.szExeFile, name) == 0)
				{
					result = TRUE;
					break;
				}
			} while (Process32Next(snapshot, &entry));
		}
		CloseHandle(snapshot);
	}

    return result;
}
/*
BOOL matchProcessName( DWORD processID, std::string processName)
{
    TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

    // Get a handle to the process.

    HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
                                   PROCESS_VM_READ,
                                   FALSE, processID );

    // Get the process name.

    if (NULL != hProcess )
    {
        HMODULE hMod;
        DWORD cbNeeded;

        if ( EnumProcessModules( hProcess, &hMod, sizeof(hMod),
             &cbNeeded) )
        {
            GetModuleBaseName( hProcess, hMod, szProcessName,
                               sizeof(szProcessName)/sizeof(TCHAR) );
        }
    }

    // Compare process name with your string
    BOOL matchFound = !_tcscmp(szProcessName, processName.c_str() );

    // Release the handle to the process.
    CloseHandle( hProcess );

    return matchFound;
}
*/
BOOL is_r3e_running()
{
    return is_process_running(TEXT("RRRE64.exe"));
}
