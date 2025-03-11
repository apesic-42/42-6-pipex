
#include "pipex.h"
#include <sys/ucontext.h>
#include <unistd.h>

// static t_pipexelement	*init_fork_1(t_pipexelement *pipexobj, char **v)
// {
// 	pipexobj->fd_file1 = open(v[1], O_RDONLY);
// 	if (pipexobj->fd_file1 == -1)
// 	{
// 		pipexobj->error = "open";
// 		return (pipexobj);
// 	}
// 	if (pipe(pipexobj->pip_fd) == -1)
// 	{
// 		perror("pipe");
// 		exit(EXIT_FAILURE);
// 	}
// 	pipexobj->pid_fork1 = fork();
// 	if (pipexobj->pid_fork1 == -1)
// 	{
// 		perror("fork");
// 		exit(EXIT_FAILURE);
// 	}
// 	return (pipexobj);
// }




// static t_pipexelement	*childrens(t_pipexelement *pipexobj, char **v,
// 		char **env)
// {
// 	int    status;

// 	pipexobj->pid_fork2 = fork();
// 	if (pipexobj->pid_fork2 == -1)
// 	{
// 		perror("fork");
// 		exit(EXIT_FAILURE);
// 	}
// 	if (pipexobj->pid_fork2 == 0)
// 	{
//         pipexobj->fd_file2 = open(v[4], O_WRONLY | O_CREAT, 0644);
//        	if (pipexobj->fd_file2 == -1)
//        	{
//       		pipexobj->error = "open";
//       		return (pipexobj);
//        	}
//         FdSet fds1 = {pipexobj->pip_fd[0], pipexobj->fd_file2, pipexobj->pip_fd[1]};
//         if (ft_strncmp(childs(fds1, v[3], env), "ok", 2) != 0) {
//             return (pipexobj);
//         }
// 	}
// 	else
// 	{
// 	    waitpid(pipexobj->pid_fork1, &status, 0);
// 		waitpid(pipexobj->pid_fork2, &status, 0);
// 		close(pipexobj->fd_file2);
// 		close(pipexobj->fd_file1);
// 		close(pipexobj->pip_fd[0]);
// 		close(pipexobj->pip_fd[1]);
// 	}
// 	return (pipexobj);
// }
//


// static char *childs(FdSet fds, char *cmd, char **env) {
//     if (dup2(fds.fd_in, STDIN_FILENO) == -1) {
//         perror("dup2");
//         close(fds.fd_in);
//         exit(EXIT_FAILURE);
//     }
//     if (dup2(fds.fd_out, STDOUT_FILENO) == -1) {
//         perror("dup2");
//         close(fds.fd_out);
//         exit(EXIT_FAILURE);
//     }
//     close(fds.fd_extra);
//     if (execve(find_binary(cmd, env), ft_split(cmd, ' '), NULL) == -1) {
//         perror("execve");
//         exit(EXIT_FAILURE);
//     }
//     return "ok";
// }


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
    int pipfds[2]; // 0 -> lire | 1 -> ecrire
    int i;

    i = 0;
    if (pipe(pipfds) == -1)
        return (error_case("pipe", first));
    first->fd_in = fd_files[0];
    first->fd_out = pipfds[1];
    first = first->next;
    while (first->next != NULL)
    {
        first->fd_in = pipfds[0];
        first->fd_out = pipfds[1];
        first = first->next;
    }
    first->fd_in = pipfds[0];
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

void print_pipex_list(t_pipexelement *head) {
    t_pipexelement *current = head;
    int position = 0;

    while (current != NULL)
    {
        printf("Position: %d, Command: %s, fd1 : %d, fd2 : %d\n", position, current->cmd, current->fd_in, current->fd_out);
        current = current->next;
        position++;
    }
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
	   return (127);
    print_pipex_list(first);
	if (make_process(first, v, env) == 1)
	   return (127);
	return (clean_exit(first));


	// if (!pipexobj)
	//    return (0);
	// pipexobj = init_fork_1(pipexobj, v);
	// if (pipexobj->error != NULL)
	// 	return (error_case(pipexobj->error));
	// if (pipexobj->pid_fork1 == 0)
	// {
	// 	FdSet fds2 = {pipexobj->fd_file1, pipexobj->pip_fd[1], pipexobj->pip_fd[0]};
 //        if (ft_strncmp(childs(fds2, v[3], env), "ok", 2) != 0) {
 //            return error_case(pipexobj->error);
 //        }
	// }
	// else
	// {
	// 	pipexobj = childrens(pipexobj, v, env);
	// 	if (pipexobj->error != NULL)
	// 		return (error_case(pipexobj->error));
	// }
}
