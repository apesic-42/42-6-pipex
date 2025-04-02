/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:56:01 by apesic            #+#    #+#             */
/*   Updated: 2025/03/27 15:12:07 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define CNF "command not found : "
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
	int						error;
	pid_t					pid;
	char					*cmd;
	struct s_pipexelement	*next;
}							t_pipexelement;
typedef struct s_pipex
{
	int						fd_in;
	int						fd_out;
	int						error;
	char					**env;
	char					*limiter;
	struct s_pipexelement	*start;
	int						fd[3];
}							t_pipex;

int							error_case(t_pipex *pipex, char *str,
								char **cmd_spl);
char						*find_binary(char *str, char **path);
int							clean_exit(t_pipex *pipex);
int							make_process(t_pipex *pipex);
int							here_doc(t_pipex *pipex);
t_pipexelement				*init_chain(t_pipex *pipex,
								t_pipexelement *pipexobj, char **v, int i);
char						*get_cmd(const char *path);
int							du(t_pipex *pipex, t_pipexelement *head,
								char **cmd_spl);
char						*ch(t_pipex *pipex, char *s, char **cmd_spl);
void						ft_closem1(int fd);

#endif // FT_H
