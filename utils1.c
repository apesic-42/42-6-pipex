#include "pipex.h"

int	error_case(char *str)
{
	perror(str);
	printf("ok\n");
	return (1);
}

char	*find_binary(char *str, char **env)
{
	char		**spl;
	const char	*path;
	char		*pl;
	char		*path_value;

	str = ft_split(str, ' ')[0];
	while (*env)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
		{
			path_value = ft_strchr(*env, '=') + 1;
			path = path_value;
			break ;
		}
		env++;
	}
	spl = ft_split(path, ':');
	while (*spl)
	{
		if (access(*spl, F_OK | X_OK) == 0)
			break ;
		spl++;
	}
	return (ft_strjoin(ft_strjoin(*spl, "/"), str));
}

int clean_exit(t_pipexelement *pipexx)
{
    free(pipexx);
    return (0);
}
