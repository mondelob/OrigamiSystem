
#include <stddef.h>
#include <stdint.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

enum vga_color {
  VGA_COLOR_BLACK = 0,
  VGA_COLOR_BLUE = 1,
  VGA_COLOR_GREEN = 2,
  VGA_COLOR_CYAN = 3,
  VGA_COLOR_RED = 4,
  VGA_COLOR_MAGENTA = 5,
  VGA_COLOR_BROWN = 6,
  VGA_COLOR_LIGHT_GRAY = 7,
  VGA_COLOR_GRAY = 8,
  VGA_COLOR_LIGHT_BLUE = 9,
  VGA_COLOR_LIGHT_GREEN = 10,
  VGA_COLOR_LIGHT_CYAN = 11,
  VGA_COLOR_LIGHT_RED = 12,
  VGA_COLOR_LIGHT_MAGENTA = 13,
  VGA_COLOR_YELLOW = 14,
  VGA_COLOR_WHITE = 15
};
/* Enumeration of all the VGA colors */

struct terminal {
  size_t t_row;         /* Actual row */
  size_t t_col;         /* Actual column */
  uint8_t t_color;      /* Terminal text color */
  uint16_t * t_buffer;  /* Terminal text buffer */
};
/* Struct containing the actual terminal values */

static struct terminal t;
/* Terminal used by the user */

static inline uint8_t
vga_entry_color(enum vga_color fg, enum vga_color bg) {
  return fg | bg << 4;
}

static inline uint16_t
vga_entry(unsigned char uc, uint8_t color) {
  return (uint16_t) uc | (uint16_t) color << 8;
}

static size_t
strlen(char * s) {
  size_t len = 0;
  while(s[len])
    len++;
  return len;
}
/* Returns the size of a string */

void
terminal_clean() {
  for (size_t y = 0; y < VGA_HEIGHT; y++)
    for (size_t x = 0; x < VGA_WIDTH; x++)
      t.t_buffer[y * VGA_WIDTH + x] = vga_entry(' ', t.t_color);
}
/* Cleans the terminal all text */

void
terminal_setcolor(uint8_t color) {
  t.t_color = color;
}

void
terminal_init() {
  t.t_row = 0;
  t.t_col = 0;
  terminal_setcolor(vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK));
  t.t_buffer = (uint16_t*) 0xB8000;
  terminal_clean();
}
/* Initializes the terminal */

void
terminal_put(char c, uint8_t color, size_t x, size_t y) {
  t.t_buffer[y * VGA_WIDTH + x] = vga_entry(c, color);
}

void
terminal_putchar(char c) {
  terminal_put(c, t.t_color, t.t_col, t.t_row);
  if (++t.t_col == VGA_WIDTH) {
    t.t_col = 0;
    if (++t.t_row == VGA_HEIGHT) {
      t.t_row = 0;
    }
  }
}

void
terminal_newline() {
  t.t_col = 0;
  if (++t.t_row == VGA_HEIGHT)
    t.t_row = 0;
}

size_t
terminal_write(char * s, size_t size) {
  size_t i;
  for (i = 0; i < size; i++) {
    switch (s[i]) {
      case 10:
        terminal_newline();
        break;
      default:
        terminal_putchar(s[i]);
        break;
    }
  }
  return i;
}

size_t
terminal_print(char * s) {
  return terminal_write(s, strlen(s));
}
/* Writes a string on the terminal */

void
kernel_main(void) {
  terminal_init();
  terminal_print("Hello World!\n");
  terminal_setcolor(vga_entry_color(VGA_COLOR_RED, VGA_COLOR_BLACK));
  terminal_print("How are you?\n");
  terminal_setcolor(vga_entry_color(VGA_COLOR_YELLOW, VGA_COLOR_BLACK));
  terminal_print("Wow! :D\n");
  terminal_setcolor(vga_entry_color(VGA_COLOR_CYAN, VGA_COLOR_MAGENTA));
  terminal_print("Changing back color\n");
}
/* Main function called by the bootloader */
