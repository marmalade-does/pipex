/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroberts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:24:27 by lroberts          #+#    #+#             */
/*   Updated: 2025/05/18 21:57:42 by lroberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// change the name of the ft_child and the ft_execute function
// to whatever the other person didn't have on github

#include "pipex.h"
#include <limits.h>

int	main(int argc, char *argv[], char **envp)
{
	int		infile;
	int		outfile;
	size_t	i;

	if (argc < 5)
		ft_fail("Usage, need at least two commands: ./pipex file1 cmd1 cmd2 ... cmdn file2");
	if ((ft_strncmp(argv[1], "here_doc", 8)))
	{
		if (argc < 6)
			ft_fail("Usage: ./pipex here_doc LIMITER cmd1 cmd2 ... cmdn file2");
		i = 3;
		outfile = open(argv[argc - 2], O_WRONLY | O_APPEND | O_CREAT);
		if (outfile <= 0)
			ft_fail("Error opening file - main");
		ft_here_we_are(argv[2]); // pass the delimiter
	}
	else
	{
		i = 2;
		infile = open(argv[2], O_RDONLY);
		outfile = open(argv[argc - 2], O_WRONLY | O_TRUNC | O_CREAT);
		if (infile <= 0 || outfile <= 0)
			ft_fail("Error opening file - main");
		if (dup2(infile, STDIN_FILENO) < 0)
			ft_fail("Error redirecting input - main");
	}
	while(i < argc - 2) // yes because we want too NOT execute the last function
		children(argv[i++], envp);
	if((dup2(outfile, STDOUT_FILENO)) < 0)
		ft_fail("Error redirecting output");
	wrapped_execve(argv[i], envp);
	ft_fail("Error executing command");
}
void children(char *arg, char **envp)
{
	int pip[2];
	pid_t pid;

	if (pipe(pip) == -1)
		ft_fail("Error creating pipe");
	pid = fork();
	if (pid == -1)
		ft_fail("Error creating fork");
	if (pid == 0)
	{
		close(pip[0]);
		dup2(pip[1], STDOUT_FILENO);
		wrapped_execve(arg, envp);
		ft_error("execve failed -- CHILDREN");
	}
	else
	{
		close(pip[1]);
		dup2(pip[0], STDIN_FILENO);
		wait(NULL);
		// no free needed here since the child process is the one that alocates the strs
	}
}

void wrapped_execve(char *arg, char **envp)
{
	char	**splited;
	char	*path;
	size_t	i;

	splited = ft_split(arg);
	if (splited == NULL)
		ft_fail("ft_split failed - wrapped execve");
	path = get_path(splited, envp); /// check if this is NULL
		ft_fail("get_path failed - wrapped execve"); // this isn't an if, dhuy!






	execve(path, splited, envp);
	while(splited[i])
		free(splited[i++]);
	free(splited);
	free(path);
	ft_fail("execve failed");
}

void ft_here_we_are(char *delimeter)
{
	int		pip[2];
	pid_t	pid;
	char	*line;

	if(pipe(pip) < 0)
		ft_fail("Error creating pipe - ft_here_doc");
	if((pid = fork()) < 0)
		ft_fail("Error creating fork - ft_here_doc");
	if (pid == 0)
	{
		close(pip[0]);
		while(get_next_line(&line)) // don't need to worry if returns NULL becuase is dealt with in called function
		{
			if(ft_strncmp(line, delimeter, ft_strlen(delimeter)) == 0)
				break ; // the other person used exit(EXIT_SUCCESS) -> this also works, but just in case
			write(pip[1], line, ft_strlen(line));
			free(line);
		}
	}
	else
	{
		close(pip[1]);
		wait(NULL); // other person used waitpid
		dup2(pip[0], STDIN_FILENO);
	}
}

int get_next_line(char **line)
{
	int		red;
	size_t	i;
	char	*buf;
	char	c;

	buf = (char *)malloc(2147483647);
	if (buf == NULL)
		ft_fail("malloc failed - get_next_line");  // he returns a -1 allowing the parent child process to just go till completion and end
	red = 1;
	c = 0;
	i = 0; // bruh tantas lineas :(
	while (red > 0 && c != '\n')
	{
		red = read(0, &c, 1);
		if (c != '\n')
			buf[i] = c;
		i++;
	}
	if (red == -1)
		return (free(buf), ft_fail("read failed - get_next_line"), -1); // this might give erorrs later
	buf[i - 1] = '\n';
	buf[i] = '\0';
	*line = buf;
	return (red);
}
