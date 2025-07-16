/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_get_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroberts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:09:56 by lroberts          #+#    #+#             */
/*   Updated: 2025/07/16 06:48:14 by lroberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_handle_error(char **splitted_cmd, char **paths, char *msg, int code)
{
	free_dbl_ptrs(splitted_cmd, paths, NULL);
	ft_fail(msg, code);
}

char	*get_path(char **splitted_cmd, char **envp)
{
	size_t	i;
	char	**paths;

	
	i = 0;
	paths = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			exit(errno);
			paths = ft_split(envp[i] + 5, ':');
			if (paths == NULL)
				ft_handle_error(splitted_cmd, NULL, "ft_split fail-get_path", 1);
			break ;
		}
		i++;
	}
	if (paths == NULL)
	{
		ft_handle_error(splitted_cmd, NULL, "PATH not in env - get_path", 2);
	}
	return (ft_test_paths(splitted_cmd, paths));
}

char	*ft_test_paths(char **splitted_cmd, char **paths)
{
	char	**back_slashed_paths;
	char	*accessible;
	size_t	i;

	back_slashed_paths = append_backslash(paths);
	free_dbl_ptrs(paths, NULL);
	if (!back_slashed_paths)
		ft_handle_error(splitted_cmd, NULL, "app*_back\\ fail-ft_test_paths", 3);
	i = 0;
	while (back_slashed_paths[i])
	{
		accessible = ft_strjoin(back_slashed_paths[i], splitted_cmd[0]);
		if (!accessible)
			ft_handle_error(splitted_cmd, back_slashed_paths, "malloc fail", 4);
		if (access(accessible, X_OK) == 0)
		{
			free_dbl_ptrs(back_slashed_paths, NULL);
			return (accessible);
		}
		free(accessible);
		i++;
	}
	ft_handle_error(splitted_cmd, back_slashed_paths,
		"no binaries available with that name - ft_test_paths", 5);
	return (NULL);
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
