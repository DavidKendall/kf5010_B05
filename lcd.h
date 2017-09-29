/* some constants */
#include <curses.h>

/* LCD api */
int  lcdinit(void);  /* initialise LCD return sucess/fail */
void lcdsetpos(int row, int column);
/*
0x00-0x07:  standard colors (as in ESC [ 30–37 m)
0x08-0x0F:  high intensity colors (as in ESC [ 90–97 m)
0x10-0xE7:  6 × 6 × 6 cube (216 colors): 16 + 36 × r + 6 × g + b (0 ≤ r, g, b ≤ 5)
0xE8-0xFF:  grayscale from black to white in 24 steps
*/
void lcdsetcolour(int foreground, int background);
void lcdsetattr(int attributes);
void lcdunsetattr(int attributes);
int  lcdwrite(const char *fmt,...);

/* LED api */
void LEDon(int n);
void LEDoff(int n);

/* Button api */
int ispressed(int button);
