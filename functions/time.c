int64_t GetCurrentTime()
{
    return (int64_t)time(NULL);
}

int64_t stringtotime(char *tid)
{

    time_t result = 0;

    int year = 0, month = 0, day = 0;

    if (sscanf(tid, "%d-%d-%d", &day, &month, &year) == 3)
    {
        struct tm breakdown = {0};
        breakdown.tm_year = year - 1900; /* years since 1900 */
        breakdown.tm_mon = month - 1;
        breakdown.tm_mday = day;
        breakdown.tm_hour = 0;
        breakdown.tm_min = 0;

        if ((result = mktime(&breakdown)) == (time_t)-1)
            return INT_MAX;

        return (int64_t)result;
    }

    return -1; // return error (wrong format)
}

char *timetostring(int64_t unixtime)
{

    time_t time;
    struct tm ts;
    char buf[80];
    char *timeString = (char *)malloc(80);

    time = unixtime;

    ts = *localtime(&time);
    strftime(timeString, 80, "%a %d-%m-%Y", &ts);

    return timeString;
}