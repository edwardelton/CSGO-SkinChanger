#include "error.h"

#include <Windows.h>
#include <stdio.h>

void handleProcessError(char* errorText) {
	printf("%s", errorText);
	Sleep(3000);
	exit(1);
}