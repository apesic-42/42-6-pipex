
#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/get_next_line/get_next_line.h"
# include "./libft/printf/ft_printf.h"
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipexelement
{
	int						fd_in;
	int						fd_out;
	int						error;
	pid_t                   pid;
	char					*cmd;
	char					*limiter;
	struct s_pipexelement	*next;

}							t_pipexelement;

int							error_case(char *str, t_pipexelement *pipexx);
char						*find_binary(char *str, char **path);
int							clean_exit(t_pipexelement *pipexx);
int							make_process(t_pipexelement *head, char **env);
int							close_fds(t_pipexelement *first);
int							here_doc(char *limiter);
t_pipexelement				*init_chain(t_pipexelement *pipexobj, char **v,
								int i);
char						*get_cmd(const char *path);
int							multi_dup(t_pipexelement *head, int *fd, int in_fd);
char *test_binary(char *bin);

#endif // FT_H
