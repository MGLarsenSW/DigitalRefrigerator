#include <stdint.h>
#include <time.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <inttypes.h>
#include "header.h"
#include "functions/main.c"

int main(void) {

    int64_t screen = 0;
    int64_t numberOfProducts = 0;
    struct Product products[100];

    srand(time(NULL));

    while(screen != StateExit) {

        GetUserProducts(&numberOfProducts, products);

        ClearConsole();

        switch (screen) {

            case StateShowProductsScreen:
            ShowProductsScreen(numberOfProducts, products);
            break;

            case StateShowAddScreen:
            ShowAddScreen();
            break;

            case StateShowEditScreen:
            ShowEditScreen();
            break;

            case StateShowDeleteScreen:
            ShowDeleteScreen(numberOfProducts, products);
            break;

            default:
            ShowWelcomeScreen(); 
            break;
        }

        screen = HandleScan(screen);

    }


}