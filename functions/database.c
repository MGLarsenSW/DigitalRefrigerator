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

int AddProductToFile(char* name, int64_t barcode) {

    int64_t id, time = -1;
    char date[20];

    FILE* fp = fopen(PATH_TO_USER_PRODUCTS, "a+");

    if(!fp){ 
        printf("CAN'T OPEN '%s'\n", PATH_TO_USER_PRODUCTS);
        return -1; 
    }

    printf("\nYOU HAVE SCANNED: %s\n", name);

    while(time == -1) {

        dprint("\nPLEASE ENTER THE PRODUCTS EXPIRAION DATE (dd-mm-yyyy)\n\n", Cyan);
        scanf("%s", date);

        time = stringtotime(date);

    }

    id = rand();

    fprintf(fp, "%lld,%lld,%s,%lld,%lld\n", id, barcode, name, time, GetCurrentTime());

    dprint("\nTHE PRODUCT WAS ADDED SUCCESSFULLY!\n\n", Green);

    dprint("IF YOU WANT TO ADD A NEW PRODUCT, PRESS B\n\n", Cyan);

    fclose(fp);

    return 1;

}

int SaveBarcode(char* name, int64_t barcode) {

    FILE* fp = fopen(PATH_TO_BARCODE_LIST, "a+");

    if(!fp){ 
        printf("CAN'T OPEN '%s'\n", PATH_TO_USER_PRODUCTS);
        return -1; 
    }

    fprintf(fp, "%lld,%s\n", barcode, name);

    fclose(fp);

    return 1;

}

// http://www.tutorialspanel.com/delete-a-specific-line-from-a-text-file-using-c/index.htm
int DeleteByLine(int lineOfProduct) {

    char copy;
    int64_t line = 0;

    // Check if user input is a valid ID
    if(lineOfProduct == -1) {
        printf("\nID DID NOT EXIST IN '%s'\nTHE PRODUCT WAS NOT DELETED!\n", PATH_TO_USER_PRODUCTS);
        return -1;
    }

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
        while (copy != EOF) {
            
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

    return 1;

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

                if (column == 4) {
                    products[row].added = timetostring(S64(value));
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