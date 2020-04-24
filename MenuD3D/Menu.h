#pragma once

void Menu(LPDIRECT3DDEVICE9 pDevice) {
    DrawBox(Esquerda, Topo, Largura, Altura, AZUL, pDevice);
    DrawBox(Esquerda + 1, Topo + 1, Largura - 2, Altura - 2, AZUL, pDevice);

    DrawItem(items[0],(LPSTR)"Munição infinita", pDevice);
    DrawItem(items[1],(LPSTR)"Item 2", pDevice);
    DrawItem(items[2],(LPSTR)"Item 3", pDevice);

}

HRESULT WINAPI My_EndScene(LPDIRECT3DDEVICE9 pDevice) {
    HRESULT ret;

    creatFont(pDevice);
    if (bShow) {
        Menu(pDevice);
        Text(Esquerda, 5, (LPSTR)"RE5_Menu", BRANCO);
    }
    Key();
    y = (Topo + 6);
    total_items = 0;
    resetFont();
    UnHookFunction((void*)Original_EndScene, EndScene_bytes, 5);
    ret = Original_EndScene(pDevice);
    HookFunction((void*)Original_EndScene, (void*)My_EndScene, 5, EndScene_bytes);
    return ret;
}