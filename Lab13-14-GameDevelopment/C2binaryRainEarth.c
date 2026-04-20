#include <stdbool.h>
#include <stdlib.h>

volatile int *pC = (int *)0xFF203020;
volatile int *sP = (int *)0xFF200040;
volatile int *h0 = (int *)0xFF200020;

char s7[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x67};

int fD[17][5] = {
    {7,5,5,5,7}, {2,6,2,2,7}, {7,1,7,4,7}, {7,1,7,1,7},
    {5,5,7,1,1}, {7,4,7,1,7}, {7,4,7,5,7}, {7,1,1,1,1},
    {7,5,7,5,7}, {7,5,7,1,7}, {7,4,5,5,7}, {2,5,7,5,5},
    {5,7,5,5,5}, {7,4,7,4,7}, {7,5,5,5,7}, {5,5,5,2,2},
    {7,5,7,4,5}
};

short cA[] = {0x07FF, 0xFFE0, 0x07E0, 0xF81F, 0xFFFF, 0xFD20};

typedef struct {
    int x, y, v, n, s, e;
    short c;
    bool a;
} P;

P p[5];
int sc = 0;
int pB;

void pPx(int x, int y, short c) {
    *(short *)(pB + (y << 10) + (x << 1)) = c;
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
                
                if (c1 < 1200 || c2 < 2000 || c3 < 1600 || c4 < 800) {
                    c = 0x07E0;
                }
                
                if (dx*dx + dy*dy > 99000) {
                    c = 0x07FF;
                }
                
                pPx(i, j, c);
            } else {
                short c = 0x0000;
                if((i * 23 + j * 19) % 313 == 0) c = 0x5AEB;
                pPx(i, j, c);
            }
        }
    }
}

void cVa() {
    dBg(0, 0, 320, 180);
    dEr();
}

void dRt(int x, int y, int w, int h, short c) {
    for(int i = 0; i < w; i++)
        for(int j = 0; j < h; j++)
            pPx(x + i, y + j, c);
}

void dRd(int x, int y, short c) {
    for(int i = 0; i < 24; i++) {
        for(int j = 0; j < 24; j++) {
            int dx = i - 12;
            int dy = j - 12;
            if(dx*dx + dy*dy <= 144) {
                pPx(x + i, y + j, c);
            }
        }
    }
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

void sBk(int i) {
    p[i].x = (i * 64) + 20;
    p[i].y = 0;
    p[i].v = 60 + (sc * 4);
    if(p[i].v > 250) p[i].v = 250;
    p[i].n = (rand() % 10) + 1;
    p[i].c = cA[rand() % 6];
    p[i].s = 0;
    p[i].e = 0;
    p[i].a = true;
    dRd(p[i].x, 0, p[i].c);
    dNm(p[i].x + 8, 9, p[i].n, 0x0000);
}

void uSc() {
    *h0 = s7[sc % 10] | (s7[(sc / 10) % 10] << 8);
}

int main() {
    pB = *pC;
    cVa();

    for(int i = 0; i < 5; i++) sBk(i);
    uSc();

    while(1) {
        int w = *sP & 0x0F;

        for(int i = 0; i < 5; i++) {
            if(!p[i].a) continue;

            if(p[i].s == 0) {
                if(w == p[i].n) {
                    p[i].s = 1;
                    p[i].e = 12; 
                    sc++;
                    uSc();
                    for(int j = 0; j < 5; j++) {
                        if(p[j].a && p[j].s == 0) {
                            p[j].v += 5;
                            if(p[j].v > 250) p[j].v = 250;
                        }
                    }
                    continue;
                }

                int oY = p[i].y / 100;
                p[i].y += p[i].v;
                int nY = p[i].y / 100;

                if(nY > oY) {
                    dBg(p[i].x, oY, 24, nY - oY);
                    dRd(p[i].x, nY, p[i].c);
                    dNm(p[i].x + 8, nY + 9, p[i].n, 0x0000);
                }

                if(nY + 24 >= 180) {
                    cVa();
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
            } else if(p[i].s == 1) {
                int pyB = p[i].y / 100;
                for(int ex = 0; ex < 24; ex++) {
                    for(int ey = 0; ey < 24; ey++) {
                        int px = p[i].x + ex;
                        int py = pyB + ey;
                        if((rand() % 45) < p[i].e) {
                            short ec = (rand() % 2 == 0) ? 0xF800 : ((rand() % 2 == 0) ? 0xFFE0 : 0xFFFF);
                            pPx(px, py, ec);
                        } else {
                            short cBg = 0x0000;
                            if((px * 23 + py * 19) % 313 == 0) cBg = 0x5AEB;
                            pPx(px, py, cBg);
                        }
                    }
                }
                p[i].e--;
                if(p[i].e <= 0) {
                    dBg(p[i].x, pyB, 24, 24);
                    sBk(i);
                }
            }
        }
        for(volatile int d = 0; d < 110000; d++);
    }
}