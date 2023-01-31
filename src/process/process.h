#ifndef PROCESS_H
#define PROCESS_H

#include <Windows.h>

struct Process {
	DWORD id;
	HANDLE hProcess;
} process;

void* read(uintptr_t address);
BOOL write(uintptr_t address, void* value);

void getProcessInfo(const char* processName);
uintptr_t getModuleAddress(const char* moduleName);

#endif