
#include "pipex.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>




static int pipee(int *fds)
{
   	if (pipe(fds) == -1)
        return (-1);
    return (0);
}



int here_doc(char *limiter)
{
    char *line = NULL;
    char * wbn;
    int fds[2];

    wbn = ft_strjoin(limiter, "\n");
    if (!wbn || pipee(fds) == -1)
        return (-1);
    while (1)
    {
        ft_printf("> ");
        line = get_next_line(STDIN_FILENO);
        if (line == NULL) {
            free(limiter);
            break;
        }
        if (ft_strncmp(wbn , line, ft_strlen(line)) == 0) {
            free(line);
            break;
        }
        write(fds[1], line, strlen(line));
    }
    close(fds[1]);
    return (fds[0]);
}

// void	here_doc_put_in(char **av, int *p_fd)
// {
// 	char	*ret;

// 	close(p_fd[0]);
// 	while (1)
// 	{
// 		ret = get_next_line(0);
// 		if (ft_strncmp(ret, av[2], ft_strlen(av[2])) == 0)
// 		{
// 			free(ret);
// 			exit(0);
// 		}
// 		ft_putstr_fd(ret, p_fd[1]);
// 		free(ret);
// 	}
// }

// void	here_doc(char **av)
// {
// 	int		p_fd[2];
// 	pid_t	pid;

// 	if (pipe(p_fd) == -1)
// 		exit(0);
// 	pid = fork();
// 	if (pid == -1)
// 		exit(0);
// 	if (!pid)
// 		here_doc_put_in(av, p_fd);
// 	else
// 	{
// 		close(p_fd[1]);
// 		dup2(p_fd[0], 0);
// 		wait(NULL);
// 	}
// }
