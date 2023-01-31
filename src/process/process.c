#include "process.h"
#include "../utils/error.h"

#include <TlHelp32.h>
#include <stdio.h>

void* read(uintptr_t address) {
	void* value;
	ReadProcessMemory(process.hProcess, (LPCVOID) address, &value, sizeof(value), NULL);
	return value;
}

BOOL write(uintptr_t address, void* value) {
	return WriteProcessMemory(process.hProcess, (LPVOID) address, &value, sizeof(value), NULL);
}

void getProcessInfo(const char* processName) {
	const HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hSnapshot == INVALID_HANDLE_VALUE) {
		handleProcessError("[Error] Cannot get an Handle.");
	}

	PROCESSENTRY32 processEntry = { .dwSize = sizeof(PROCESSENTRY32) };

	if (!Process32First(hSnapshot, &processEntry)) {
		handleProcessError("[Error] Cannot get process.");
	}

	do {
		if (strcmp(processEntry.szExeFile, processName) == 0) {
			process.id = processEntry.th32ProcessID;
			process.hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, process.id);
			break;
		}
	} while (Process32Next(hSnapshot, &processEntry));

	if (hSnapshot) {
		CloseHandle(hSnapshot);
	}
}

uintptr_t getModuleAddress(const char* moduleName) {
	uintptr_t moduleAddress = 0;
	const HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, process.id);

	if (hSnapshot == INVALID_HANDLE_VALUE) {
		handleProcessError("[Error] Cannot get an Handle.");
	}

	MODULEENTRY32 moduleEntry = { .dwSize = sizeof(MODULEENTRY32) };

	if (!Module32First(hSnapshot, &moduleEntry)) {
		handleProcessError("[Error] Cannot get process.");
	}

	do {
		if (strcmp(moduleEntry.szModule, moduleName) == 0) {
			moduleAddress = moduleEntry.modBaseAddr;
			break;
		}
	} while (Module32Next(hSnapshot, &moduleEntry));

	if (hSnapshot) {
		CloseHandle(hSnapshot);
	}
	return moduleAddress;
}