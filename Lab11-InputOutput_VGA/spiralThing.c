#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void writePixel(int x, int y, short color){
    volatile short *pixelAddress = (volatile short*)(0x08000000 + (x<<1) + (y<<10));
    *pixelAddress = color;
}

void writeChar(int x, int y, char c){
    volatile char* charAddress = (volatile char*)(0x09000000 + x + (y<<7));
    *charAddress = c;
}

void clearScreen(){
    int x, y;
    for(x = 0; x<320; x++){
        for(y = 0; y<240; y++){
            writePixel(x, y, 0);
        }
    }
    for(x = 0; x<80; x++){
        for(y = 0; y<60; y++){
            writeChar(x, y, 0);
        }
    }
}

int min(int a, int b){
    return (a < b ? a : b);
}

bool check(int x, int y){
    if(x < 0 || y < 0 || x >= 320 || y >= 240){return true;}
    return false;
}

void doTheSpiral(int delta, short color){
    int x, y;
    int diff = delta;
    int c = 1, dx = 1, dy = 1, z;
    x = 160; y = 120;
    while(true){
        int tmp = 0;

        if(c == 1){
            for(z=0; z<delta; z++){
                y += (-1)*dy;
                if(check(x, y)){tmp = 0; break;}
                writePixel(x, y, color);
                tmp = 1;
            }
            dy *= -1;
        }
        else{
            for(z=0; z<delta; z++){
                x += (-1)*dx;
                if(check(x, y)){tmp = 0; break;}
                writePixel(x, y, color);
                tmp = 1;
            }
            dx *= -1;
            delta += diff;
        }


        c *= -1;
        if(!tmp){break;}
    }
}

int main(){
    clearScreen();
    int x, y;

    doTheSpiral(10, 0xffff);
    doTheSpiral(7, 0xf800);
    doTheSpiral(6, 0xf0fb);

    return 0;
}