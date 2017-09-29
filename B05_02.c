#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <assert.h>
#include <pthread.h>
#include <time.h>

#include "lcd.h"

bool flashing = false;
uint32_t count1;
uint32_t count2;
uint32_t total;

void randomDelay(void) {
    int i;
    int delay = rand();
    
    for (i = 0; i < delay; i++) {
        /* skip */
    }
}

void *led1Toggle(void * arg) {
    bool isOn = false;

    while (true) {
        if (flashing) {
            if (isOn) {
                LEDoff(1);
                isOn = false;
            }
            else {
                LEDon(1);
                isOn = true;
            }
            sleep(1);
        }
    }
}

void *count1Thr(void * arg) {
    count1 += 1;
    randomDelay();
    total += 1;
    if ((count1 + count2) != total) {
        flashing = true;
    }
}

void *count2Thr(void * arg) {
    count2 += 1;
    randomDelay();
    total += 1;
    if ((count1 + count2) != total) {
        flashing = true;
    }
}

int main (void) {
    pthread_t thread[3];
    int rc;
    long i;


    lcdinit();
    srand(time(NULL));

    rc = pthread_create(&thread[0], NULL, led1Toggle, NULL);
    assert(rc == 0);
    rc = pthread_create(&thread[1], NULL, count1Thr, NULL);
    assert(rc == 0);
    rc = pthread_create(&thread[2], NULL, count2Thr, NULL);
    assert(rc == 0);

    rc = pthread_join(thread[0], NULL);
    assert(rc == 0);
    rc = pthread_join(thread[1], NULL);
    assert(rc == 0);
    rc = pthread_join(thread[2], NULL);
    assert(rc == 0);

    exit(0);
}
