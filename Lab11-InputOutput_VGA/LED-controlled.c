#include <stdio.h>

#define LEDR_BASE 0xFF200000
#define SW_BASE   0xFF200040

int main() {
    volatile int *led_ptr = (int *)LEDR_BASE;
    volatile int *sw_ptr  = (int *)SW_BASE;

    while (1) {
        *led_ptr = (*sw_ptr) & 0x3FF;   // mask to 10 switches / 10 LEDs
    }

    return 0;
}