
#include "pipex.h"
#include <sys/ucontext.h>
#include <unistd.h>


static int filesfds(int *fd_files, char **v, int c)
{
    int re;

    re = 0;
    if (ft_strncmp(v[1], "here_doc", 8) == 0)
    {
        fd_files[0] = -128;
        re++;
    }
    else
        fd_files[0] = open(v[1], O_RDONLY);
    fd_files[1] = open(v[c - 1], O_WRONLY | O_CREAT, 0644);
    if (fd_files[0] == -1 || fd_files[1] == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    return (re);
}


int put_fds(t_pipexelement *first, int *fd_files)
{
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


t_pipexelement *init_chain(t_pipexelement	*pipexobj, char **v, int i)
{
   	pipexobj = (t_pipexelement *)ft_calloc(sizeof(t_pipexelement), 1);
    if (!pipexobj)
    {
        error_case("malloc", pipexobj);
        return (pipexobj);
    }
    pipexobj->cmd = v[i];
    pipexobj->limiter = v[2];
    return (pipexobj);
}



static void placee(t_pipexelement *nexte, t_pipexelement *pipexobj, t_pipexelement *first, char *vi)
{

    nexte = (t_pipexelement *)ft_calloc(sizeof(t_pipexelement), 1);
    if (nexte == NULL)
        first->error = "malloc";
    pipexobj->next = nexte;
    nexte->cmd = vi;
    pipexobj = nexte;
}

int	main(int c, char **v, char **env)
{
	t_pipexelement	*pipexobj;
	t_pipexelement	*first;
    t_pipexelement	*nexte;
	int i;
	int		fd_files[2];

	if (c < 5)
		return (0);
	if (env[0] == NULL)
	    env = NULL;
	i = 1;
	i += filesfds(fd_files, v, c);
    pipexobj = init_chain(pipexobj, v, ++i);
    first = pipexobj;
    while (i < c - 2)
        placee(nexte, pipexobj, first, v[++i]);
    if (first->error == "malloc")
        return (error_case("malloc", first));
	if (put_fds(first, fd_files) == 1)
	   return (-1);
	if (make_process(first, v, env) == 1)
	   return (127);
	return (0);
}



// int	main(int c, char **v, char **env)
// {
// 	t_pipexelement	*pipexobj;
// 	t_pipexelement	*nexte;
// 	t_pipexelement	*first;
// 	int i;
// 	int		fd_files[2];

// 	if (c < 5)
// 		return (0);
// 	i = 1;
// 	i += filesfds(fd_files, v, c);
// 	i++;
//     pipexobj = init_chain(pipexobj, v, i);
//     first = pipexobj;
//     while (i < c - 2)
//     {
//         nexte = (t_pipexelement *)ft_calloc(sizeof(t_pipexelement), 1);
//         if (nexte == NULL)
//             return (error_case("malloc", first));
//         pipexobj->next = nexte;
//         nexte->cmd = v[++i];
//         pipexobj = nexte;
//     }
// 	if (put_fds(first, fd_files) == 1)
// 	   return (-1);
// 	if (make_process(first, v, env) == 1)
// 	   return (127);
// 	return (0);

// }
