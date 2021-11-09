#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "header.h"
#include "functions.c"

int main(void) {

    int screen = 0;

    while(1) {

        GetUserProducts();

        printf("\e[1;1H\e[2J"); //clear console

        switch (screen) {

            case 1:
            ShowProductsScreen();
            break;

            case 2:
            ShowAddScreen();
            break;

            case 3:
            ShowEditScreen();
            break;

            case 4:
            ShowDeleteScreen();
            break;

            default:
            ShowWelcomeScreen(); 
            break;
        }

        screen = HandleScan(screen);

    }

    
}

