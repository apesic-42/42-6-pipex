
#include "pipex.h"
#include <sys/ucontext.h>
#include <unistd.h>


static void filesfds(int *fd_files, char **v, int c)
{
    fd_files[0] = open(v[1], O_RDONLY);
    fd_files[1] = open(v[c - 1], O_WRONLY | O_CREAT, 0644);
    if (fd_files[0] == -1 || fd_files[1] == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
}


int put_fds(t_pipexelement *first, int *fd_files)
{
    int i;

    i = 0;

    first->fd_in = fd_files[0];
    first->fd_out = -228;
    first = first->next;
    while (first->next != NULL)
    {
        first->fd_in = -228;
        first->fd_out = -228;
        first = first->next;
    }
    first->fd_in = -228;
    first->fd_out = fd_files[1];
    return (0);
}


t_pipexelement *init_chain(t_pipexelement	*pipexobj, char *vi)
{
   	pipexobj = (t_pipexelement *)ft_calloc(sizeof(t_pipexelement), 1);
    if (!pipexobj)
    {
        error_case("malloc", pipexobj);
        return (pipexobj);
    }
    pipexobj->cmd = vi;
    return (pipexobj);
}



int	main(int c, char **v, char **env)
{
	t_pipexelement	*pipexobj;
	t_pipexelement	*nexte;
	t_pipexelement	*first;
	int i;
	int		fd_files[2];

	if (c < 5)
		return (0);
	i = 1;
	filesfds(fd_files, v, c);
    pipexobj = init_chain(pipexobj, v[++i]);
    first = pipexobj;
    while (i < c - 2)
    {
        nexte = (t_pipexelement *)ft_calloc(sizeof(t_pipexelement), 1);
        if (nexte == NULL)
            return (error_case("malloc", first));
        pipexobj->next = nexte;
        nexte->cmd = v[++i];
        pipexobj = nexte;
    }

	if (put_fds(first, fd_files) == 1)
	   return (-1);
	if (make_process(first, v, env) == 1)
	   return (127);
	return (0);

}
