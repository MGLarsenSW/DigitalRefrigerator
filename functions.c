void ClearConsole() {

    #ifdef _WIN32
        system("cls");
    #else //In any other OS
        system("clear");
    #endif

}

int HandleScan(int screen) {

    if(screen) {
        printf("ENTER 'Q' TO GO BACK\n\n");
    }

    char ch;

    scanf(" %c", &ch);

    if(toupper(ch) == 'A') { return 1; }
    if(toupper(ch) == 'B') { return 2; }
    if(toupper(ch) == 'C') { return 3; }
    if(toupper(ch) == 'D') { return 4; }
    if(toupper(ch) == 'Q' && !screen) { return 5; }

    return 0;
}

void ShowWelcomeScreen() {

    printf("YOU HAVE THE FOLLOWING OPTIONS:\n\n");

    printf("A:  VIEW YOUR INVENTORY       B:  ADD PRODUCT\n\n");
    printf("C:  EDIT PRODUCT              D:  DELETE PRODUCT\n\n");
    printf("Q:  EXIT PROGRAM\n\n");

}

void ShowProductsScreen(int numberOfProducts, struct Product products[]) {

    printf("YOU HAVE THE FOLLOWING ITEMS IN YOUR INVENTORY:\n\n");

    for (int i = 0; i < numberOfProducts; i++)
    {
        
        printf("%d. %s \n", i, products[i].name);
        printf("EXPIRE: %d \n\n", products[i].date);

    }
    if (numberOfProducts == 0){
        printf("YOU HAVE NOTHING IN THE INVENTORY AT THE MOMENT\n\n");
    }
    
}

void ShowDeleteScreen() {

    printf("DELETE SCREEN:\n");
    
}

void ShowEditScreen() {

    printf("EDIT SCREEN\n\n");
    
}

void ShowAddScreen() {

    int id, barcode, date;

    printf("\nSCAN THE BARCODE ON THE PRODUCT\n\n");
    scanf(" %d", &barcode);

    char* name = strtok(GetName(barcode), "\n");

    ClearConsole();

    if(atoi(name) == 1) {

        printf("\nTHE PRODUCT IS NOT IN OUR DATABASE.\nPLEASE ENTER THE NAME OF THE PRODUCT.\n\n");
        scanf(" %[^\n]%*c", name);

        ClearConsole();

    }

    FILE* fp = fopen("database/user_products.txt", "a+");

    if(!fp){
        printf("CAN'T OPEN 'USER_PRODUCTS' FILE\n");
    }

    printf("\nYOU HAVE SCANNED: %s\n", name);

    printf("\nPLEASE ENTER THE PRODUCTS EXPIRAION DATE\n\n");
    scanf(" %d", &date);

    srand(time(NULL));
    id = rand();

    fprintf(fp, "%d,%d,%s,%d\n", id, barcode, name, date);

    printf("\nTHE PRODUCT WAS ADDED SUCCESSFULLY!\n\n");

    printf("IF YOU WANT TO ADD A NEW PRODUCT, PRESS B\n\n");

    fclose(fp);

}

// https://stackoverflow.com/questions/10131464/returning-a-char-pointer-in-c
char* strdup(const char* org)
{
    if(org == NULL) return NULL;

    char* newstr = malloc(strlen(org)+1);
    char* p;

    if(newstr == NULL) return NULL;

    p = newstr;

    while(*org) *p++ = *org++; /* copy the string. */
    return newstr;
}

char* GetName(int id) {

    FILE* fp = fopen("database/barcode_list.txt", "r");

    if(!fp){ printf("CAN'T OPEN 'BARCODE_LISTE' FILE\n");

    } else {

        char buffer[1024];
        int row = 0;

        while(fgets(buffer, 1024, fp)) {

            row++;

            if(row == 1) { continue; }

            // Splitting the data
            char* value = strtok(buffer, ",");
            
            int number = atoi(value);

            if(number == id) {

                value = strtok(NULL, ",");
                
                return strdup(value);

            }
            
        }

        fclose(fp);
    }

    return strdup("1");

}

void GetUserProducts(int *number, struct Product *products) {

    FILE* fp = fopen("database/user_products.txt", "r");

    if(!fp){ printf("CAN'T OPEN 'USER_PRODUCTS' FILE\n");

    } else {

        char buffer[1024];
        int row = 0;

        while(fgets(buffer, 1024, fp)) {

            row++;

            if(row == 1) { continue; }

            // Splitting the data
            char* value = strtok(buffer, ",");

            int column = 0;
            
            while(value){

                if (column == 0) {
                    products[row-2].id = atoi(value);
                }

                if (column == 1) {
                    products[row-2].barcode = atoi(value);
                }

                if (column == 2) {
                    products[row-2].name = strdup(value);
                }

                if (column == 3) {
                    products[row-2].date = atoi(value);
                }

                *number = row-1;

                value = strtok(NULL, ",");
                column++;
            }
            
        }

        fclose(fp);
    }

}