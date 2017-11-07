#define GRAPHICS_HEADER 1

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
/* VGA sizes of the screen */

struct terminal {
  size_t t_row;         /* Actual row */
  size_t t_col;         /* Actual column */
  uint8_t t_color;      /* Terminal text color */
  uint16_t * t_buffer;  /* Terminal text buffer */
};
/* Definition of the terminal used by the user */

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

static struct terminal t;
/* Actual terminal */

static inline uint8_t
vga_entry_color(enum vga_color fg, enum vga_color bg) {
  return fg | bg << 4;
}
/* Creates a new color for the terminal */

void
terminal_init() {
  t.t_row = 0;
  t.t_col = 0;
  t.t_color =
}
