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
void ShowDeleteScreen(struct Product products[]);
void ShowEditScreen();
void ShowAddScreen();
void AddProduct();
int HandleScan(int welcome);
char* strdup(const char* org);
void GetUserProducts(int *number, struct Product *products);
char* GetName(int id);
int GetLine(int *id);