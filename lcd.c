#define  _XOPEN_SOURCE_EXTENDED 1

#include <unistd.h>
#include <curses.h>
#include <locale.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>

#include "lcd.h"

static short setcolor(short fg, short bg)
{
    static short pairs = 4;
    short p;
    for( p=4 ; p<pairs ; p++){
        short f,b;
        pair_content(p, &f, &b);
        if( f==fg && b==bg ) return p;
    }
    init_pair(p, fg, bg);
    pairs++;
    return p;
}

/*
0x00-0x07:  standard colors (as in ESC [ 30–37 m)
0x08-0x0F:  high intensity colors (as in ESC [ 90–97 m)
0x10-0xE7:  6 × 6 × 6 cube (216 colors): 16 + 36 × r + 6 × g + b (0 ≤ r, g, b ≤ 5)
0xE8-0xFF:  grayscale from black to white in 24 steps
*/
void lcdsetcolor(short fg, short bg)
{
    color_set( setcolor(fg,bg), NULL );
}


void lcdshutdown()
{
    endwin();
}

static WINDOW *led;
static WINDOW *lcd;
static WINDOW *screen;

static bool ledstate[4] = {0,0,0,0};
void drawled(int n, bool s)
{
    wmove(led, 0,8+n*6);
    wcolor_set(led,n,NULL);
    if( s )  mvwaddch(led,0,8+n*6, ' '|A_REVERSE|A_STANDOUT);
    else  mvwaddch(led,0,8+n*6, ACS_BOARD|A_DIM);
    wrefresh(led);
}
void drawleds()
{
    int n;
    for(n=0 ; n<4 ; n++) drawled(n,0);
}

int lcdinit()
{
    setlocale(LC_ALL, "");
    initscr();			    /* Start curses mode              */
    cbreak();			    /* Line buffering disabled        */
    noecho();			    /* Don't echo() while we do getch */
    start_color();
    curs_set(0);


    atexit(lcdshutdown);
    led = newwin(1, 0, 0,0);
    lcd = newwin(0, 0, 1,0);
    screen = derwin(lcd,LINES-3,COLS-2,1,1);
    nodelay(screen,TRUE);
    wcolor_set(lcd,setcolor(7,8), NULL);
    box(lcd,0,0);
    mvwaddstr(lcd,0,1,"lcd");
    wrefresh(lcd);
    wcolor_set(led,setcolor(7,8), NULL);
    wbkgdset(led, COLOR_PAIR(setcolor(7,8)));
    werase(led);
    mvwaddstr(led, 0,0 ," Led   0     1     2     3       ");
    init_pair(1, 9, 8);
    init_pair(2, 10, 8);
    init_pair(3, 12, 8);
    drawleds();
    keypad(screen, TRUE);	/* We get F1, F2 etc..            */
    wrefresh(screen);
    return 1;
}

void lcdsetpos(int row, int column)
{
    wmove(screen,row,column);
}
void lcdsetcolour(int foreground, int background)
{
    wcolor_set(screen,setcolor(foreground,background),NULL);
}
void lcdsetattr(int attributes)
{
    wattron(screen, attributes);
}
void lcdunsetattr(int attributes)
{
    wattroff(screen, attributes);
}
int  lcdwrite(const char *fmt,...)
{
    int ret;
    va_list args;
    va_start(args, fmt);
    ret = vw_printw(screen, fmt, args);
    va_end(args);
    wrefresh(lcd);
    wrefresh(screen);
    return ret;
}

void LEDon(int n)
{
    drawled(n,TRUE);
}
void LEDoff(int n)
{
    drawled(n,FALSE);
}

int ispressed(int button)
{
    return wgetch(screen)==button;
}
