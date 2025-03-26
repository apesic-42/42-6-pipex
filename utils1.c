#include "pipex.h"

char	*find_binary(char *str, char **path)
{
	char	*bin;
	char	*tp;

	while (*path)
	{
		tp = ft_strjoin(*path, "/");
		bin = ft_strjoin(tp, str);
		free(tp);
		if (access(bin, F_OK) == 0)
		{
			if (access(bin, X_OK) == 0)
			{
				free_double_table(path);
				return (bin);
			}
			else
			{
				free(bin);
				return (NULL);
			}
		}
		path++;
		free(bin);
	}
	return (NULL);
}

static void	free_chained_list(t_pipexelement *pipexx)
{
	t_pipexelement	*current;
	t_pipexelement	*next;

	current = pipexx;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

int	close_fds(t_pipexelement *first)
{
	while (first != NULL)
	{
		if (first->fd_in >= 0)
		{
			if (close(first->fd_in) == -1)
				return (-1);
		}
		if (first->fd_out >= 0)
		{
			if (close(first->fd_out) == -1)
				return (-1);
		}
		first = first->next;
	}
	return (0);
}

// Fonction pour libérer une liste chaînée
int	clean_exit(t_pipexelement *pipexx)
{
	close_fds(pipexx);
	free_chained_list(pipexx);
	return (0);
}

int	error_case(char *str, t_pipexelement *pipexx)
{
	close_fds(pipexx);
	free_chained_list(pipexx);
	perror(str);
	free(str);
	return (1);
}
