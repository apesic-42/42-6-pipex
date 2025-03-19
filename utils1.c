#include "pipex.h"


char	*find_binary(char *str, char **path)
{
	char	*bin;
	char    *tm;

	while (*path)
	{
	    tm =  ft_strjoin(*path, "/");

    	bin = ft_strjoin(tm, str);
        free(tm);
		if (access(bin, F_OK) == 0)
		{
		    if (access(bin, X_OK) == 0)
               	return (bin);
			else
			{
			    free(bin);
				printf("icici\n");
                return (NULL);
			}
		}
		path++;
		free(bin);
	}
	printf("icici2\n");
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

int close_fds(t_pipexelement *first)
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
