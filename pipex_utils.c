#include "pipex.h"

char	*get_path(char **splitted_cmd, char **envp)
{
	size_t	i;
	char	**paths;
	//write(2, "checkpoint 20\n", 14); // remove later

	i = 0;
	paths = NULL;
	//write(2, "checkpoint 20\n", 14); // remove later
	// Find the single PATH variable
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			paths = ft_split(envp[i] + 5, ':');
			if (paths == NULL)
			{
				free_dbl_ptrs(splitted_cmd, NULL);
				ft_fail("ft_split failed - get_path", 1);
			}
			break ;
		}
		i++;
	}
	// If no PATH found, handle error
	if (paths == NULL)
	{
		free_dbl_ptrs(splitted_cmd, NULL);
		ft_fail("PATH not found in environment - get_path", 2);
	}
	return (ft_test_paths(splitted_cmd, paths));
}

char	*ft_test_paths(char **splitted_cmd, char **paths)
{
	char	*accessible;
	char	**back_slashed_paths;
	size_t	i;

	i = 0;
	back_slashed_paths = append_backslash(paths);
	free_dbl_ptrs(paths, NULL);
		// Free paths immediately after creating back_slashed_paths
	if (back_slashed_paths == NULL)
	{
		free_dbl_ptrs(splitted_cmd, NULL);
		ft_fail("append_backslash failed - ft_test_paths", 3);
	}
	while (back_slashed_paths[i])
	{
		accessible = ft_strjoin(back_slashed_paths[i], splitted_cmd[0]);
		if (accessible == NULL)
		{
			free_dbl_ptrs(splitted_cmd, back_slashed_paths, NULL);
			ft_fail("malloc failed - ft_test_paths", 4);
		}
		if (access(accessible, X_OK) == 0)
		{
			free_dbl_ptrs(splitted_cmd, back_slashed_paths, NULL);
			return (accessible);
		}
		free(accessible);
		i++;
	}
	free_dbl_ptrs(back_slashed_paths, splitted_cmd, NULL);
	ft_fail("no binaries available with that name - ft_test_paths", 5);
	return (NULL); // Never reached due to ft_fail exit
}

char	**append_backslash(char **paths)
{
	size_t	i;
	char	**back_slashed_paths;

	if (paths == NULL)
		return (NULL);
	i = 0;
	while (paths[i])
		i++;
	back_slashed_paths = (char **)malloc(sizeof(char *) * (i + 1));
	if (back_slashed_paths == NULL)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		back_slashed_paths[i] = ft_strjoin(paths[i], "/");
		if (!back_slashed_paths[i])
		{
			free_dbl_ptrs(back_slashed_paths, NULL);
			return (NULL);
		}
		i++;
	}
	back_slashed_paths[i] = NULL;
	return (back_slashed_paths);
}

void	free_dbl_ptrs(char **first, ...)
{
	va_list	args;
	char	**ptr;
	size_t	i;

	// Handle the first argument
	if (first)
	{
		i = 0;
		while (first[i])
			free(first[i++]);
		free(first);
	}
	// Initialize variadic argument list
	va_start(args, first);
	// Process remaining arguments until NULL
	while ((ptr = va_arg(args, char **)) != NULL)
	{
		i = 0;
		while (ptr[i])
			free(ptr[i++]);
		free(ptr);
	}
	va_end(args);
}

void	ft_fail(char *errmsg, int fail_num)
{
	perror(errmsg);
	exit(fail_num);
}
