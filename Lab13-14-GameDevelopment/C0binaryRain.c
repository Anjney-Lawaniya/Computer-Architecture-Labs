#include <stdbool.h>
#include <stdlib.h>

volatile int *pCtrl = (int *)0xFF203020;
volatile int *swP = (int *)0xFF200040;
volatile int *hex0 = (int *)0xFF200020;

char s7[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x67};
int f[10][5] = {{7,5,5,5,7},{2,6,2,2,7},{7,1,7,4,7},{7,1,7,1,7},{5,5,7,1,1},{7,4,7,1,7},{7,4,7,5,7},{7,1,1,1,1},{7,5,7,5,7},{7,5,7,1,7}};

typedef struct {
    int x, y, v;
    int val;
    bool a;
} B;

B l[5];
int s = 0;
int pb;

void pPx(int x, int y, short c) {
    *(short *)(pb + (y << 10) + (x << 1)) = c;
}

void clrVga() {
    for (int i = 0; i < 320; i++)
        for (int j = 0; j < 240; j++)
            pPx(i, j, 0x0000);
}

void dRect(int x, int y, int w, int h, short c) {
    for (int i = 0; i < w; i++)
        for (int j = 0; j < h; j++)
            pPx(x + i, y + j, c);
}

void pDig(int dx, int dy, int d, short c) {
    for(int i = 0; i < 5; i++) {
        int v = f[d][i];
        if(v & 4) pPx(dx, dy + i, c);
        if(v & 2) pPx(dx + 1, dy + i, c);
        if(v & 1) pPx(dx + 2, dy + i, c);
    }
}

void dNum(int nx, int ny, int n, short c) {
    int t = n / 10;
    int u = n % 10;
    if(t > 0) {
        pDig(nx, ny, t, c);
        pDig(nx + 5, ny, u, c);
    } else {
        pDig(nx + 2, ny, u, c);
    }
}

void spwnBlk(int i) {
    l[i].x = (i * 64) + 12;
    l[i].y = 0;
    l[i].val = (rand() % 10) + 1;
    l[i].v = 60 - (l[i].val * 4);
    l[i].a = true;
    dRect(l[i].x, 0, 40, 20, 0x07FF);
    dNum(l[i].x + 16, 7, l[i].val, 0x0000);
}

void upSc() {
    *hex0 = s7[s % 10] | (s7[(s / 10) % 10] << 8);
}

int main() {
    pb = *pCtrl;
    clrVga();
    dRect(0, 220, 320, 2, 0xF800);

    for(int i = 0; i < 5; i++) spwnBlk(i);
    upSc();

    while(1) {
        int sw = *swP & 0x0F; 

        for(int i = 0; i < 5; i++) {
            if(!l[i].a) continue;

            if(sw == l[i].val) {
                dRect(l[i].x, l[i].y / 100, 40, 20, 0x0000);
                s++;
                upSc();
                spwnBlk(i);
                continue;
            }

            int oY = l[i].y / 100;
            l[i].y += l[i].v;
            int nY = l[i].y / 100;

            if(nY > oY) {
                dRect(l[i].x, oY, 40, nY - oY, 0x0000);
                dNum(l[i].x + 16, oY + 7, l[i].val, 0x07FF);
                dRect(l[i].x, oY + 20, 40, nY - oY, 0x07FF);
                dNum(l[i].x + 16, nY + 7, l[i].val, 0x0000);
            }

            if(nY + 20 >= 220) {
                clrVga();
                while(1);
            }
        }
        for(volatile int d = 0; d < 150000; d++);
    }
}