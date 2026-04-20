#include <stdbool.h>
#include <stdlib.h>

volatile int *pC = (int *)0xFF203020;
volatile int *sP = (int *)0xFF200040;
volatile int *h0 = (int *)0xFF200020;
volatile int *aF = (int *)0xFF203044;
volatile int *aL = (int *)0xFF203048;
volatile int *aR = (int *)0xFF20304C;

char s7[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x67};

int fD[17][5] = {
    {7,5,5,5,7}, {2,6,2,2,7}, {7,1,7,4,7}, {7,1,7,1,7},
    {5,5,7,1,1}, {7,4,7,1,7}, {7,4,7,5,7}, {7,1,1,1,1},
    {7,5,7,5,7}, {7,5,7,1,7}, {7,4,5,5,7}, {2,5,7,5,5},
    {5,7,5,5,5}, {7,4,7,4,7}, {7,5,5,5,7}, {5,5,5,2,2},
    {7,5,7,4,5}
};

typedef struct {
    int x, y, vx, vy;
} tP;

typedef struct {
    int x, y, v, n, s, e;
    tP pt[16];
    bool a;
} pN;

pN p[5];
int sc = 0;
int pB;

void pPx(int x, int y, short c) {
    if(x >= 0 && x < 320 && y >= 0 && y < 240) {
        *(short *)(pB + (y << 10) + (x << 1)) = c;
    }
}


void dBg(int x, int y, int w, int h) {
    for(int i = 0; i < w; i++) {
        for(int j = 0; j < h; j++) {
            int px = x + i;
            int py = y + j;
            short c = 0x0000;
            if((px * 23 + py * 19) % 313 == 0) c = 0x5AEB;
            pPx(px, py, c);
        }
    }
}

void dEr() {
    for(int i = 0; i < 320; i++) {
        for(int j = 180; j < 240; j++) {
            long dx = i - 160;
            long dy = j - 500;
            if(dx*dx + dy*dy <= 102400) {
                short c = 0x001F;
                long c1 = (i-90)*(i-90) + (j-210)*(j-210);
                long c2 = (i-230)*(i-230) + (j-220)*(j-220);
                long c3 = (i-150)*(i-150) + (j-240)*(j-240);
                long c4 = (i-180)*(i-180) + (j-200)*(j-200);
                if(c1 < 1200 || c2 < 2000 || c3 < 1600 || c4 < 800) c = 0x07E0;
                if(dx*dx + dy*dy > 99000) c = 0x07FF;
                pPx(i, j, c);
            } else {
                short c = 0x0000;
                if((i * 23 + j * 19) % 313 == 0) c = 0x5AEB;
                pPx(i, j, c);
            }
        }
    }
}

void dRt(int x, int y, int w, int h, short c) {
    for(int i = 0; i < w; i++)
        for(int j = 0; j < h; j++)
            pPx(x + i, y + j, c);
}

void pDg(int dx, int dy, int d, short c) {
    for(int i = 0; i < 5; i++) {
        int v = fD[d][i];
        if(v & 4) pPx(dx, dy + i, c);
        if(v & 2) pPx(dx + 1, dy + i, c);
        if(v & 1) pPx(dx + 2, dy + i, c);
    }
}

void dNm(int nx, int ny, int n, short c) {
    int q = n / 10;
    int r = n % 10;
    if(q > 0) {
        pDg(nx, ny, q, c);
        pDg(nx + 5, ny, r, c);
    } else {
        pDg(nx + 3, ny, r, c);
    }
}

void bDg(int dx, int dy, int d, short c) {
    for(int i = 0; i < 5; i++) {
        int v = fD[d][i];
        if(v & 4) dRt(dx, dy + i*3, 3, 3, c);
        if(v & 2) dRt(dx + 3, dy + i*3, 3, 3, c);
        if(v & 1) dRt(dx + 6, dy + i*3, 3, 3, c);
    }
}

void bNm(int nx, int ny, int n, short c) {
    int q = n / 10;
    int r = n % 10;
    if(q > 0) {
        bDg(nx, ny, q, c);
        bDg(nx + 12, ny, r, c);
    } else {
        bDg(nx, ny, r, c);
    }
}

void uNk(int x, int oY, int nY, int n) {
    int h = nY - oY + 24;
    for(int j = 0; j < h; j++) {
        int py = oY + j;
        for(int i = 0; i < 24; i++) {
            int px = x + i;
            int nj = py - nY;
            bool iN = false;
            short cN = 0x4A40; 
            if(nj >= 0 && nj < 24) {
                if(nj < 6 && i >= 4 && i <= 19) { iN = true; if(nj < 3) cN = 0xFFE0; }
                else if(nj >= 6 && nj < 9 && i >= 8 && i <= 15) { iN = true; cN = 0xFFE0; }
                else if(nj >= 9 && nj < 19 && i >= 2 && i <= 21) { iN = true; }
                else if(nj >= 19 && nj < 22 && i >= 6 && i <= 17) { iN = true; }
                else if(nj >= 22 && nj < 24 && i >= 10 && i <= 13) { iN = true; cN = 0xFFE0; }
            }
            if(iN) pPx(px, py, cN);
            else {
                short cB = 0x0000;
                if((px * 23 + py * 19) % 313 == 0) cB = 0x5AEB;
                pPx(px, py, cB);
            }
        }
    }
    dNm(x + 7, nY + 10, n, 0xFFFF);
}

void sBm(int i) {
    p[i].x = (i * 64) + 20;
    p[i].y = -(rand() % 50) * 100;
    p[i].v = 40 + (rand() % 30) + (sc * 3);
    if(p[i].v > 250) p[i].v = 250;
    
    bool u;
    do {
        p[i].n = (rand() % 10) + 1;
        u = true;
        for(int j = 0; j < 5; j++) {
            if(i != j && p[j].a && p[j].s == 0 && p[j].n == p[i].n) {
                u = false;
                break;
            }
        }
    } while(!u);

    p[i].s = 0;
    p[i].e = 0;
    p[i].a = true;
    
    if(p[i].y >= 0) {
        uNk(p[i].x, 0, p[i].y / 100, p[i].n);
    }
}

void uSc() {
    *h0 = s7[sc % 10] | (s7[(sc / 10) % 10] << 8);
}

int main() {
    pB = *pC;
    dBg(0, 0, 320, 180);
    dEr();

    for(int i = 0; i < 5; i++) sBm(i);
    uSc();

    while(1) {
        int w = *sP & 0x0F;

        for(int i = 0; i < 5; i++) {
            if(!p[i].a) continue;

            if(p[i].s == 0) {
                if(w == p[i].n) {
                    dBg(p[i].x, p[i].y / 100, 24, 24);
                    p[i].s = 1; 
                    p[i].e = 20; 
                    sc++;
                    uSc();
                    
                    for(int j = 0; j < 5; j++) {
                        if(p[j].a && p[j].s == 0) {
                            p[j].v += 5;
                            if(p[j].v > 250) p[j].v = 250;
                        }
                    }
                    
                    for(int k=0; k<16; k++) {
                        p[i].pt[k].x = p[i].x + 12;
                        p[i].pt[k].y = (p[i].y / 100) + 12;
                        p[i].pt[k].vx = (rand() % 7) - 3;
                        p[i].pt[k].vy = (rand() % 7) - 3;
                    }
                    continue;
                }
                
                int oY = p[i].y / 100;
                p[i].y += p[i].v;
                int nY = p[i].y / 100;
                
                if(nY > oY && nY >= 0) {
                    int eO = oY < 0 ? 0 : oY;
                    dBg(p[i].x, eO, 24, nY - eO);
                    uNk(p[i].x, eO, nY, p[i].n);
                }
                
                if(nY + 24 >= 180) {
                    dBg(0, 0, 320, 180);
                    dEr();
                    bDg(60, 100, 10, 0xF800);
                    bDg(72, 100, 11, 0xF800);
                    bDg(84, 100, 12, 0xF800);
                    bDg(96, 100, 13, 0xF800);
                    bDg(120, 100, 14, 0xF800);
                    bDg(132, 100, 15, 0xF800);
                    bDg(144, 100, 13, 0xF800);
                    bDg(156, 100, 16, 0xF800);
                    bNm(180, 100, sc, 0x07E0);
                    while(1); 
                }
            } 
            else if(p[i].s == 1) {
                
                for(int k=0; k<16; k++) {
                    dBg(p[i].pt[k].x, p[i].pt[k].y, 2, 2);
                    
                    p[i].pt[k].x += p[i].pt[k].vx;
                    p[i].pt[k].y += p[i].pt[k].vy;
                    
                    short c = (p[i].e > 10) ? 0xF800 : 0x7800; 
                    dRt(p[i].pt[k].x, p[i].pt[k].y, 2, 2, c);
                }
                
                p[i].e--;
                if(p[i].e <= 0) {
                    for(int k=0; k<16; k++) {
                        dBg(p[i].pt[k].x, p[i].pt[k].y, 2, 2);
                    }
                    sBm(i);
                }
            }
        }
        for(volatile int d = 0; d < 100000; d++);
    }
}