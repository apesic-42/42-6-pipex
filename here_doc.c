
#include "pipex.h"


static int pipee(int *fds)
{
   	if (pipe(fds) == -1)
        return (-1);
    return (0);
}

static char * place(char *str)
{
    free(str);
    return (NULL);
}


static int finish(char *f1, char *f2, int c1, int r1)
{
    free(f1);
    free(f2);
    close(c1);
    return (r1);
}

int here_doc(char *limiter)
{
    char *line;
    char *wbn;
    int fds[2];

    wbn = ft_strjoin(limiter, "\n");
    if (!wbn || pipee(fds) == -1)
        return (-1);
    while (line != NULL)
    {
        ft_printf("> ");
        line = get_next_line(STDIN_FILENO);
        if (ft_strcmp(wbn , line) == 0)
            line = place(line);
        if (line != NULL)
            write(fds[1], line, ft_strlen(line));
        place(line);
    }
    return (finish(wbn, line, fds[1], fds[0]));
}
