void ShowWelcomeScreen()
{
    dprint("\n## MENU ##\n\n", Cyan);

    dprint("A:  VIEW YOUR INVENTORY       ", Blue);
    dprint("B:  ADD PRODUCT\n\n", Green);
    dprint("C:  VIEW FOOD FEED            ", Yellow);
    dprint("D:  DELETE PRODUCT\n\n", Red);
    dprint("Q:  EXIT PROGRAM\n\n", White);
}

void ShowDeleteScreen(int64_t numberOfProducts, struct Product products[])
{

    int64_t id, result = -1;

    ShowProductsScreen(numberOfProducts, products);

    if (numberOfProducts > 0)
    {

        printf("PLEASE ENTER THE PRODUCT YOU WANT TO DELETE (BY ID)?\n");

        // Check if user input is int
        while (result == -1)
        {

            if (scanf("%lld", &id) != 1)
            {
                printf("\nYOU DID NOT ENTER A VALID ID\n");

                scanf("%*s");
            }
            else
                result = DeleteByLine(GetLine(id));

            if (!result)
                printf("ENTER THE PRODUCT YOU WANT TO DELETE (BY ID)?\n");
        }
    }
}

void ShowProductsScreen(int64_t numberOfProducts, struct Product products[])
{

    char title[150];
    snprintf(title, sizeof(title), "YOU HAVE THE FOLLOWING ITEMS IN YOUR INVENTORY (%lld):\n\n", numberOfProducts);
    dprint(title, Cyan);

    for (int64_t i = 0; i < numberOfProducts; i++)
    {

        char *getname = GetName(products[i].barcode);

        char name[100];
        snprintf(name, sizeof(name), "%s (%lld) \n", getname, products[i].id);
        dprint(name, White);

        free(getname);

        char added[50];
        snprintf(added, sizeof(added), "%s - ", timetostring(products[i].added));
        dprint(added, Green);

        char date[50];
        snprintf(date, sizeof(date), "%s \n\n", timetostring(products[i].date));
        dprint(date, Red);
    }

    if (numberOfProducts == 0)
        dprint("YOU HAVE NOTHING IN YOUR INVENTORY AT THE MOMENT\n\n", Cyan);
}

void ShowAddScreen()
{

    int64_t barcode;

    dprint("\nSCAN THE BARCODE ON THE PRODUCT\n\n", Cyan);

    // Check if user input is int
    while (scanf("%lld", &barcode) != 1)
    {

        dprint("\nYOU DID NOT ENTER A VALID BARCODE\n", Red);

        scanf("%*s");
    }

    char *name;

    ClearConsole();

    if (S64(GetName(barcode)) == 1)
    {

        dprint("\nTHE PRODUCT IS NOT IN OUR DATABASE.\n", Red);
        dprint("PLEASE ENTER THE NAME OF THE PRODUCT.\n\n", Cyan);
        scanf(" %[^\n]%*c", name);

        SaveBarcode(name, barcode);

        ClearConsole();
    }
    else
        name = GetName(barcode);

    AddProductToFile(name, barcode);
}

void ShowFeedScreen(int64_t numberOfFeed, struct Feed feed[])
{

    char title[50];
    snprintf(title, sizeof(title), "FEED SCREEN: (%lld):\n\n", numberOfFeed);
    dprint(title, White);

    for (int64_t i = 0; i < numberOfFeed; i++)
    {

        char name[50];
        snprintf(name, sizeof(name), "%s) ", feed[i].name);
        dprint(name, Green);

        char comment[500];
        snprintf(comment, sizeof(comment), "%s \n\nProduktet udløber: %s\nAdressen er %s\n\n", feed[i].comment, timetostring(feed[i].date), feed[i].address);
        dprint(comment, Cyan);
    }

    if (numberOfFeed == 0)
        dprint("THERE IS NOTHING IN THE FEED AT THE MOMENT\n\n", '3');
}
