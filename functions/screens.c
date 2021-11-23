void ShowWelcomeScreen() {

    dprint("\n## MENU ##\n\n", Cyan);

    dprint("A:  VIEW YOUR INVENTORY       ", Blue); dprint("B:  ADD PRODUCT\n\n", Green);
    dprint("C:  EDIT PRODUCT              ", Yellow); dprint("D:  DELETE PRODUCT\n\n", Red);
    dprint("Q:  EXIT PROGRAM\n\n", White);

} 

void ShowDeleteScreen(int64_t numberOfProducts, struct Product products[]) {

    int64_t id;

    ShowProductsScreen(numberOfProducts, products);
    
    if (numberOfProducts > 0) {

        printf("ENTER THE PRODUCT YOU WANT TO DELETE (BY ID)?\n");

        // Check if user input is int
        while (scanf("%lld", &id) != 1) {

            printf("\nYOU DID NOT ENTER A VALID ID\n");

            scanf("%*s");
        }

        // tjek result. -1 = fejl prøv igen; 1 = succes.
        int result = DeleteByLine(GetLine(id));

    }
}

void ShowProductsScreen(int64_t numberOfProducts, struct Product products[]) {

    char title[150];
    snprintf(title, sizeof(title), "YOU HAVE THE FOLLOWING ITEMS IN YOUR INVENTORY (%lld):\n\n", numberOfProducts);
    dprint(title, Cyan);

    for (int64_t i = 0; i < numberOfProducts; i++) {

        char name[50];
        snprintf(name, sizeof(name), "%s (#%lld) \n", products[i].name, products[i].id);
        dprint(name, White);

        char added[50];
        snprintf(added, sizeof(added), "%s - ", products[i].added);
        dprint(added, Green);

        char date[50];
        snprintf(date, sizeof(date), "%s \n\n", products[i].date);
        dprint(date, Red);

    }

    if (numberOfProducts == 0) {
        dprint("YOU HAVE NOTHING IN YOUR INVENTORY AT THE MOMENT\n\n", '3');
    }
    
}

void ShowAddScreen() {

    int64_t barcode;

    dprint("\nSCAN THE BARCODE ON THE PRODUCT\n\n", Cyan);

    // Check if user input is int
    while (scanf("%lld", &barcode) != 1) {

        dprint("\nYOU DID NOT ENTER A VALID BARCODE\n", Red);

        scanf("%*s");
    }

    char* name = strtok(GetName(barcode), "\n");

    ClearConsole();

    if(S64(name) == 1) {

        dprint("\nTHE PRODUCT IS NOT IN OUR DATABASE.\n", Red);
        dprint("PLEASE ENTER THE NAME OF THE PRODUCT.\n\n", Cyan);
        scanf(" %[^\n]%*c", name);

        SaveBarcode(name, barcode);

        ClearConsole();

    }

    AddProductToFile(name, barcode);

}

