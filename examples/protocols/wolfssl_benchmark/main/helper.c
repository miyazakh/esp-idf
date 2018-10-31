/*
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sdkconfig.h"

#define WOLFSSL_BENCH_ARGV              CONFIG_BENCH_ARGV

char* __argv[22];

int construct_argv()
{
    int cnt = 0;
    int i = 0;
    int len = 0;
    char *_argv;            /* buffer for copying the string    */
    char *ch;               /* char pointer to trace the string */
    char buff[16] = { 0 };  /* buffer for a argument copy       */

    printf("arg:%s\n", CONFIG_BENCH_ARGV);
    len = strlen(CONFIG_BENCH_ARGV);
    _argv = (char*)malloc(len + 1);
    if (!_argv) {
        return -1;
    }
    memset(_argv, 0, len+1);
    memcpy(_argv, CONFIG_BENCH_ARGV, len);
    _argv[len] = '\0';
    ch = _argv;

    __argv[cnt] = malloc(10);
    sprintf(__argv[cnt], "benchmark");
    __argv[9] = '\0';
    cnt = 1;

    while (*ch != '\0')
    {
        /* skip white-space */
        while (*ch == ' ') { ++ch; }

        memset(buff, 0, sizeof(buff));
        /* copy each args into buffer */
        i = 0;
        while ((*ch != ' ') && (*ch != '\0') && (i < 16)) {
            buff[i] = *ch;
            ++i;
            ++ch;
        }
        /* copy the string into argv */
        __argv[cnt] = (char*)malloc(i + 1);
        memset(__argv[cnt], 0, i + 1);
        memcpy(__argv[cnt], buff, i + 1);
        /* next args */
        ++cnt;
    }

    free(_argv);

    return (cnt);
}
