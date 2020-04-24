#include "framework.h"
#include "Hook.h"
#include "Draw.h"
#include "Menu.h"
#include "Hacks.h"

void creatDevice(DWORD* dVTable) {
    LPDIRECT3D9 mD3D = NULL;
    mD3D = Direct3DCreate9(D3D_SDK_VERSION);
    if (mD3D == NULL) {
        return;
    }
    D3DPRESENT_PARAMETERS pPresentParams;
    ZeroMemory(&pPresentParams, sizeof(pPresentParams));
    pPresentParams.Windowed = true;
    pPresentParams.BackBufferFormat = D3DFMT_UNKNOWN;
    pPresentParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
    LPDIRECT3DDEVICE9 pDevice = NULL;
    if (FAILED(mD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GetDesktopWindow(), D3DCREATE_SOFTWARE_VERTEXPROCESSING,
        &pPresentParams, &pDevice))) {
        return;
    }
    DWORD* vTable = (DWORD*)pDevice;
    vTable = (DWORD*)vTable[0];
    dVTable[0] = vTable[16];
    dVTable[1] = vTable[17];
    dVTable[2] = vTable[42];
}

void creatMenu() {
    DWORD vTable[3] = { 0 };
    creatDevice(vTable);
    Original_EndScene = (_EndScene)vTable[2];
    HookFunction((void*)Original_EndScene, (void*)My_EndScene, 5, EndScene_bytes);
}

DWORD WINAPI mThread(PVOID MenuD3D) {
    while (!GetModuleHandle(L"d3d9.dll"))
    {
        Sleep(100);
    }
    creatMenu();
    while (1) {
        ativa();
        Sleep(100);
    }
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        CreateThread(0, 0, mThread, nullptr, 0, 0);
    }
    return TRUE;
}