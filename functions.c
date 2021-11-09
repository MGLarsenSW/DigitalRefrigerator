
void ClearConsole() {

    printf("\e[1;1H\e[2J");

    #ifdef _WIN32
        system("cls");
    #else //In any other OS
        system("clear");
    #endif

}

int HandleScan(int screen) {

    if(screen) {
        printf("SKRIV 'Q' FOR AT GÅ TILBAGE\n\n");
    }

    char ch;

    scanf(" %c", &ch);

    if(toupper(ch) == 'A') { return 1; }
    if(toupper(ch) == 'B') { return 2; }
    if(toupper(ch) == 'C') { return 3; }
    if(toupper(ch) == 'D') { return 4; }

    return 0;
}

void ShowWelcomeScreen() {

    printf("DU HAR NU FØLGENDE VALGMULIGHEDER:\n\n");

    printf("A:  SE DIT KØLESKAB           B:  TILFØJ PRODUKTER\n\n");
    printf("C:  ÆNDRE PRODUKTER           D:  SLET PRODUKTER\n\n\n");

}

void ShowProductsScreen(int numberOfProducts, struct Product products[]) {

    printf("DU HAR FØLGENDE PRODUKTER I DIT KØLESKAB:\n\n");

    for (int i = 0; i < numberOfProducts; i++)
    {
        
        printf("%d. %s \n", i, products[i].name);
        printf("UDLØBER: %d \n\n", products[i].date);

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

    printf("\nSCAN STREGKODEN PÅ PRODUKTET\n\n");
    scanf(" %d", &barcode);

    char* name = strtok(GetName(barcode), "\n");

    ClearConsole();

    if(atoi(name) == 1) {

        printf("\nVaren findes ikke i vores database.\nIndtast venligst et navn på produktet:\n\n");
        scanf(" %s", name);

        ClearConsole();

    }

    FILE* fp = fopen("database/user_products", "a+");

    if(!fp){
        printf("Can't open file\n");
    }

    printf("\nDU HAR SCANNET: %s\n", name);

    printf("\nINDTAST VENLIGST PRODUKTETS UDLØBSDATO\n\n");
    scanf(" %d", &date);

    srand(time(NULL));
    id = rand();

    fprintf(fp, "%d, %d, %s, %d\n", id, barcode, name, date);

    printf("\nPRODUKTET BLEV TILFØJET!\n\n");

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

    FILE* fp = fopen("database/barcode_list", "r");

    if(!fp){ printf("Can't open file\n");

    } else {

        char buffer[1024];
        int row = 0;

        while(fgets(buffer, 1024, fp)) {

            row++;

            if(row == 1) { continue; }

            // Splitting the data
            char* value = strtok(buffer, ", ");
            
            int number = atoi(value);

            if(number == id) {

                value = strtok(NULL, ", ");
                
                return strdup(value);

            }
            
        }

        fclose(fp);
    }

    return strdup("1");

}

void GetUserProducts(int *number, struct Product *products) {

    FILE* fp = fopen("database/user_products", "r");

    if(!fp){ printf("Can't open file\n");

    } else {

        char buffer[1024];
        int row = 0;

        while(fgets(buffer, 1024, fp)) {

            row++;

            if(row == 1) { continue; }

            // Splitting the data
            char* value = strtok(buffer, ", ");

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

                value = strtok(NULL, ", ");
                column++;
            }
            
        }

        fclose(fp);
    }

}