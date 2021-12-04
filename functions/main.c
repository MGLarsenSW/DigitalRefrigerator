#include "dprint.c"
#include "time.c"
#include "database.c"
#include "screens.c"

void ClearConsole()
{
#ifdef _WIN32
    system("cls");
#else //In any other OS
    system("clear");
#endif
}

int64_t HandleScan(int64_t screen)
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

    return 0;
}

// https://stackoverflow.com/questions/10131464/returning-a-char-pointer-in-c
char *strdup(const char *org)
{

    if (org == NULL)
        return NULL;

    char *newstr = malloc(strlen(org) + 1);
    char *p;

    if (newstr == NULL)
        return NULL;

    p = newstr;

    while (*org)
        *p++ = *org++; /* copy the string. */
    return newstr;
}

int64_t S64(const char *s)
{
    int64_t i;

    int scanned = sscanf(s, "%lld", &i);

    if (scanned >= 1)
        return i;

    return 0;
}