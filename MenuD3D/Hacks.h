#pragma once

DWORD Module = *(DWORD*)GetModuleHandle(L"gta_sa.exe");

void ativa() {
	if (items[0].off_on) {
		DWORD Money = *(DWORD*)Module + 0x77F4D0;
		*(DWORD*)Money = 99999999;
	}
}