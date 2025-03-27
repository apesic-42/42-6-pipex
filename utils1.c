#include "pipex.h"
#include <sys/wait.h>

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

// int clean_exit(t_pipexelement *pipexx)
// {
//     t_pipexelement *current;

//     current = pipexx;
//     close_fds(pipexx);


// 	int	k;
// 	int	rn;

// 	k = 0;
// 	rn = 0;
// 	while (current)
// 	{
// 		waitpid(current->pid, &k, 0);
// 		current = current->next;
// 	}

// 	rn = k >> 8;
//     free_chained_list(pipexx);
// 	return (rn);
// }

int clean_exit(t_pipexelement *pipexx)
{
    t_pipexelement *current = pipexx;
    int status;
    int last_status = 0;

    close_fds(pipexx);

    // Wait for all processes but only care about the last one's status
    while (current)
    {
        if (current->next == NULL)  // This is the last command (grep)
        {
            waitpid(current->pid, &status, 0);
            if ((status & 0xFF) == 0)  // Normal exit
                last_status = (status >> 8) & 0xFF;  // Extract exit code
            else
                last_status = 1;  // Default to 1 for failures
        }
        else
        {
            waitpid(current->pid, NULL, 0);  // Ignore status of non-last commands
        }
        current = current->next;
    }

    free_chained_list(pipexx);
    return last_status;
}

int	error_case(char *str, t_pipexelement *pipexx)
{
	close_fds(pipexx);
	free_chained_list(pipexx);
	perror(str);
	free(str);
	return (1);
}
