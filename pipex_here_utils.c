/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_here_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroberts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:19:34 by lroberts          #+#    #+#             */
/*   Updated: 2025/07/15 16:17:46 by lroberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_dbl_ptrs(char **first, ...)
{
	va_list	args;
	char	**ptr;
	size_t	i;

	if (first)
	{
		i = 0;
		while (first[i])
			free(first[i++]);
		free(first);
	}
	va_start(args, first);
	ptr = va_arg(args, char **);
	while (ptr != NULL)
	{
		i = 0;
		while (ptr[i])
			free(ptr[i++]);
		free(ptr);
		ptr = va_arg(args, char **);
	}
	va_end(args);
}

void	ft_fail(char *errmsg, int fail_num)
{
	perror(errmsg);
	exit(fail_num);
}

static void	ft_child_here_we_are(char *delimeter, int *pip)
{
	char	*line;

	close(pip[0]); // Child doesn't read from pipe
	while (pipex_rd_nxt_line(&line))
	{
		if (ft_strncmp(line, delimeter, ft_strlen(delimeter)) == 0)
		{
			if (line[ft_strlen(delimeter)] == '\0')
			{
				free(line);
				break ;
			}
		}
		if (write(pip[1], line, ft_strlen(line)) == -1 || write(pip[1], "\n",
				1) == -1)
		{
			free(line);
			close(pip[1]);
			exit(1);
		}
		free(line);
	}
	close(pip[1]);
	exit(0);
}

void	ft_here_we_are(char *delimeter)
{
	int		pip[2];
	pid_t	pid;

	if (pipe(pip) < 0)
		ft_fail("Error creating pipe - ft_here_doc", 19);
	pid = fork();
	if (pid < 0)
		ft_fail("Error creating fork - ft_here_doc", 20);
	if (pid == 0)
	{
		close(pip[0]);
		ft_child_here_we_are(delimeter, pip);
	}
	// no else statment needed for the parent function since the child exits
	close(pip[1]);
	wait(NULL);
	dup2(pip[0], STDIN_FILENO);
	close(pip[0]); // why have the close of the pipes? I don't get it
}

int	pipex_rd_nxt_line(char **line)
{
	int		red;
	size_t	i;
	char	*buf;
	char	c;

	buf = (char *)malloc(1024);
	if (buf == NULL) // og returns -1->allows parent process to continue
		ft_fail("malloc failed - pipex_rd_nxt_line", 21);
	red = 1;
	c = 0;
	i = 0; // bruh tantas lineas :(
	while (red > 0 && c != '\n')
	{
		red = read(0, &c, 1);
		if (red > 0 && c != '\n')
		{
			buf[i] = c;
			i++;
		}
	}
	if (red == -1)
		return (free(buf), ft_fail("read failed - pipex_rd_nxt_line", 22), -1);
	buf[i] = '\0'; // Simple null termination
	*line = buf;
	return (red);
}
