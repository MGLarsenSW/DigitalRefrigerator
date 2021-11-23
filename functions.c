void ClearConsole() {

    #ifdef _WIN32
        system("cls");
    #else //In any other OS
        system("clear");
    #endif

}

int64_t HandleScan(int64_t screen) {

    if(screen) {
        printf("ENTER 'Q' TO GO BACK\n\n");
    }

    char ch;

    scanf(" %c", &ch);

    if(toupper(ch) == 'A') { return StateShowProductsScreen; }
    if(toupper(ch) == 'B') { return StateShowAddScreen; }
    if(toupper(ch) == 'C') { return StateShowEditScreen; }
    if(toupper(ch) == 'D') { return StateShowDeleteScreen; }
    if(toupper(ch) == 'Q' && !screen) { return StateExit; }

    return 0;
}

void ShowWelcomeScreen() {

    //printf("+----------------------------------------------------+\n");
    //printf("|                        MENU                        |\n");
    //printf("+----------------------------------------------------+\n\n");

    dprint("\n## MENU ##\n\n", Cyan);

    dprint("A:  VIEW YOUR INVENTORY       ", Blue); dprint("B:  ADD PRODUCT\n\n", Green);
    dprint("C:  EDIT PRODUCT              ", Yellow); dprint("D:  DELETE PRODUCT\n\n", Red);
    dprint("Q:  EXIT PROGRAM\n\n", White);

} 

void ShowProductsScreen(int64_t numberOfProducts, struct Product products[]) {

    char title[150];
    snprintf(title, sizeof(title), "YOU HAVE THE FOLLOWING ITEMS IN YOUR INVENTORY (%lld):\n\n", numberOfProducts);
    dprint(title, Cyan);

    for (int64_t i = 0; i < numberOfProducts; i++) {

        char name[50];
        snprintf(name, sizeof(name), "%s (#%lld) \n", products[i].name, products[i].id);
        dprint(name, Green);

        char date[50];
        snprintf(date, sizeof(date), "EXPIRE: %s \n\n", products[i].date);
        dprint(date, Red);

    }

    if (numberOfProducts == 0) {
        dprint("YOU HAVE NOTHING IN YOUR INVENTORY AT THE MOMENT\n\n", '3');
    }
    
}

// http://www.tutorialspanel.com/delete-a-specific-line-from-a-text-file-using-c/index.htm
void ShowDeleteScreen(int64_t numberOfProducts, struct Product products[]) {

    int64_t id, lineOfProduct = 0, line = 0;
    char copy;

    char title[150];
    snprintf(title, sizeof(title), "YOU HAVE THE FOLLOWING ITEMS IN YOUR INVENTORY (%lld):\n\n", numberOfProducts);
    dprint(title, Cyan);

    for (int64_t i = 0; i < numberOfProducts; i++) {

        char name[50];
        snprintf(name, sizeof(name), "%s (#%lld) \n", products[i].name, products[i].id);
        dprint(name, Green);

        char date[50];
        snprintf(date, sizeof(date), "EXPIRE: %s \n\n", products[i].date);
        dprint(date, Red);

    }

    if (numberOfProducts == 0) {
        dprint("YOU HAVE NOTHING IN YOUR INVENTORY AT THE MOMENT\n\n", '3');
    } else {

        printf("ENTER THE PRODUCT YOU WANT TO DELETE (BY ID)?\n");

        // Check if user input is int
        while (scanf("%lld", &id) != 1) {

            printf("\nYOU DID NOT ENTER A VALID ID\n");

            scanf("%*s");
        }

        lineOfProduct = GetLine(id);

        // Check if user input is a valid ID
        if(lineOfProduct != -1){

            FILE* fp = fopen(PATH_TO_USER_PRODUCTS, "r");

            if(!fp) {

                printf("ShowDeleteScreen() - CAN'T OPEN '%s'\n", PATH_TO_USER_PRODUCTS);

            } else {

                FILE* temp = fopen(PATH_TO_TEMP, "w");

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

                temp = fopen(PATH_TO_TEMP, "r");
                fp = fopen(PATH_TO_USER_PRODUCTS, "w");

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

                dprint("\nTHE PRODUCT WAS DELETED SUCCESSFULLY!\n\n", Green);

                remove(PATH_TO_TEMP);
            }

        } else {

            printf("\nID DID NOT EXIST IN '%s'\nTHE PRODUCT WAS NOT DELETED!\n", PATH_TO_USER_PRODUCTS);

        }

    }
}

void ShowEditScreen() {

    dprint("EDIT SCREEN\n\n", Yellow);
    
}

void ShowAddScreen() {

    int64_t id, barcode, time = -1;
    char date[20];

    dprint("\nSCAN THE BARCODE ON THE PRODUCT\n\n", Cyan);

    // Check if user input is int
    while (scanf("%lld", &barcode) != 1) {

        dprint("\nYOU DID NOT ENTER A VALID BARCODE\n", Red);

        scanf("%*s");
    }

    char* name = strtok(GetName(barcode), "\n");

    //ClearConsole();

    if(S64(name) == 1) {

        dprint("\nTHE PRODUCT IS NOT IN OUR DATABASE.\n", Red);
        dprint("PLEASE ENTER THE NAME OF THE PRODUCT.\n\n", Cyan);
        scanf(" %[^\n]%*c", name);

        //ClearConsole();

    }

    FILE* fp = fopen(PATH_TO_USER_PRODUCTS, "a+");

    if(!fp){ printf("CAN'T OPEN '%s'\n", PATH_TO_USER_PRODUCTS); }

    printf("\nYOU HAVE SCANNED: %s\n", name);

    while(time == -1) {

        dprint("\nPLEASE ENTER THE PRODUCTS EXPIRAION DATE (dd-mm-yyyy)\n\n", Cyan);
        scanf("%s", date);

        time = stringtotime(date);

    }

    id = rand();

    fprintf(fp, "%lld,%lld,%s,%lld\n", id, barcode, name, time);

    dprint("\nTHE PRODUCT WAS ADDED SUCCESSFULLY!\n\n", Green);

    dprint("IF YOU WANT TO ADD A NEW PRODUCT, PRESS B\n\n", Cyan);

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

int64_t GetLine(int64_t id){
    
    FILE* fp = fopen(PATH_TO_USER_PRODUCTS, "r");

    if(!fp){ printf("GetLine() - CAN'T OPEN '%s'\n", PATH_TO_USER_PRODUCTS);

    } else {

        char buffer[1024];
        int64_t row = 0;

        while(fgets(buffer, 1024, fp)) {

            // Splitting the data
            char* value = strtok(buffer, ",");
            
            int64_t number = S64(value);

            if(number == id) {

                return row;

            }

            row++;
            
        }

        fclose(fp);
    }

    return -1;

}

char* GetName(int64_t id) {

    FILE* fp = fopen(PATH_TO_BARCODE_LIST, "r");

    if(!fp){ printf("CAN'T OPEN '%s'\n", PATH_TO_BARCODE_LIST);

    } else {

        char buffer[1024];

        while(fgets(buffer, 1024, fp)) {

            // Splitting the data
            char* value = strtok(buffer, ",");
            
            int64_t number = S64(value);

            if(number == id) {

                value = strtok(NULL, ",");
                
                return strdup(value);

            }
            
        }

        fclose(fp);
    }

    return strdup("1");

}

void GetUserProducts(int64_t *number, struct Product *products) {

    /*for(int64_t i = 0; i < *number; i++) {
        free(products[i].name);
    }*/

    FILE* fp = fopen(PATH_TO_USER_PRODUCTS, "r");

    if(!fp){ printf("CAN'T OPEN '%s'\n", PATH_TO_USER_PRODUCTS);

    } else {

        char buffer[1024];
        int64_t row = 0;

        while(fgets(buffer, 1024, fp)) {

            // Splitting the data
            char* value = strtok(buffer, ",");

            int64_t column = 0;
            
            while(value){

                if (column == 0) {
                    products[row].id = S64(value);
                }

                if (column == 1) {
                    products[row].barcode = S64(value);
                }

                if (column == 2) {
                    products[row].name = strdup(value);
                }

                if (column == 3) {
                    products[row].date = timetostring(S64(value));
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

    case Black:
        printf("\033[1;37m%s\033[0m", text);
        break;
    case Blue:
        printf("\033[1;34m%s\033[0m", text);
        break;
    case Green:
        printf("\033[1;32m%s\033[0m", text);
        break;
    case Cyan:
        printf("\033[1;36m%s\033[0m", text);
        break;
    case Red:
        printf("\033[1;31m%s\033[0m", text);
        break;
    case Purple:
        printf("\033[1;35m%s\033[0m", text);
        break;
    case Yellow:
        printf("\033[1;33m%s\033[0m", text);
        break;
    case White:
        printf("\033[1;37m%s\033[0m", text);
        break;
    
    default:
        printf("%s", text);
        break;
    }

}

int64_t stringtotime(char* tid) { // 2 forskellige fejlkoder | fejl er ugylidigt, sæt tal til det højeste

    time_t result = 0;
   
    int year = 0, month = 0, day = 0;
   
    if (sscanf(tid, "%d-%d-%d", &day, &month, &year) == 3) {
        struct tm breakdown = {0};
        breakdown.tm_year = year - 1900; /* years since 1900 */
        breakdown.tm_mon = month - 1;
        breakdown.tm_mday = day;
        breakdown.tm_hour = 0;
        breakdown.tm_min = 0;
        
        if ((result = mktime(&breakdown)) == (time_t)-1) {
            return INT_MAX; 
        }
            
        return (int64_t)result;
    }
    
    return -1; // return error (wrong format)

}

char* timetostring(int64_t unixtime) {

    time_t     time;
    struct tm  ts;
    char       buf[80];

    time = unixtime;
    
    ts = *localtime(&time);
    strftime(buf, sizeof(buf), "%A %d-%m-%Y", &ts);

    return strdup(buf);

}

int64_t S64(const char *s) {
  int64_t i;
  char c ;
  int scanned = sscanf(s, "%lld %c", &i, &c);
  if (scanned == 1) return i;
  if (scanned > 1) {
    // TBD about extra data found
    return i;
    }
  // TBD failed to scan;  
  return 0;  
}