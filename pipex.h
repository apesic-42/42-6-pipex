
#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/printf/ft_printf.h"
# include "./libft/get_next_line/get_next_line.h"
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
	char    *limiter;
	struct s_pipexelement *next;

}			t_pipexelement;
// astuce int[3] (pour pouvoir stocker temporairement)

int	error_case(char *str, t_pipexelement *pipexx);
char		*find_binary(char *str, char **path);
int     clean_exit(t_pipexelement *pipexx, char **path);
int make_process(t_pipexelement *head, char **v, char **env);
int close_fds(t_pipexelement *first);
int here_doc(char *limiter);

#endif // FT_H
