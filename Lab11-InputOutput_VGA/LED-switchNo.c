#include <stdio.h>

#define LEDR_BASE      0xFF200000
#define HEX3_HEX0_BASE 0xFF200020
#define HEX5_HEX4_BASE 0xFF200030
#define SW_BASE        0xFF200040

// 7-segment codes for hex digits 0 to F
// bit pattern: gfedcba (active-high on DE1-SoC HEX display register interface)
int hex_table[16] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F, // 9
    0x77, // A
    0x7C, // b
    0x39, // C
    0x5E, // d
    0x79, // E
    0x71  // F
};

int main() {
    volatile int *led_ptr      = (int *)LEDR_BASE;
    volatile int *hex30_ptr    = (int *)HEX3_HEX0_BASE;
    volatile int *hex54_ptr    = (int *)HEX5_HEX4_BASE;
    volatile int *sw_ptr       = (int *)SW_BASE;

    int sw_value;
    int d0, d1, d2;

    while (1) {
        sw_value = (*sw_ptr) & 0x3FF;   // 10-bit switch value

        // Show switch value on LEDs
        *led_ptr = sw_value;

        // Convert switch value to 3 hex digits
        d0 =  sw_value        & 0xF;
        d1 = (sw_value >> 4)  & 0xF;
        d2 = (sw_value >> 8)  & 0xF;

        // HEX0 = lowest hex digit
        // HEX1 = next hex digit
        // HEX2 = next hex digit
        // HEX3 = blank
        *hex30_ptr = (hex_table[d0]) |
                     (hex_table[d1] << 8) |
                     (hex_table[d2] << 16);

        // HEX5 and HEX4 off
        *hex54_ptr = 0x0;
    }

    return 0;
}