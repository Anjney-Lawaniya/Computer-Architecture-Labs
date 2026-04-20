#include <stdio.h>

#define LEDR_BASE      0xFF200000
#define SW_BASE        0xFF200040
#define HEX3_HEX0_BASE 0xFF200020
#define HEX5_HEX4_BASE 0xFF200030

// ACTIVE-HIGH 7-segment hex decoding array (1 turns a segment ON)
const unsigned char seg[11] = {
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
    0x00  // 10 (Blank / All segments OFF)
};

int main() {
    volatile int *led_ptr    = (int *)LEDR_BASE;
    volatile int *sw_ptr     = (int *)SW_BASE;
    volatile int *hex3_0_ptr = (int *)HEX3_HEX0_BASE;
    volatile int *hex5_4_ptr = (int *)HEX5_HEX4_BASE;

    while (1) {
        // 1. Read switches and calculate 10-bit 2's complement
        int sw_val = (*sw_ptr) & 0x3FF;
        int tc_val = (-sw_val) & 0x3FF;
       
        // Output the raw binary to LEDs (This part was working correctly!)
        *led_ptr = tc_val;

        // 2. Prepare value for decimal 7-segment display
        int signed_val = tc_val;
       
        // Sign-extend if the 10th bit (bit 9) is 1 (meaning it's negative in 10-bit math)
        if (signed_val & 0x0200) {
            signed_val |= 0xFFFFFE00; // Pad the upper 22 bits with 1s
        }

        // 3. Find absolute value and check if we need a negative sign
        int abs_val;
        int is_negative = 0;

        if (signed_val < 0) {
            is_negative = 1;
            abs_val = -signed_val;
        } else {
            abs_val = signed_val;
        }

        // 4. Extract digits (We use index 10 to "blank out" leading zeros)
        int d0 = abs_val % 10;
        int d1 = (abs_val > 9)   ? ((abs_val / 10) % 10)   : 10;
        int d2 = (abs_val > 99)  ? ((abs_val / 100) % 10)  : 10;
        int d3 = (abs_val > 999) ? ((abs_val / 1000) % 10) : 10;

        // 5. Write to HEX displays
        *hex3_0_ptr = (seg[d3] << 24) | (seg[d2] << 16) | (seg[d1] << 8) | seg[d0];

        // 6. Write the negative sign to HEX4 if needed.
        // In Active-High, 0x40 turns ON only the middle segment 'g'. 0x00 is totally blank.
        if (is_negative) {
            *hex5_4_ptr = 0x0040; // HEX5 is blank (00), HEX4 is minus (40)
        } else {
            *hex5_4_ptr = 0x0000; // Both HEX5 and HEX4 are blank
        }
    }

    return 0;
}