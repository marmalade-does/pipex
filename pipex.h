
#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <stdarg.h>
# include <sys/wait.h>
# include "./includes/libft/libft.h" 

// pipex.c
void children(char *arg, char **envp);
void wrapped_execve(char *arg, char **envp);


// pipex_here_utils.c
void	free_dbl_ptrs(char **first, ...);
void	ft_fail(char *errmsg, int fail_num);
void	ft_here_we_are(char *delimeter);
int     pipex_rd_nxt_line(char **line);

// pipex_get_path.c
char	*get_path(char **splitted_cmd, char **envp);
char	*ft_test_paths(char **splitted_cmd, char **paths);
char	**append_backslash(char **paths);

#endif
