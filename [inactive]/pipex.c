/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroberts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:24:27 by lroberts          #+#    #+#             */
/*   Updated: 2025/07/15 18:56:22 by lroberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

static void	handle_here_doc(int argc, char **argv, int *i, int *outfile);
static void	handle_regular_mode(int argc, char **argv, int *i, int *outfile);

int	main(int argc, char *argv[], char **envp)
{
	int	outfile;
	int	i;

	if (argc < 5)
		ft_fail("Usage: ./pipex file1 cmd1 cmd2 ... cmdn file2", 6);
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

static void	handle_here_doc(int argc, char **argv, int *i, int *outfile)
{
	if (argc < 6)
		ft_fail("Usage: ./pipex here_doc LIMITER cmd1 cmd2 ... cmdn file2", 7);
	*i = 3;
	*outfile = open(argv[argc - 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (*outfile <= 0)
		ft_fail("Error opening file - main", 8);
	ft_here_we_are(argv[2]);
}

static void	handle_regular_mode(int argc, char **argv, int *i, int *outfile)
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
	size_t i;

	splited = ft_split(arg, ' ');
	if (splited == NULL)
		ft_fail("ft_split failed - wrapped execve", 16);
	i = -1;
	while(splited[0][++i] != '.' && i < 2)
	if(splited[0][i] == '/')
		execve(splited[0], splited, envp);
	else
		path = get_path(splited, envp);
	if (path == NULL)
	{
		free_dbl_ptrs(splited, NULL, NULL);
		ft_fail("get_path failed - wrapped execve", 17);
	}
	execve(path, splited, envp);
	free_dbl_ptrs(splited, NULL);
	free(path);
	ft_fail("execve failed for some reason", errno);
}

/*
static void	ft_printing_splited(char **splited)
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