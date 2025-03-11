
#include "pipex.h"


static void get_fd_pipe(t_pipexelement *pipexobj, int *pipfds)
{
    pipfds[1] = pipexobj->fd_out;
    while (pipexobj->next != NULL)
        pipexobj = pipexobj->next;
    pipfds[0] = pipexobj->fd_in;
}

static int childrens(t_pipexelement *pipexobj, char **v, char **env)
{
    int pipfds[2];

    get_fd_pipe(pipexobj, pipfds);
    //gerer les fds, faire la commande
    if (dup2(pipexobj->fd_in, STDIN_FILENO) == -1)
        return (error_case("dup2", pipexobj));
    if (dup2(pipexobj->fd_out, STDOUT_FILENO) == -1)
        return (error_case("dup2", pipexobj));
    if (execve(find_binary(pipexobj->cmd, env), ft_split(pipexobj->cmd, ' '), NULL) == -1)
        return (error_case("execvs", pipexobj));
    return (0);
}


static int parent(t_pipexelement *pipexobj)
{
    int status;
    pid_t terminated_pid = wait(&status);
    return (0);
}
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


int make_process(t_pipexelement *head, char **v, char **env)
{
    t_pipexelement *current = head;

    while (current != NULL)
    {
        current->pid_fork = fork();
        if (current->pid_fork == -1)
            return (error_case("fork", head));
        if (current->pid_fork == 0) //enfant
        {
            if (childrens(head, v, env) == 1)
                return (1);
        }
        else
        {
            if (parent(head) == 1)
                return (1);
        }
        current = current->next;
    }
    return (0);
}
