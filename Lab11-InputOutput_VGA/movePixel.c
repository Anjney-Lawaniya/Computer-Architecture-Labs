#include <stdio.h>
#include <stdlib.h>


void writePixel(int x, int y, short color, volatile short *pixelBuffer){
    volatile short *pixelAddress = (volatile short*)((int)pixelBuffer + (x<<1) + (y<<10));
    *pixelAddress = color;
}

void writeChar(int x, int y, char c){
    volatile char* charAddress = (volatile char*)(0x09000000 + x + (y<<7));
    *charAddress = c;
}

void clearScreen(volatile short *pixelBuffer){
    int x, y;
    for(x = 0; x<320; x++){
        for(y = 0; y<240; y++){
            writePixel(x, y, 0, pixelBuffer);
        }
    }
}

int min(int a, int b){
    return (a < b ? a : b);
}
void waitForVsync() {
    volatile int *pixel_ctrl_ptr = (int *)0xFF203020;
    *pixel_ctrl_ptr = 1; // Start the sync process
    
    // Poll the status bit (bit 0) - wait until it is 0
    while ((*pixel_ctrl_ptr & 0x01) != 0) {
        // Do nothing, just wait
    }
}

int main(){
    volatile int *pixelCtrlPtr = (int *)0xFF203020;
    volatile short *backBuffer = (volatile short *)(*(pixelCtrlPtr + 1));
    clearScreen(backBuffer);
    int x, y;
    for(x = 0; x < 320; x++){
        writePixel(x, 120, 0xF800, backBuffer);
        waitForVsync();
        backBuffer = (volatile short *)(*(pixelCtrlPtr + 1));
    }
}