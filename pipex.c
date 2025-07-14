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

#include "./pipex.h"





void	handle_here_doc(int argc, char **argv, int *i, int *outfile)
{
	if (argc < 6)
		ft_fail("Usage: ./pipex here_doc LIMITER cmd1 cmd2 ... cmdn file2", 7);
	*i = 3;
	*outfile = open(argv[argc - 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (*outfile <= 0)
		ft_fail("Error opening file - main", 8);
	ft_here_we_are(argv[2]);
}

void	handle_regular_mode(int argc, char **argv, int *i, int *outfile)
{
	int	infile;

	*i = 2;
	infile = open(argv[1], O_RDONLY);
	if (infile < 0)
		ft_fail("Error opening input file\n", 9);
	*outfile = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (*outfile < 0)
		ft_fail("Error opening output file\n", 10);
	if (dup2(infile, STDIN_FILENO) < 0)
		ft_fail("Error redirecting input - main\n", 11);
}

int	main(int argc, char *argv[], char **envp)
{
	int	outfile;
	int	i;

	if (argc < 5)
		ft_fail("Usage, need at least two commands: ./pipex file1 cmd1 cmd2 ... cmdn file2", 6);	
	if (!(ft_strncmp(argv[1], "here_doc", 8)))
		handle_here_doc(argc, argv, &i, &outfile);
	else
	{
		handle_regular_mode(argc, argv, &i, &outfile);
	}
	while (i < argc - 2)
	{
		children(argv[i], envp);
		i++;
	}
	if (dup2(outfile, STDOUT_FILENO) < 0)
		ft_fail("Error redirecting output", 11);
	wrapped_execve(argv[i], envp);
	ft_fail("Error executing command", 12);
}


void	children(char *arg, char **envp)
{
	int		pip[2];
	pid_t	pid;

	if (pipe(pip) == -1)
		ft_fail("Error creating pipe", 13);
	pid = fork();
	if (pid == -1)
		ft_fail("Error creating fork", 14);
	if (pid == 0)
	{
		close(pip[0]);
		dup2(pip[1], STDOUT_FILENO);
		wrapped_execve(arg, envp);
		ft_fail("execve failed -- CHILDREN", 17);
	}
	else
	{
		close(pip[1]);
		dup2(pip[0], STDIN_FILENO);
		wait(NULL);
	}
}
void	wrapped_execve(char *arg, char **envp)
{
	char	**splited;
	char	*path;

	splited = ft_split(arg, ' '); 
	if (splited == NULL)
	{
		//write(2, "checkpoint - entered splitted", 29); // remove
		ft_fail("ft_split failed - wrapped execve", 16); 
	}
	path = get_path(splited, envp);
	//write(2, "checkpoint: left get_path\n", 26);
	if (path == NULL) /// check if this is NULL
	{
		//write(2, "the path variable == NULL\n", 26); // remove this later
		free_dbl_ptrs(splited, NULL, NULL);
		ft_fail("get_path failed - wrapped execve", 17);
	}
	execve(path, splited, envp);
	free_dbl_ptrs(splited, NULL);
	free(path);
	ft_fail("execve failed for some reason", errno);
}

int	ft_here_we_are(char *delimeter)
{
	int		pip[2];
	pid_t	pid;
	char	*line;

	if (pipe(pip) < 0)
		ft_fail("Error creating pipe - ft_here_doc", 19);
	if ((pid = fork()) < 0)
		ft_fail("Error creating fork - ft_here_doc", 20);
	if (pid == 0)
	{
		close(pip[0]);
		while (pipex_rd_nxt_line(&line))
		{
			if (ft_strncmp(line, delimeter, ft_strlen(delimeter)) == 0 && 
				line[ft_strlen(delimeter)] == '\0')
			{
				free(line);
				break;
			}
			write(pip[1], line, ft_strlen(line));
			write(pip[1], "\n", 1);  // Add back the newline for the pipe
			free(line);
		}
		return (close(pip[1]), exit(0), 0);  // Important: child should exit -- whhy?
	}
	else
		return (close(pip[1]), wait(NULL), dup2(pip[0], STDIN_FILENO), close(pip[0]), 0);
	// why ??? 
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
	while(red > 0 && c != '\n')
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
	buf[i] = '\0';  // Simple null termination
	*line = buf;
	return (red);
}

/*
static void ft_printing_splited(char **splited)
{
	size_t i= 0;
	write(2, "\n", 1);
	while(splited[i] != NULL)
	{
		write(2, splited[i], ft_strlen(splited[i]));
		write(2, "\n", 1);
		i++;
	}
	write(2, "got to the end\n", 15);
}

*/