/* * Complex VGA Pattern Generator for DE1-SoC
 * Includes an XOR fractal background, geometric framing, and text overlay.
 */

/* Set a single pixel on the screen at x,y
 * x in [0,319], y in [0,239], and colour in [0,65535]
 */
void write_pixel(int x, int y, short colour) {
    volatile short *vga_addr = (volatile short*)(0x08000000 + (y << 10) + (x << 1));
    *vga_addr = colour;
}

/* Set entire screen to black */
void clear_screen() {
    int x, y;
    for (x = 0; x < 320; x++) {
        for (y = 0; y < 240; y++) {
            write_pixel(x, y, 0); // 0 is black
        }
    }
}

/* Clear the character buffer (80 columns x 60 rows) */
void clear_char_buffer() {
    int x, y;
    for (x = 0; x < 80; x++) {
        for (y = 0; y < 60; y++) {
            volatile char * character_buffer = (char *) (0x09000000 + (y << 7) + x);
            *character_buffer = ' '; // Write space character to clear
        }
    }
}

/* Write a single character to the character buffer at x,y
 * x in [0,79], y in [0,59]
 */
void write_char(int x, int y, char c) {
    volatile char * character_buffer = (char *) (0x09000000 + (y << 7) + x);
    *character_buffer = c;
}

/* Helper function to draw a hollow rectangle */
void draw_rectangle(int x1, int y1, int x2, int y2, short colour) {
    int x, y;
    // Top and bottom borders
    for (x = x1; x <= x2; x++) {
        write_pixel(x, y1, colour);
        write_pixel(x, y2, colour);
    }
    // Left and right borders
    for (y = y1; y <= y2; y++) {
        write_pixel(x1, y, colour);
        write_pixel(x2, y, colour);
    }
}

/* Helper function to write a full string to the character buffer */
void write_string(int x, int y, char* str) {
    while (*str) {
        write_char(x, y, *str);
        x++;
        str++;
    }
}

int main() {
    // 1. Initialize and clear displays
    clear_screen();
    clear_char_buffer();
    
    int x, y;

    // 2. Generate a Complex XOR Fractal Background
    // This loops through all 320x240 pixels and calculates a color based on their coordinates.
    for (y = 0; y < 240; y++) {
        for (x = 0; x < 320; x++) {
            // Use bitwise XOR on coordinates to generate geometric patterns
            short red_comp = ((x ^ y) >> 3) & 0x1F;      // 5 bits for Red
            short green_comp = ((x ^ (y * 2)) >> 2) & 0x3F; // 6 bits for Green
            short blue_comp = (((x * 2) ^ y) >> 3) & 0x1F;  // 5 bits for Blue
            
            // Shift components into the 16-bit 5-6-5 color format
            short colour = (red_comp << 11) | (green_comp << 5) | blue_comp;
            
            write_pixel(x, y, colour);
        }
    }

    // 3. Draw Geometric Overlays (Nested Rectangles)
    // 0xFFFF is White, 0xF800 is Red, 0x07E0 is Green, 0x001F is Blue
    draw_rectangle(10, 10, 309, 229, 0xFFFF); // Outer white border
    draw_rectangle(12, 12, 307, 227, 0xF800); // Inner red border
    draw_rectangle(80, 80, 240, 160, 0x001F); // Center blue box border 1
    draw_rectangle(82, 82, 238, 158, 0x07E0); // Center green box border 2
    
    // Fill the center box with a solid dark gray to make text readable
    // Gray represented by 0x8410
    for (y = 83; y <= 157; y++) {
        for (x = 83; x <= 237; x++) {
            write_pixel(x, y, 0x8410); 
        }
    }

    // 4. Write formatted text to the Character Buffer
    // Note: Character grid is 80x60. The center box is roughly x:20 to 60, y: 20 to 40 in char coordinates.
    write_string(30, 25, "DE1-SoC SYSTEM");
    write_string(27, 27, "VGA ADAPTER ONLINE");
    write_string(25, 30, "Complex Pattern Loaded");
    write_string(33, 35, "[OK]");

    return 0;
}