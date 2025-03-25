
#include "pipex.h"

bool all_is_not_null(char **v,int c)
{
    int i ;
     i= 1;

    while(i < c)
    {
        if (ft_strcmp("", v[i]) == 0)
            return (true);
        i++;
    }
    return (false);
}
