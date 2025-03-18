
#include "pipex.h"

static int	multi_dup(t_pipexelement *head, int *fd, int in_fd)
{
	if (head->fd_in == -228 || head->fd_in == -128)
		dup2(in_fd, STDIN_FILENO);
	else
		dup2(head->fd_in, STDIN_FILENO);
	if (head->fd_out == -228)
		dup2(fd[1], STDOUT_FILENO);
	else
		dup2(head->fd_out, STDOUT_FILENO);
	close(fd[0]);
    close(fd[1]);
	return (0);
}

static char	**spl_path(char **env)
{
	const char	*path;
	char		**spl;

	while (*env)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
		{
			path = ft_strchr(*env, '=') + 1;
			break ;
		}
		env++;
	}
	spl = ft_split(path, ':');
	return (spl);
}


char *get_cmd(const char *path) {
    char *last_slash = ft_strrchr(path, '/');

    if (last_slash != NULL) {
        // Avancez d'un caractère pour obtenir le début du nom de la commande
        return last_slash + 1;
    } else {
        // Si aucun '/' n'est trouvé, retournez le chemin original
        return (char *)path;
    }
}

static char *un_bb(char **env, t_pipexelement *head, int fd[2], t_pipexelement *headd)
{

	int             i;
	char			**pathhh;
	char			*bin;
	char			**cmd_spl;

	i = 0;

	cmd_spl = ft_split(head->cmd, ' ');
	multi_dup(head, fd, fd[2]);

	// la thechique du / est mauvaise
	// il faut chercher si le chemin complet + l'executable (bin) est executable

	if (ft_strchr(cmd_spl[0], '/') == NULL) //si oui il n'y a pas de /, c'est une commande
	{
	    pathhh = spl_path(env);
    	bin = find_binary(cmd_spl[0], pathhh);
    	free_double_table(pathhh);
        clean_exit(headd);
       	printf("cmdij : %s bin ; %s\n", cmd_spl[0], bin);
        execve(bin, cmd_spl, env);
        exit(1);
	}
	else
	{
    	clean_exit(headd);
    	bin = cmd_spl[0];
    	cmd_spl[0] = get_cmd(cmd_spl[0]);
    	printf("cmd : %s bin ; %s\n", cmd_spl[0], bin);
    	execve(bin, cmd_spl, env);
    	exit(1);
	}
}

int make_process(t_pipexelement *head, char **v, char **env)
{
	int				fd[3];
	t_pipexelement	*headd;

	headd = head;
	while (head != NULL)
	{
		if (pipe(fd) == -1)
			return (error_case("pipe", headd));
		if (head->fd_in == -128)
		{
			fd[2] = here_doc(head->limiter);
			if (fd[2] == -1)
				return (-1);
		}
		if ((head->pid_fork = fork()) == 0)
		{
		  un_bb(env, head, fd, headd);
		}
		close(fd[1]);
		if (fd[2] != 0)
			close(fd[2]);
		fd[2] = fd[0];
		head = head->next;
	}
	if (fd[2] != 0)
		close(fd[2]);
	return (clean_exit(headd));
}
