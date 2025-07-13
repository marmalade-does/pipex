
#include "pipex.h"

/* ft_fail ->> look with a ctrll shift f for all the  fucntions that ft_fail
get_path
void ft_here_we_are(char *delimeter)
append_backslash
*/

char *get_path(char **splitted_cmd, char **envp)
{
	size_t i;
	char **paths_base;
	char **paths_tmp;
	char *accesible_path;

	i = -1;
	paths_base = NULL;
	paths_tmp = NULL;
	while(envp[++i])
	{
		if(if(ft_strncmp(envp[i], "PATH=", 5) == 0))
		{
			if (paths_base == NULL)
			{
				paths_base = ft_split(envp[i] + 5, ':');
				if (paths_base == NULL)
				{
					free_dbl_ptrs(splitted_cmd, NULL, NULL);
					ft_fail("ft_split failed - get_path", 1);
				}
			}
			else
			{
				paths_tmp = ft_split(envp[i] + 5, ':');
				if (paths_tmp == NULL)
				{
					free_dbl_ptrs(splitted_cmd, paths_base, NULL);
					ft_fail("ft_split failed - get_path", 1);
				}
				paths_base = ft_merge_paths(paths_base, paths_tmp); /// these free it internally
				if (paths_base == NULL)
				{
					free_dbl_ptrs(splitted_cmd, NULL, NULL);
					ft_fail("ft_merge_paths failed - get_path", 2);
				}
			}
		}
	}
	return(ft_test_paths(splitted_cmd, paths_base));
}

// **yet to inlpement**: need to free paths, splitted_cmd and back_slashed_paths on failure
char	*ft_test_paths(char **splitted_cmd, char **paths)
{
	char *accesible;
	char **back_slashed_paths;
	size_t i;

	i = 0;
	back_slashed_paths = append_backslash(paths);
	while(back_slashed_paths[i])
	{
		accesible = ft_strjoin(back_slashed_paths[i], splitted_cmd[0]);
		if(accesible == NULL)
		{
			free_dbl_ptrs(paths, splitted_cmd, back_slashed_paths, NULL);
			ft_fail("malloc failed - ft_test_paths", 3);
		}
		if(access(accesible, X_OK) == 0)
			return (free_dbl_ptrs(paths, splitted_cmd, back_slashed_paths, NULL), accesible);
		i++;
		free(accesible);
	}
	free_dbl_ptrs(paths, splitted_cmd, back_slashed_paths, NULL);
	ft_fail("no binaries avaiable with that name - ft_test_paths", 6);
}

void free_dbl_ptrs(char **first, ...)
{
    va_list args;
    char **ptr;
    size_t i;
    
    // Handle the first argument
    if (first) {
        i = 0;
        while (first[i])
            free(first[i++]);
        free(first);
    }
    
    // Initialize variadic argument list
    va_start(args, first);
    
    // Process remaining arguments until NULL
    while ((ptr = va_arg(args, char **)) != NULL) {
        i = 0;
        while (ptr[i])
            free(ptr[i++]);
        free(ptr);
    }
    
    va_end(args);
}

char	**ft_merge_paths(char **paths_base, char **paths_tmp)
{
	size_t i;
	size_t j;
	size_t len_total;
	char **merged_paths;

	len_total = ft_total_dbl_ptr_len(paths_base, paths_tmp);
	merged_paths = (char **)malloc(sizeof(char *) * (len_total + 1));
	if (merged_paths == NULL)
		return (NULL);
	i = -1;
	while (paths_base[++i])
	{
		merged_paths[i] = (char *)malloc(ft_strlen(paths_base[i]) + 1);
		if (!merged_paths[i])
			return (free_dbl_ptrs(paths_base, paths_tmp, merged_paths, NULL), NULL);
		ft_strlcpy(merged_paths[i], paths_base[i], ft_strlen(paths_base[i]) + 1);
	}
	j = -1;
	while (paths_tmp[++j])
	{
		merged_paths[i + j] = (char *)malloc(ft_strlen(paths_tmp[j]) + 1);
		if (!merged_paths[i + j])
			return (free_dbl_ptrs(paths_base, paths_tmp, merged_paths, NULL), NULL);
		ft_strlcpy(merged_paths[i + j], paths_tmp[j], ft_strlen(paths_tmp[j]) + 1);
	}
	merged_paths[i + j] = NULL;
	free_dbl_ptrs(paths_base, paths_tmp, NULL);
	return (merged_paths);
}


static size_t ft_total_dbl_ptr_len(char **paths_base, char **paths_tmp)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (paths_base[i])
		i++;
	while (paths_tmp[j])
		j++;
	return (i + j);
}

void ft_fail(char *errmsg, int fail_num)
{
	perror(errmsg);
	exit(fail_num);
}

