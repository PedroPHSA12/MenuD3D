#pragma once

#define BRANCO          D3DCOLOR_ARGB(200,255,255,255)
#define VERDE           D3DCOLOR_ARGB(255, 0, 255, 0)
#define VERDE_T         D3DCOLOR_ARGB(120, 50, 200, 150)
#define VERMELHO        D3DCOLOR_ARGB(255, 255, 0, 0)
#define AZUL            D3DCOLOR_ARGB(255, 50, 150, 200)
#define AZUL_t          D3DCOLOR_ARGB(120, 50, 150, 200)


LPD3DXFONT pFont;

struct Items_ {
    bool seleted, off_on;
};

Items_ items[200];

void creatFont(LPDIRECT3DDEVICE9 pD3D9) {
    if (!pFont) {
        D3DXCreateFont(pD3D9, 15, 0, FW_BOLD, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
            ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Tahoma", &pFont);
    }
}

void resetFont() {
    pFont->OnLostDevice();
    pFont->OnResetDevice();
}

void Text(int x, int y, LPSTR text, DWORD color) {
    RECT rect, rect2;
    SetRect(&rect, x, y, x, y);
    SetRect(&rect2, x - 0.1, y + 0.2, x - 0.1, y + 0.);
    pFont->DrawTextA(NULL, text, -1, &rect2, DT_LEFT | DT_NOCLIP, 0x00000000);
    pFont->DrawTextA(NULL, text, -1, &rect, DT_LEFT | DT_NOCLIP, color);
}

void DrawBox(int x, int y, int w, int h, D3DCOLOR Color, LPDIRECT3DDEVICE9 pD3D9) {

    struct Vertex
    {
        float x, y, z, ht;
        DWORD Color;
    }
    V[4] = { {x, y + h, 0.0f, 0.0f, Color}, {x, y, 0.0f, 0.01, Color}, {x + w, y + h, 0.0f, 0.0f, Color}, {x + w, y, 0.0f, 0.0f, Color} };
    pD3D9->SetTexture(0, NULL);
    pD3D9->SetPixelShader(0);
    pD3D9->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
    pD3D9->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
    pD3D9->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    pD3D9->SetRenderState(D3DRS_ZENABLE, FALSE);
    pD3D9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
    pD3D9->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, V, sizeof(Vertex));
    return;
}
int Esquerda = 25, Topo = 25;
int Largura = 200, Altura = 200;
int x = (Esquerda + 6), y = (Topo + 6);
int total_items = 0;

void DrawItem(Items_ its,LPSTR text, LPDIRECT3DDEVICE9 pDevice) {
    total_items++;
    if (its.seleted) {
        DrawBox(Esquerda, y, Largura, 20, VERMELHO, pDevice);

    }
    else {
        DrawBox(Esquerda, y, Largura, 20, AZUL, pDevice);
    }
    if (its.off_on) {
        Text(x + 150, y + 3, (LPSTR)"< ON >", VERDE);
    }
    else {
        Text(x + 150, y + 3, (LPSTR)"< OFF >", BRANCO);

    }
    DrawBox(Esquerda, y, Largura, 20, VERDE_T, pDevice);
    Text(x, y + 3, text, BRANCO);
    y += 25;
}

int index = 0;
bool bShow = false;

void Key() {
    if (GetAsyncKeyState(VK_UP) & 1) {
        if (index > 0) {
            items[index].seleted = false;
            index--;
        }
        else {
            items[index].seleted = false;
            index = total_items - 1;
        }
    }
    if (GetAsyncKeyState(VK_DOWN) & 1) {
        if (index < total_items - 1) {
            items[index].seleted = false;
            index++;
        }
        else {
            items[index].seleted = false;
            index = 0;
        }
    }
    if (GetAsyncKeyState(VK_LEFT) & 1) {
        items[index].off_on = !items[index].off_on;
    }

    if (GetAsyncKeyState(VK_RIGHT) & 1) {
        items[index].off_on = !items[index].off_on;
    }
    if (GetAsyncKeyState(VK_INSERT) & 1) {
        bShow = (!bShow);
    }

    items[index].seleted = true;
}
