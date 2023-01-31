#include "skinChanger.h"

short retrieveWeaponId(short itemID) {
	switch (itemID) {
		case 1: // Deagle
			return 1090;
		case 4: // Glock
			return 988;
		case 7: // Ak47
			return 959;
		case 9: // Awp
			return 446;
		case 11: // Sg1
			return 897;
		case 23: // Mp5
			return 1061;
		case 30: // Tec9
			return 791;
		case 60: // M4A1s
			return 962;
		case 61: // Usps
			return 991;
		default: // Not found
			return 0;
	}
}