
#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/printf/ft_printf.h"
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
#include <sys/types.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>


typedef struct t_pipexelement
{
	int            fd_file1;
	int            fd_file2;
    int            pip_fd[2]; // lecture [0], ecriture [1]
    pid_t          pid_fork1;
    pid_t          pid_fork2;
}						t_pipexelement;


int error_case(char *str);
char* find_binary(char *str, char** env);

#endif // FT_H
