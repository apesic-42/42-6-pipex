
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
	int     fd_in;
	int     fd_out;
	pid_t	pid_fork;
	char	*error;
	char    *cmd;
	struct s_pipexelement *next;

}			t_pipexelement;
// astuce int[3] (pour pouvoir stocker temporairement)

int	error_case(char *str, t_pipexelement *pipexx);
char		*find_binary(char *str, char **env);
int     clean_exit(t_pipexelement *pipexx);
int make_process(t_pipexelement *head, char **v, char **env);


#endif // FT_H
