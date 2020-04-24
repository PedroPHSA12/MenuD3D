#pragma once

typedef HRESULT(WINAPI* _EndScene)(LPDIRECT3DDEVICE9 pDevice);

_EndScene Original_EndScene;

BYTE EndScene_bytes[5];

void UnHookFunction(void* original, BYTE* bytes_original, int tamanho) {
    DWORD protect;
    VirtualProtect(original, tamanho, PAGE_EXECUTE_READWRITE, &protect);
    memcpy(original, bytes_original, tamanho);
    VirtualProtect(original, tamanho, protect, &protect);
}
void HookFunction(void* original, void* nova, int tamanho, BYTE* bytes_salvos) {
    DWORD protect;
    VirtualProtect(original, tamanho, PAGE_EXECUTE_READWRITE, &protect);
    memcpy(bytes_salvos, original, tamanho);
    DWORD diferença = ((DWORD)nova - (DWORD)original) - tamanho;
    memset(original, 0x90, tamanho);
    *(BYTE*)original = 0xE9;
    *(DWORD*)((DWORD)original + 1) = diferença;
    VirtualProtect(original, tamanho, protect, &protect);
}