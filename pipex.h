
#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/printf/ft_printf.h"
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipexelement
{
	int		fd_file1;
	int		fd_file2;
	int		pip_fd[2];
	pid_t	pid_fork1;
	pid_t	pid_fork2;
	char	*error;
}			t_pipexelement;

int			error_case(char *str);
char		*find_binary(char *str, char **env);
int         clean_exit(t_pipexelement * pipexx);

#endif // FT_H
