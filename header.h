
struct Product
{
    int id;
    int barcode;
    char* name;
    int date;
};

struct Product products[100];
int numberOfProducts = 0;

void HandleScreens();
void ShowWelcomeScreen();
void ShowProductsScreen();
void ShowDeleteScreen();
void ShowEditScreen();
void ShowAddScreen();
void AddProduct();
int HandleScan(int welcome);
char* strdup(const char* org);
void GetUserProducts();
char* GetName(int id);

