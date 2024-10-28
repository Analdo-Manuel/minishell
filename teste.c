#include <stdio.h>

static size_t primary_alloc(const char *str)
{
    char    c;
    size_t  i;
    size_t  j;
    
    i = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] == 34)
        {
            i++;
            while (str[i++] != 34)
                ;
        }
        else if (str[i] == 39)
        {
            i++;
            while (str[i++] != 39)
                ;
        }
        if (str[i] == ' ')
            j++;
        i++;
    }
    return (j);
}

static size_t second_alloc(const char *str)
{
    size_t  i;
    size_t  j;

    i = 0;
    j = 0;
    while (str[i] && str[i] != 32)
    {
        if (str[i] == 34)
        {
            while (str[++i] != 34)
                j++;
            break;
        }
        else if (str[i] == 39)
        {
            while (str[++i] != 39)
                j++;
            break;
        }
        j++;
        i++;
    }
    return (j);
}

int main(void)
{
    char    str[100] = "'ola mundo' melhor";

    printf("%ld\n", second_alloc(str));
    return (0);
}