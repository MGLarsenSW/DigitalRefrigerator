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

    //printf("+----------------------------------------------------+\n");
    //printf("|                        MENU                        |\n");
    //printf("+----------------------------------------------------+\n\n");

    dprint("\n## MENU ##\n\n", '3');

    dprint("A:  VIEW YOUR INVENTORY       ",'1'); dprint("B:  ADD PRODUCT\n\n",'2');
    dprint("C:  EDIT PRODUCT              ",'6'); dprint("D:  DELETE PRODUCT\n\n",'4');
    dprint("Q:  EXIT PROGRAM\n\n", '8');

} 

void ShowProductsScreen(int numberOfProducts, struct Product products[]) {

    printf("YOU HAVE THE FOLLOWING ITEMS IN YOUR INVENTORY (%d):\n\n", numberOfProducts);

    for (int i = 0; i < numberOfProducts; i++) {

        char id[50];
        snprintf(id, sizeof(id), "ID: %d \n", products[i].id);
        dprint(id, '3');

        char name[50];
        snprintf(name, sizeof(name), "%s \n", products[i].name);
        dprint(name, '4');

        char date[50];
        snprintf(date, sizeof(date), "EXPIRE: %s \n\n", timetostring(products[i].date));
        dprint(date, '5');

    }

    if (numberOfProducts == 0) {
        printf("YOU HAVE NOTHING IN YOUR INVENTORY AT THE MOMENT\n\n");
    }
    
}

// http://www.tutorialspanel.com/delete-a-specific-line-from-a-text-file-using-c/index.htm
void ShowDeleteScreen(int numberOfProducts, struct Product products[]) {

    int id, lineOfProduct = 0, line = 0;
    char copy;

    printf("YOU HAVE THE FOLLOWING ITEMS IN YOUR INVENTORY (%d):\n\n", numberOfProducts);

    for (int i = 0; i < numberOfProducts; i++)
    {
        
        printf("ID: %d \n", products[i].id);
        printf("%s \n", products[i].name);
        printf("EXPIRE: %s \n\n", timetostring(products[i].date));

    }
    if (numberOfProducts == 0){
        dprint("YOU HAVE NOTHING IN THE INVENTORY AT THE MOMENT\n\n", '4');
    }
    
    printf("ENTER THE PRODUCT YOU WANT TO DELETE (BY ID)?\n");

    // Check if user input is int
    while (scanf("%d", &id) != 1) {

        printf("\nYOU DID NOT ENTER A VALID ID\n");

        scanf("%*s");
    }

    lineOfProduct = GetLine(id);

    // Check if user input is a valid ID
    if(lineOfProduct != -1){

        FILE* fp = fopen(PATHTOUSERPRODUCTS, "r");

        if(!fp) {
            printf("ShowDeleteScreen() - CAN'T OPEN '%s'\n", PATHTOUSERPRODUCTS);
        } else {

            FILE* temp = fopen("database/user_products_temp.txt", "w");

            copy = getc(fp);

            while(copy != EOF) {

                if(lineOfProduct != line) {

                    putc(copy, temp);

                }     
                        
                if(copy =='\n') {
                    line++;
                }

                copy = getc(fp);

            }
            fclose(temp);
            fclose(fp);

            temp = fopen("database/user_products_temp.txt", "r");
            fp = fopen(PATHTOUSERPRODUCTS, "w");

            copy = fgetc(temp);
            while (copy != EOF)
            {
                // Write to destination file
                fputc(copy, fp);

                // Read next character from source file
                copy = fgetc(temp);
            }
            fclose(temp);
            fclose(fp);

            dprint("\nTHE PRODUCT WAS DELETED SUCCESSFULLY!\n\n", '2');

            remove("database/user_products_temp.txt");
        }
    } else {
        printf("\nID DID NOT EXIST IN '%s'\nTHE PRODUCT WAS NOT DELETED!\n", PATHTOUSERPRODUCTS);
    }
}

void ShowEditScreen() {

    dprint("EDIT SCREEN\n\n",'6');
    
}

void ShowAddScreen() {

    int id, barcode, time;
    char date[20];

    dprint("\nSCAN THE BARCODE ON THE PRODUCT\n\n", '3');

    // Check if user input is int
    while (scanf("%d", &barcode) != 1) {

        dprint("\nYOU DID NOT ENTER A VALID BARCODE\n", '4');

        scanf("%*s");
    }

    char* name = strtok(GetName(barcode), "\n");

    ClearConsole();

    if(atoi(name) == 1) {

        dprint("\nTHE PRODUCT IS NOT IN OUR DATABASE.\n",'4');
        dprint("PLEASE ENTER THE NAME OF THE PRODUCT.\n\n",'3');
        scanf(" %[^\n]%*c", name);

        ClearConsole();

    }

    FILE* fp = fopen(PATHTOUSERPRODUCTS, "a+");

    if(!fp){ printf("CAN'T OPEN '%s'\n", PATHTOUSERPRODUCTS); }

    printf("\nYOU HAVE SCANNED: %s\n", name);

    dprint("\nPLEASE ENTER THE PRODUCTS EXPIRAION DATE (dd-mm-yyyy)\n\n",'3');
    scanf("%s", date);

    time = stringtotime(date);

    id = rand();

    fprintf(fp, "%d,%d,%s,%d\n", id, barcode, name, time);

    dprint("\nTHE PRODUCT WAS ADDED SUCCESSFULLY!\n\n",'2');

    dprint("IF YOU WANT TO ADD A NEW PRODUCT, PRESS B\n\n",'3');

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

int GetLine(int id){
    
    FILE* fp = fopen(PATHTOUSERPRODUCTS, "r");

    if(!fp){ printf("GetLine() - CAN'T OPEN '%s'\n", PATHTOUSERPRODUCTS);

    } else {

        char buffer[1024];
        int row = 0;

        while(fgets(buffer, 1024, fp)) {

            // Splitting the data
            char* value = strtok(buffer, ",");
            
            int number = atoi(value);

            if(number == id) {

                return row;

            }

            row++;
            
        }

        fclose(fp);
    }

    return -1;

}

char* GetName(int id) {

    FILE* fp = fopen(PATHTOBARCODE, "r");

    if(!fp){ printf("CAN'T OPEN '%s'\n", PATHTOBARCODE);

    } else {

        char buffer[1024];

        while(fgets(buffer, 1024, fp)) {

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

    FILE* fp = fopen(PATHTOUSERPRODUCTS, "r");

    if(!fp){ printf("CAN'T OPEN '%s'\n", PATHTOUSERPRODUCTS);

    } else {

        char buffer[1024];
        int row = 0;

        while(fgets(buffer, 1024, fp)) {

            // Splitting the data
            char* value = strtok(buffer, ",");

            int column = 0;
            
            while(value){

                if (column == 0) {
                    products[row].id = atoi(value);
                }

                if (column == 1) {
                    products[row].barcode = atoi(value);
                }

                if (column == 2) {
                    products[row].name = strdup(value);
                }

                if (column == 3) {
                    products[row].date = atoi(value);
                }

                *number = row+1;

                value = strtok(NULL, ",");
                column++;
            }

            row++;
            
        }

        fclose(fp);
    }

}

void dprint(char* text, char type) {

    switch (type)
    {
    //colors
    case '0': // black
        printf("\033[1;37m%s\033[0m", text);
        break;
    case '1': // blue
        printf("\033[1;34m%s\033[0m", text);
        break;
    case '2': // green
        printf("\033[1;32m%s\033[0m", text);
        break;
    case '3': // cyan
        printf("\033[1;36m%s\033[0m", text);
        break;
    case '4': // red
        printf("\033[1;31m%s\033[0m", text);
        break;
    case '5': // purple
        printf("\033[1;35m%s\033[0m", text);
        break;
    case '6': // yellow
        printf("\033[1;33m%s\033[0m", text);
        break;
    case '8': // white
        printf("\033[1;37m%s\033[0m", text);
        break;
    
    default:
        printf("%s", text);
        break;
    }

}

int stringtotime(char* time) {

    struct tm tm;
    time_t ts = 0;
    memset(&tm, 0, sizeof(tm));

    strptime(time, "%d-%m-%Y", &tm);
    ts = mktime(&tm);

    return (int)ts;

}

char* timetostring(int unixtime) {

    time_t     time;
    struct tm  ts;
    char       buf[80];

    time = unixtime;
    
    ts = *localtime(&time);
    strftime(buf, sizeof(buf), "%a %d-%m-%Y", &ts);

    return strdup(buf);

}