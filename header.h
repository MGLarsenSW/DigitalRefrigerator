#define PATH_TO_USER_PRODUCTS "database/user_products.txt"
#define PATH_TO_BARCODE_LIST "database/barcode_list.txt"
#define PATH_TO_TEMP "database/user_products_temp.txt"
#define PATH_TO_FOOD_FEED "database/food_feed.txt"

enum State
{
    StateShowProductsScreen = 1,
    StateShowAddScreen = 2,
    StateShowFeedScreen = 3,
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
    int64_t date;
    int64_t added;
};

struct Feed
{
    int id;
    int date;
    char name[20];
    char address[50];
    char comment[50];
};

void ClearConsole();
void HandleScreens();
void ShowWelcomeScreen();
void ShowProductsScreen();
void ShowDeleteScreen();
void ShowFeedScreen();
void ShowAddScreen();
void AddProduct();
int64_t HandleScan();
char *strdup();
void GetUserProducts();
void GetFeed();
char *GetName();
int64_t GetLine();
int64_t stringtotime();
char *timetostring();
int64_t S64();
int64_t GetCurrentTime();