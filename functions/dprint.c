void dprint(char* text, char type) {

    switch (type)
    {

    case Black:
        printf("\033[1;37m%s\033[0m", text);
        break;
    case Blue:
        printf("\033[1;34m%s\033[0m", text);
        break;
    case Green:
        printf("\033[1;32m%s\033[0m", text);
        break;
    case Cyan:
        printf("\033[1;36m%s\033[0m", text);
        break;
    case Red:
        printf("\033[1;31m%s\033[0m", text);
        break;
    case Purple:
        printf("\033[1;35m%s\033[0m", text);
        break;
    case Yellow:
        printf("\033[1;33m%s\033[0m", text);
        break;
    case White:
        printf("\033[1;37m%s\033[0m", text);
        break;
    
    default:
        printf("%s", text);
        break;
    }

}