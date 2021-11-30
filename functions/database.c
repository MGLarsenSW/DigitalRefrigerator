int64_t GetLine(int64_t id){
    
    FILE* fp = fopen(PATH_TO_USER_PRODUCTS, "r");

    if(!fp){ printf("GetLine() - CAN'T OPEN '%s'\n", PATH_TO_USER_PRODUCTS);

    } else {

        char buffer[1024];
        int64_t row = 0;
        int64_t product_id;

        while(fgets(buffer, 1024, fp)) {

            sscanf(buffer, "%lld", &product_id);

            if(product_id == id) {
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

    if(!fp){
        
        printf("GetName() - CAN'T OPEN '%s'\n", PATH_TO_BARCODE_LIST);

    } else {

        char buffer[1024];
        int64_t barcode;
        char* name = (char*) malloc(20);

        while(fgets(buffer, 1024, fp)) {

            sscanf(buffer, "%lld;%[^\n]%*c", &barcode, name);

            if(barcode == id) {
                return name;
            }
            
        }

        fclose(fp);
        free(name);
    }

    return "1";

}

int AddProductToFile(char* name, int64_t barcode) {

    int64_t id, time = -1;
    char date[20];

    FILE* fp = fopen(PATH_TO_USER_PRODUCTS, "a+");

    if(!fp){ 
        printf("AddProductToFile() - CAN'T OPEN '%s'\n", PATH_TO_USER_PRODUCTS);
        return -1; 
    }

    printf("\nYOU HAVE SCANNED: %s\n", name);

    while(time == -1) {

        dprint("\nPLEASE ENTER THE PRODUCTS EXPIRAION DATE (dd-mm-yyyy)\n\n", Cyan);
        scanf("%s", date);

        time = stringtotime(date);

    }

    id = rand();

    fprintf(fp, "%lld;%lld;%lld;%lld\n", id, barcode, time, GetCurrentTime());

    dprint("\nTHE PRODUCT WAS ADDED SUCCESSFULLY!\n\n", Green);

    dprint("IF YOU WANT TO ADD A NEW PRODUCT, PRESS B\n\n", Cyan);

    fclose(fp);

    return 1;

}

int SaveBarcode(char* name, int64_t barcode) {

    FILE* fp = fopen(PATH_TO_BARCODE_LIST, "a+");

    if(!fp){ 
        printf("SaveBarcode() - CAN'T OPEN '%s'\n", PATH_TO_USER_PRODUCTS);
        return -1; 
    }

    fprintf(fp, "%lld;%s\n", barcode, name);

    fclose(fp);

    return 1;

}

// http://www.tutorialspanel.com/delete-a-specific-line-from-a-text-file-using-c/index.htm
int DeleteByLine(int lineOfProduct) {

    char copy;
    int64_t line = 0;

    // Check if user input is a valid ID
    if(lineOfProduct == -1) {
        printf("\nID DID NOT EXIST IN '%s'\n\n", PATH_TO_USER_PRODUCTS);
        return -1;
    }

    FILE* fp = fopen(PATH_TO_USER_PRODUCTS, "r");

    if(!fp) {

        printf("DeleteByLine() - CAN'T OPEN '%s'\n", PATH_TO_USER_PRODUCTS);

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
            
            fputc(copy, fp);
            
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

    *number = 0;

    FILE* fp = fopen(PATH_TO_USER_PRODUCTS, "r");

    if(!fp) { printf("GetUserProducts() - CAN'T OPEN '%s'\n", PATH_TO_USER_PRODUCTS);

    } else {

        char buffer[1024];
        int64_t row = 0;

        while(fgets(buffer, 1024, fp)) {

            int64_t id, barcode, date, added;

            sscanf(buffer, "%lld;%lld;%lld;%lld", &id, &barcode, &date, &added);

            products[row].id = id;
            products[row].barcode = barcode;
            products[row].date = date;
            products[row].added = added;

            row++;
            *number = row;
            
        }

        fclose(fp);
    }

}

void GetFeed(int64_t *number, struct Feed *feed) {

    *number = 0;

    FILE* fp = fopen(PATH_TO_FOOD_FEED, "r");

    if(!fp){ printf("GetFeed() - CAN'T OPEN '%s'\n", PATH_TO_FOOD_FEED);

    } else {

        char buffer[1024];
        int64_t row = 0;

        while(fgets(buffer, 1024, fp)) {

            int64_t id, date;
            char* name = (char*) malloc(20);
            char* address = (char*) malloc(50);
            char* comment = (char*) malloc(50);

            // ID og DATO bliver scannet korrekt.
            // NAME, ADDRESS og COMMENT bliver alle smidt ind i variablen name.
            // Der skal laves så den FREE'ER variablerne igen.

            sscanf(buffer, "%lld;%lld;%[^\n]%*c;%[^\n]%*c;%[^\n]%*c", &id, &date, name, address, comment);

            //printf("id: %lld, date: %lld, name: %s, address: %s, comment: %s", id, date, name, address, comment);

            feed[row].name = name;
            feed[row].date = timetostring(date);
            feed[row].address = address;
            feed[row].comment = comment;

            row++;
            *number = row;
            
        }

        fclose(fp);
    }

}
