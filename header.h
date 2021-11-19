#define PATHTOUSERPRODUCTS "database/user_products.txt"
#define PATHTOBARCODE "database/barcode_list.txt"

struct Product
{
    int id;
    int barcode;
    char* name;
    int date;
};

void HandleScreens();
void ShowWelcomeScreen();
void ShowProductsScreen(int number, struct Product products[]);
void ShowDeleteScreen(int numberOfProducts, struct Product products[]);
void ShowEditScreen();
void ShowAddScreen();
void AddProduct();
int HandleScan(int welcome);
char* strdup(const char* org);
void GetUserProducts(int *number, struct Product *products);
char* GetNameDB(int id);
char* GetNameUD(int id);
int GetLine(int id);
void dprint(char* text, char type);