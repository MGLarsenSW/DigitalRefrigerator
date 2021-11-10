#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "header.h"
#include "functions.c"

int main(void) {

    int screen = 0;
    int numberOfProducts = 0;
    struct Product products[100];

    while(screen != 5) {

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
            ShowDeleteScreen();
            break;

            default:
            ShowWelcomeScreen(); 
            break;
        }

        screen = HandleScan(screen);

    }

    
}

