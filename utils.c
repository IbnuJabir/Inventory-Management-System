#include "inventory.h"

void clearInputBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int validateString(const char *str, size_t maxLength)
{
    if (str == NULL || strlen(str) >= maxLength)
    {
        return 0;
    }

    // Check if string contains only valid characters
    for (int i = 0; str[i] != '\0' && str[i] != '\n'; i++)
    {
        if (!isprint(str[i]) || str[i] == ',')
        {
            return 0;
        }
    }
    return 1;
}

int validatePositiveInt(int num)
{
    return (num >= 0);
}

int validatePositiveFloat(float num)
{
    return (num >= 0.0f);
}