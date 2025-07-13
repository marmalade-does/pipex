#include "pipex.h"

char	*find_path(char *cmd, char **envp);
void	error(void);
void	execute(char *argv, char **envp);
int	    get_next_line(char **line);


/* Function that take the command and send it to find_path
 before executing it. */
void	execute(char *argv, char **envp)
{
	char	**cmd;
	int 	i;
	char	*path;
	
	i = 0;
	cmd = ft_split(argv, ' ');
	path = find_path(cmd[0], envp); // always cmd[0] since the first one is the command, the rest is flags
	if (!path)	
	{
		while (cmd[i])
        {
			free(cmd[i]);
            i++;
        }
        free(cmd);
		error();
	}
	if (execve(path, cmd, envp) == -1)
		error();
}


/* Function parses the PATHs from the env variable, 
 splits and tests each command path and then returns the first one that works. */
char	*find_path(char *cmd, char **envp)
{
    char	**paths;
    char	*path;
    int		i;
    char	*part_path;

    paths = pip_get_path(envp); // parses all the paths from the env variable
    if (!paths)
        return (NULL);
    i = 0;
    while (paths[i])
    {
        part_path = ft_strjoin(paths[i], "/");
        path = ft_strjoin(part_path, cmd);
        free(part_path);
        if (access(path, F_OK) == 0)
        {
            i = 0;
            while (paths[i])
                free(paths[i++]);
            free(paths);
            return (path);
        }
        free(path);
        i++;
    }
    i = 0;
    while (paths[i])
        free(paths[i++]);
    free(paths);
    return (NULL);
}
  
/* A simple error displaying function. */
void	error(void)
{
	perror("\033[31mError");
	exit(EXIT_FAILURE);
}

