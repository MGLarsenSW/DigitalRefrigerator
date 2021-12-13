int64_t GetLine(int64_t id)
{

    FILE *fp = fopen(PATH_TO_USER_PRODUCTS, "r");

    if (fp)
    {
        int64_t i = 0, product_id, dummy1, dummy2, dummy3;

        while (fscanf(fp, "%lld;%lld;%lld;%lld", &product_id, &dummy1, &dummy2, &dummy3) == 4)
        {

            if (product_id == id)
                return i;

            i++;
        }

        fclose(fp);
    }

    return -1;
}

char *GetName(int64_t id)
{

    FILE *fp = fopen(PATH_TO_BARCODE_LIST, "r");

    if (fp != NULL)
    {
        int64_t i = 0, product_id;
        char *name = (char *)malloc(20);

        while (fscanf(fp, "%lld;%[^\n]%*c", &product_id, name) == 2)
        {

            if (product_id == id)
            {
                fclose(fp);
                return name;
            }
        }

        fclose(fp);
        free(name);
    }

    return NULL;
}

int AddProductToFile(char *name, int64_t barcode)
{

    int64_t id, time = -1;
    char date[20];

    FILE *fp = fopen(PATH_TO_USER_PRODUCTS, "a+");

    if (!fp)
    {
        printf("AddProductToFile() - CAN'T OPEN '%s'\n", PATH_TO_USER_PRODUCTS);
        return -1;
    }

    printf("\nYOU HAVE SCANNED: %s\n", name);

    while (time == -1)
    {

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

int SaveBarcode(char *name, int64_t barcode)
{

    FILE *fp = fopen(PATH_TO_BARCODE_LIST, "a+");

    if (!fp)
    {
        printf("SaveBarcode() - CAN'T OPEN '%s'\n", PATH_TO_USER_PRODUCTS);
        return -1;
    }

    fprintf(fp, "%lld;%s\n", barcode, name);

    fclose(fp);

    return 1;
}

// http://www.tutorialspanel.com/delete-a-specific-line-from-a-text-file-using-c/index.htm
int DeleteByLine(int lineOfProduct)
{

    char copy;
    int64_t line = 0;

    // Check if user input is a valid ID
    if (lineOfProduct == -1)
    {
        printf("\nID DID NOT EXIST IN '%s'\n\n", PATH_TO_USER_PRODUCTS);
        return -1;
    }

    FILE *fp = fopen(PATH_TO_USER_PRODUCTS, "r");

    if (!fp)
        printf("DeleteByLine() - CAN'T OPEN '%s'\n", PATH_TO_USER_PRODUCTS);

    else
    {

        FILE *temp = fopen(PATH_TO_TEMP, "w");

        copy = getc(fp);

        while (copy != EOF)
        {

            if (lineOfProduct != line)
                putc(copy, temp);

            if (copy == '\n')
                line++;

            copy = getc(fp);
        }

        fclose(temp);
        fclose(fp);

        // Delete old user_products.txt and rename temp
        remove(PATH_TO_USER_PRODUCTS);
        if (rename(PATH_TO_TEMP, PATH_TO_USER_PRODUCTS))
        {
            printf("DeleteByLine() - COULD NOT RENAME '%s'\n", PATH_TO_USER_PRODUCTS);
            return -1;
        }

        dprint("\nTHE PRODUCT WAS DELETED SUCCESSFULLY!\n\n", Green);
    }

    return 1;
}

void GetUserProducts(int64_t *number, struct Product products[])
{

    *number = 0;

    FILE *fp = fopen(PATH_TO_USER_PRODUCTS, "r");

    if (fp)
    {
        struct Product p;
        int i = 0;

        while (fscanf(fp, "%lld;%lld;%lld;%lld", &p.id, &p.barcode, &p.date, &p.added) == 4)
        {
            products[i] = p;
            i++;
        }

        *number = i;

        fclose(fp);
    }
}

void GetFeed(int64_t *number, struct Feed feed[])
{

    *number = 0;

    FILE *fp = fopen(PATH_TO_FOOD_FEED, "r");

    if (fp)
    {
        struct Feed f;
        int i = 0;

        while (fscanf(fp, "%d;%d;%[^;]%*c%[^;]%*c%[^\n]%*c", &f.id, &f.date, f.name, f.address, f.comment) == 5)
        {
            feed[i] = f;
            i++;
        }

        *number = i;

        fclose(fp);
    }
}
