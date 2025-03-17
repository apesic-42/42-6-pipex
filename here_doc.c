
#include "pipex.h"


static int pipee(int *fds)
{
   	if (pipe(fds) == -1)
        return (-1);
    return (0);
}

static bool place(char *str)
{
    free(str);
    return (false);
}

int here_doc(char *limiter)
{
    char *line = NULL;
    char * wbn;
    int fds[2];
    bool varr;

    varr = true;
    wbn = ft_strjoin(limiter, "\n");
    if (!wbn || pipee(fds) == -1)
        return (-1);
    while (varr == true)
    {
        ft_printf("> ");
        line = get_next_line(STDIN_FILENO);
        if (line == NULL)
            varr = place(limiter);
        if (ft_strncmp(wbn , line, ft_strlen(line)) == 0)
            varr = place(line);
        write(fds[1], line, strlen(line));
    }
    close(fds[1]);
    return (fds[0]);
}
