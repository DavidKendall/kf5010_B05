#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <assert.h>
#include <pthread.h>
#include <semaphore.h>

#include "lcd.h"

#define N_THREADS 2

sem_t sem;

void *led1Toggle(void * arg) {
    bool isOn = false;

    while (true) {
        if (isOn) {
            sem_wait(&sem);
            LEDoff(1);
            sem_post(&sem);
            isOn = false;
        }
        else {
            sem_wait(&sem);
            LEDon(1);
            sem_post(&sem);
            isOn = true;
        }
        sleep(1);
    }
}

void *led2Toggle(void * arg) {
    bool isOn = false;

    while (true) {
        if (isOn) {
            sem_wait(&sem);
            LEDoff(2);
            sem_post(&sem);
            isOn = false;
        }
        else {
            sem_wait(&sem);
            LEDon(2);
            sem_post(&sem);
            isOn = true;
        }
        sleep(1);
    }
}

int main (void) {
    pthread_t thread[4];
    int rc;
    long i;

    rc = sem_init(&sem, 0, 1);
    assert(rc == 0);

    lcdinit();
    
    rc = pthread_create(&thread[1], NULL, led1Toggle, NULL);
    assert(rc == 0);
    rc = pthread_create(&thread[2], NULL, led2Toggle, NULL);
    assert(rc == 0);

    rc = pthread_join(thread[1], NULL);
    assert(rc == 0);
    rc = pthread_join(thread[2], NULL);
    assert(rc == 0);

    exit(0);
}
