#include <stdint.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <inttypes.h>
#include "header.h"
#include "functions.c"

int main(void) {

    int64_t screen = 0;
    int64_t numberOfProducts = 0;
    struct Product products[100];

    srand(time(NULL));

    printf("time: %lld", stringtotime("5-8-2039"));

    /*while(screen != 5) {

        GetUserProducts(&numberOfProducts, products);

        ClearConsole();

        switch (screen) {

            case 1:
            ShowProductsScreen(numberOfProducts, products);
            break;

            case 2:
            ShowAddScreen();
            break;

            case 3:
            ShowEditScreen();
            break;

            case 4:
            ShowDeleteScreen(numberOfProducts, products);
            break;

            default:
            ShowWelcomeScreen(); 
            break;
        }

        screen = HandleScan(screen);

    }*/


}