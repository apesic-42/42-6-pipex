
#include "pipex.h"


int make_process(t_pipexelement *head, char **v, char **env)
{
    int fd[2], in_fd = 0;

    while (head != NULL) {
        pipe(fd);
        if ((head->pid_fork = fork()) == 0) {

            if (head->fd_in == -228)
                dup2(in_fd, STDIN_FILENO);  // Utiliser l'ancien in_fd comme entrée
            else
                dup2(head->fd_in, STDIN_FILENO);
            if (head->fd_out == -228)   // S'il y a une commande suivante, utiliser fd[1] comme sortie
                dup2(fd[1], STDOUT_FILENO);
            else
                dup2(head->fd_out, STDOUT_FILENO);
            close(fd[0]); // Fermer l'entrée du pipe dans le processus enfant
            execve(find_binary(head->cmd, env), ft_split(head->cmd, ' '), env); // Assurez-vous de parser la commande correctement
            perror("execvp");
            exit(EXIT_FAILURE);
        }
        close(fd[1]);  // Fermer la sortie du pipe dans le parent
        if (in_fd != 0) {
            close(in_fd);  // Fermer le précédent in_fd s'il n'est pas le stdin initial
        }
        in_fd = fd[0];  // Préparer in_fd pour la prochaine commande
        head = head->next;
    }

    // Fermer le dernier in_fd
    if (in_fd != 0)
        close(in_fd);
    return (0);
}
