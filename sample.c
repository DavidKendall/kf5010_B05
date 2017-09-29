#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>

#include "lcd.h"

void loc(void)
{
    lcdsetpos(5,2);
    if(ispressed(KEY_UP)){
        lcdwrite("key  pressed");
    }else{
        lcdwrite("              ");
    }
}

int main ( int argc , char *argv[] )
{
    int n = 0;
    lcdinit();

    lcdsetpos(2, 2);
    lcdwrite("hello world");
    lcdsetpos(3,2);
    lcdsetcolour(9, 0);
    lcdsetattr(A_BOLD);
    lcdwrite("\u2615 sit back and enjoy the coffee");

    while(TRUE){
        sleep(1);
        n++;
        loc();
        for (n = 0; n < 4; n++) {
            loc();
            LEDon(n);
            sleep(1);
        }
        for (n = 0; n < 4; n++) {
            loc();
            LEDoff(n);
            sleep(1);
        }
        fprintf(stderr,"%s:%d diagnostic n=%d\n",__FILE__,__LINE__, n );
    }
    sleep(1);
}
