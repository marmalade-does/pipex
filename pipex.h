#ifndef PIPEX_H
# define PIPEX_H
// fix this later
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>


// pipex.c
void	get_next_line(char **line);
void	ft_here_doc(char *file, char *delimeter);
void	ft_child(char *arg, char **envp);
void	ft_fail(char *errmsg);
int get_next_line(char **line);

// pipex_utils.c
char	*get_path(char *cmd, char **envp);
char	*ft_test_paths(char *cmd, char **paths);
char	**ft_merge_paths(char **paths_base, char **paths_tmp);
void	ft_fail(char *errmsg);
void free_x3_dbl_ptr(char **ptr2x_a, char **ptr2x_b, char **ptr2x_c);

#endif
