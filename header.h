#define PATH_TO_USER_PRODUCTS "database/user_products.txt"
#define PATH_TO_BARCODE_LIST "database/barcode_list.txt"
#define PATH_TO_TEMP "database/user_products_temp.txt"

enum State 
{
    StateShowProductsScreen = 1, 
    StateShowAddScreen = 2, 
    StateShowEditScreen = 3, 
    StateShowDeleteScreen = 4, 
    StateExit = 5
};

enum Color 
{
    Black, 
    Blue, 
    Green, 
    Cyan, 
    Red, 
    Purple, 
    Yellow, 
    White
};

struct Product
{
    int64_t id;
    int64_t barcode;
    char* name;
    char* date;
};

void HandleScreens();
void ShowWelcomeScreen();
void ShowProductsScreen(int64_t number, struct Product products[]);
void ShowDeleteScreen(int64_t numberOfProducts, struct Product products[]);
void ShowEditScreen();
void ShowAddScreen();
void AddProduct();
int64_t HandleScan(int64_t welcome);
char* strdup(const char* org);
void GetUserProducts(int64_t *number, struct Product *products);
char* GetName(int64_t id);
int64_t GetLine(int64_t id);
void dprint(char* text, char type);
int64_t stringtotime(char* time);
char* timetostring(int64_t unixtime);
int64_t S64(const char *s);