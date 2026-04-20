/* * DE1-SoC Interactive Square
 * Moves a stylized square using Push Buttons (KEY0 - KEY3)
 */

#define KEY_BASE       0xFF200050 // Address for Push Buttons
#define VGA_PIXEL_BASE 0x08000000 // Address for VGA output

// VGA Screen Limits
#define SCREEN_W 320
#define SCREEN_H 240

// Square settings
#define SQ_SIZE  15 // Slightly larger for better visibility
#define SPEED    10 // Move in larger, crisper increments

/* Standard VGA write function */
void write_pixel(int x, int y, short color) {
    if (x < 0 || x > 319 || y < 0 || y > 239) return; 
    volatile short *vga_addr = (volatile short*)(VGA_PIXEL_BASE + (y << 10) + (x << 1));
    *vga_addr = color;
}

/* Fills the screen with a specific background color */
void clear_screen(short bg_color) {
    int x, y;
    for (x = 0; x < SCREEN_W; x++) {
        for (y = 0; y < SCREEN_H; y++) {
            write_pixel(x, y, bg_color);
        }
    }
}

/* Draws an attractive square with a distinct border and inner fill */
void draw_fancy_square(int start_x, int start_y, short border_color, short fill_color) {
    int i, j;
    for (i = 0; i < SQ_SIZE; i++) {
        for (j = 0; j < SQ_SIZE; j++) {
            // If the pixel is on the outer edge, draw the border color
            if (i == 0 || i == SQ_SIZE - 1 || j == 0 || j == SQ_SIZE - 1) {
                write_pixel(start_x + j, start_y + i, border_color);
            } 
            // Otherwise, fill the inside
            else {
                write_pixel(start_x + j, start_y + i, fill_color);
            }
        }
    }
}

/* Safe hardware delay to "debounce" physical button presses */
void delay(int count) {
    int i;
    for (i = 0; i < count; i++) {
        asm volatile("nop"); 
    }
}

int main() {
    volatile int *btn_ptr = (int *)KEY_BASE;
    
    // Color Palette
    short color_bg     = 0x0010; // Dark Blue
    short color_border = 0xFFFF; // Bright White
    short color_fill   = 0x07E0; // Neon Green

    // 1. Initialize screen with the background color
    clear_screen(color_bg);

    // 2. Start square perfectly centered
    int x = (SCREEN_W - SQ_SIZE) / 2;
    int y = (SCREEN_H - SQ_SIZE) / 2;

    // Draw the initial square
    draw_fancy_square(x, y, color_border, color_fill);

    int prev_btn = 0;

    while (1) {
        // Read current state of the 4 push buttons
        int current_btn = (*btn_ptr) & 0x0F;
        
        // EDGE DETECTION: Only registers the exact moment a button is pressed
        int pressed_this_frame = current_btn & ~prev_btn;
        
        // Update prev_btn for the next loop iteration
        prev_btn = current_btn;

        // If any button was freshly pressed this exact moment
        if (pressed_this_frame) {
            
            // 1. Erase current position (overwrite with background color)
            draw_fancy_square(x, y, color_bg, color_bg);

            // 2. Update coordinates
            if (pressed_this_frame & 0x01) x -= SPEED; // KEY0: Left
            if (pressed_this_frame & 0x02) y -= SPEED; // KEY1: Up
            if (pressed_this_frame & 0x04) x += SPEED; // KEY2: Right
            if (pressed_this_frame & 0x08) y += SPEED; // KEY3: Down

            // 3. Boundary Checks (keep it strictly inside the screen)
            if (x < 0) x = 0;
            if (x > SCREEN_W - SQ_SIZE) x = SCREEN_W - SQ_SIZE;
            if (y < 0) y = 0;
            if (y > SCREEN_H - SQ_SIZE) y = SCREEN_H - SQ_SIZE;

            // 4. Draw at the newly calculated position
            draw_fancy_square(x, y, color_border, color_fill);
            
            // 5. Debounce delay so a long press doesn't register multiple times
            delay(150000);
        }
    }

    return 0;
}