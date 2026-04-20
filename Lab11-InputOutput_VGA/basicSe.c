#include <stdio.h>
#include <stdlib.h>


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
}

int min(int a, int b){
    return (a < b ? a : b);
}

int main(){
    clearScreen();

    int x, y;
    for(x=0; x<320; x++){
        writePixel(x, min(x, 239), 0xf800);
    }

    for(y = 0; y<240; y++){
        writePixel(y, 240-y, 0x07e0);
    }

    char msg[] = "Hello Mfs!";
    char *c = msg;
    x = 15;
    while(c){
        writeChar(x++, 10, *c);
        c++;
    }
    return 0;
}