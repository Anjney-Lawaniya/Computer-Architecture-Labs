/* Example 4: Draw a checkerboard pattern on the pixel buffer */

void write_pixel(int x, int y, short colour) {
    volatile short *vga_addr = (volatile short*)(0x08000000 + (y << 10) + (x << 1));
    *vga_addr = colour;
}

int main() {
    int x, y;
    short color1 = 0xFFFF; // White
    short color2 = 0x0000; // Black
    int square_size = 20;

    for (y = 0; y < 240; y++) {
        for (x = 0; x < 320; x++) {
            // Determine grid position based on square size
            int grid_x = x / square_size;
            int grid_y = y / square_size;
            
            // Alternate colors based on even/odd coordinates
            if ((grid_x + grid_y) % 2 == 0) {
                write_pixel(x, y, color1);
            } else {
                write_pixel(x, y, color2);
            }
        }
    }
    return 0;
}