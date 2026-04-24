// ANJNEY LAWANIYA - 2402CS11
// BINARY DEFENSE
#include <stdbool.h>
#include <stdlib.h>

// Hardware macro definitions mapping directly to physical memory addresses
#define VGA_CTRL ((volatile int *)0xFF203020)
#define SW_BASE  ((volatile int *)0xFF200040)
#define HEX_BASE ((volatile int *)0xFF200020)
#define PS2_BASE ((volatile int *)0xFF200100)

// Hexadecimal bitmasks for 7-segment display digits
char s7[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x67};

// Binary pixel patterns for drawing on-screen digits
int fD[17][5] = {
    {7,5,5,5,7}, {2,6,2,2,7}, {7,1,7,4,7}, {7,1,7,1,7},
    {5,5,7,1,1}, {7,4,7,1,7}, {7,4,7,5,7}, {7,1,1,1,1},
    {7,5,7,5,7}, {7,5,7,1,7}, {7,4,5,5,7}, {2,5,7,5,5},
    {5,7,5,5,5}, {7,4,7,4,7}, {7,5,5,5,7}, {5,5,5,2,2},
    {7,5,7,4,5}
};

// Particle struct for explosion physics
typedef struct {
    int x, y, vx, vy;
} tP;

// Bomb struct storing position, velocity, target number, and state
typedef struct {
    int x, y, v, n, s, e;
    tP pt[16];
    bool a;
} pN;

pN p[5];
int sc = 0;
int pB;
int bK = 0;
int lS = -1;

// Drains PS/2 FIFO and returns validated key press
int readKey() {
    int w = 0;
    while(1) {
        int d = *PS2_BASE;
        if(!(d & 0x8000)) break;
        int c = d & 0xFF;
        if(c == 0xF0) {
            bK = 1;
        } else if(bK) {
            bK = 0;
        } else {
            if(c == 0x16 || c == 0x69) w = 1;
            if(c == 0x1E || c == 0x72) w = 2;
            if(c == 0x26 || c == 0x7A) w = 3;
            if(c == 0x25 || c == 0x6B) w = 4;
            if(c == 0x2E || c == 0x73) w = 5;
            if(c == 0x36 || c == 0x74) w = 6;
            if(c == 0x3D || c == 0x6C) w = 7;
            if(c == 0x3E || c == 0x75) w = 8;
            if(c == 0x46 || c == 0x7D) w = 9;
            if(c == 0x45 || c == 0x70) w = 10;
        }
    }
    return w;
}

// Writes a 16-bit color to a specific VGA memory offset safely
void drawPixel(int x, int y, short c) {
    if(x >= 0 && x < 320 && y >= 0 && y < 240) {
        // Casting as volatile short forces architecture-safe hardware I/O writes
        *(volatile short *)(pB + (y << 10) + (x << 1)) = c;
    }
}

// Clears an area by drawing the space grid pattern
void drawBackground(int x, int y, int w, int h) {
    for(int i = 0; i < w; i++) {
        for(int j = 0; j < h; j++) {
            int px = x + i;
            int py = y + j;
            short c = 0x0000;
            if((px * 23 + py * 19) % 313 == 0) c = 0x5AEB;
            drawPixel(px, py, c);
        }
    }
}

// Uses circle equation to render the curved Earth horizon
void drawEarth() {
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
                drawPixel(i, j, c);
            } else {
                short c = 0x0000;
                if((i * 23 + j * 19) % 313 == 0) c = 0x5AEB;
                drawPixel(i, j, c);
            }
        }
    }
}

// Draws a solid filled rectangle
void drawRect(int x, int y, int w, int h, short c) {
    for(int i = 0; i < w; i++)
        for(int j = 0; j < h; j++)
            drawPixel(x + i, y + j, c);
}

// Renders a single digit using the 5-row bit patterns
void plotDigit(int dx, int dy, int d, short c) {
    for(int i = 0; i < 5; i++) {
        int v = fD[d][i];
        if(v & 4) drawPixel(dx, dy + i, c);
        if(v & 2) drawPixel(dx + 1, dy + i, c);
        if(v & 1) drawPixel(dx + 2, dy + i, c);
    }
}

// Splits a number into tens/units and plots them
void drawNumber(int nx, int ny, int n, short c) {
    int q = n / 10;
    int r = n % 10;
    if(q > 0) {
        plotDigit(nx, ny, q, c);
        plotDigit(nx + 5, ny, r, c);
    } else {
        plotDigit(nx + 3, ny, r, c);
    }
}

// Renders a bold, upscaled digit for the game over screen
void boxDigit(int dx, int dy, int d, short c) {
    for(int i = 0; i < 5; i++) {
        int v = fD[d][i];
        if(v & 4) drawRect(dx, dy + i*3, 3, 3, c);
        if(v & 2) drawRect(dx + 3, dy + i*3, 3, 3, c);
        if(v & 1) drawRect(dx + 6, dy + i*3, 3, 3, c);
    }
}

// Splits and draws a bold, upscaled number
void boxNumber(int nx, int ny, int n, short c) {
    int q = n / 10;
    int r = n % 10;
    if(q > 0) {
        boxDigit(nx, ny, q, c);
        boxDigit(nx + 12, ny, r, c);
    } else {
        boxDigit(nx, ny, r, c);
    }
}
// ANJNEY LAWANIYA - 2402CS11
// BINARY DEFENSE
// Draws the olive drab bomb chassis and its target decimal
void drawNuke(int x, int oY, int nY, int n) {
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
            if(iN) drawPixel(px, py, cN);
            else {
                short cB = 0x0000;
                if((px * 23 + py * 19) % 313 == 0) cB = 0x5AEB;
                drawPixel(px, py, cB);
            }
        }
    }
    drawNumber(x + 7, nY + 10, n, 0xFFFF);
}

// Initializes a new bomb with guaranteed unique target number
void spawnBomb(int i) {
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
        drawNuke(p[i].x, 0, p[i].y / 100, p[i].n);
    }
}

// Pushes the player's current score to the HEX hardware
void updateScore() {
    *HEX_BASE = s7[sc % 10] | (s7[(sc / 10) % 10] << 8);
}

// Primary execution loop managing states, inputs, and drawing
int main() {
    pB = *VGA_CTRL;
    drawBackground(0, 0, 320, 180);
    drawEarth();

    for(int i = 0; i < 5; i++) spawnBomb(i);
    updateScore();

    while(1) {
        int kb = readKey();
        int cS = *SW_BASE & 0x0F;
        int sw = 0;
        
        // Edge-trigger the slide switches
        if(cS != lS) {
            sw = cS;
            lS = cS;
        }

        for(int i = 0; i < 5; i++) {
            if(!p[i].a) continue;

            if(p[i].s == 0) {
                bool kH = (kb == p[i].n);
                bool sH = (sw == p[i].n);
                
                // Process hit detection and trigger explosion state
                if(kH || sH) {
                    drawBackground(p[i].x, p[i].y / 100, 24, 24);
                    p[i].s = 1; 
                    p[i].e = 20; 
                    sc++;
                    updateScore();
                    
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
                    
                    if(kH) kb = 0; 
                    if(sH) sw = 0; 
                    continue;
                }
                
                // Process gravity and downward translation
                int oY = p[i].y / 100;
                p[i].y += p[i].v;
                int nY = p[i].y / 100;
                
                if(nY > oY && nY >= 0) {
                    int eO = oY < 0 ? 0 : oY;
                    drawBackground(p[i].x, eO, 24, nY - eO);
                    drawNuke(p[i].x, eO, nY, p[i].n);
                }
                
                // Trigger game over screen
                if(nY + 24 >= 180) {
                    drawBackground(0, 0, 320, 180);
                    drawEarth();
                    boxDigit(60, 100, 10, 0xF800);
                    boxDigit(72, 100, 11, 0xF800);
                    boxDigit(84, 100, 12, 0xF800);
                    boxDigit(96, 100, 13, 0xF800);
                    boxDigit(120, 100, 14, 0xF800);
                    boxDigit(132, 100, 15, 0xF800);
                    boxDigit(144, 100, 13, 0xF800);
                    boxDigit(156, 100, 16, 0xF800);
                    boxNumber(180, 100, sc, 0x07E0);
                    while(1); 
                }
            } 
            else if(p[i].s == 1) {
                // Render outward particle physics
                for(int k=0; k<16; k++) {
                    drawBackground(p[i].pt[k].x, p[i].pt[k].y, 2, 2);
                    
                    p[i].pt[k].x += p[i].pt[k].vx;
                    p[i].pt[k].y += p[i].pt[k].vy;
                    
                    short c = (p[i].e > 10) ? 0xF800 : 0x7800; 
                    drawRect(p[i].pt[k].x, p[i].pt[k].y, 2, 2, c);
                }
                
                p[i].e--;
                if(p[i].e <= 0) {
                    for(int k=0; k<16; k++) {
                        drawBackground(p[i].pt[k].x, p[i].pt[k].y, 2, 2);
                    }
                    spawnBomb(i);
                }
            }
        }
        
        // Frame pacing delay completely isolated from volatile memory behavior
        for(int d = 0; d < 100000; d++) {
            __asm__ volatile ("");
        }
    }
}

// ANJNEY LAWANIYA - 2402CS11
// BINARY DEFENSE