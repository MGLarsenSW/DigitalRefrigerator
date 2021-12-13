#include "dprint.c"
#include "time.c"
#include "database.c"
#include "screens.c"

void ClearConsole()
{
#ifdef _WIN32
    system("cls");
#else // In any other OS
    system("clear");
#endif
}

enum State HandleScan(enum State screen)
{

    if (screen)
        printf("ENTER 'Q' TO GO BACK\n\n");

    char ch;

    scanf(" %c", &ch);

    if (toupper(ch) == 'A')
        return StateShowProductsScreen;

    if (toupper(ch) == 'B')
        return StateShowAddScreen;

    if (toupper(ch) == 'C')
        return StateShowFeedScreen;

    if (toupper(ch) == 'D')
        return StateShowDeleteScreen;

    if (toupper(ch) == 'Q' && !screen)
        return StateExit;

    return StateShowWelcomeScreen;
}

int64_t S64(const char *s)
{
    int64_t i;

    int scanned = sscanf(s, "%lld", &i);

    if (scanned >= 1)
        return i;

    return 0;
}