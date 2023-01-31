#include "process/process.h"
#include "config/offsets.h"
#include "cheat/skinChanger.h"

#include <stdio.h>

int main() {
	getProcessInfo("csgo.exe");
	const uintptr_t client = getModuleAddress("client.dll");
	const uintptr_t engine = getModuleAddress("engine.dll");

	DWORD dwExit = 0;
	while (GetExitCodeProcess(process.hProcess, &dwExit) && dwExit == STILL_ACTIVE) {
		uintptr_t localPlayer = read(client + DW_LOCAL_PLAYER);

		for (byte i = 0; i < 8; i++) {
			DWORD weapon = read(localPlayer + M_hMY_WEAPONS + i * 0x4);
			weapon = weapon & 0xFFF;
			weapon = read(client + DW_ENTITY_LIST + (weapon - 1) * 0x10);

			if (!weapon)
				continue;

			short paint = retrieveWeaponId(read(weapon + M_iITEM_DEFINITION_INDEX));
			if (paint) {
				BOOL shouldUpdate = read(weapon + M_nFALL_BACK_PAINT_KIT) != paint;

				write(weapon + M_iITEM_ID_HIGH, -1);
				write(weapon + M_nFALL_BACK_PAINT_KIT, paint);
				write(weapon + M_FL_FALL_BACK_WEAR, 0);

				if (shouldUpdate) {
					uintptr_t engineState = read(engine + DW_CLIENT_STATE);
					write(engineState + 0x174, -1);
				}
			}
		}
		Sleep(2);
	}
	return 0;
}