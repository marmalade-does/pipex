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

#include "./pipex.h"

int	main(int argc, char *argv[], char **envp)
{
	int	infile;
	int	outfile;
	int	i;

	int checkpoint;
	checkpoint = open("checkpoint.txt", O_WRONLY | O_CREAT,  0644);
	write(checkpoint, "checkpoint 0\n", 13);
	if (argc < 5)
		ft_fail("Usage, \
			need at least two commands: ./pipex file1 cmd1 cmd2 ... cmdn file2",
				6);
	write(checkpoint, "checkpoint 1\n", 13);
	if (!(ft_strncmp(argv[1], "here_doc", 8)))
	{
		// ft_fail("entered the here_doc mode", 87); -- this needs to be removed later -- was used for testing
		if (argc < 6)
			ft_fail("Usage: ./pipex here_doc LIMITER cmd1 cmd2 ... cmdn file2",
				7);
		i = 3;
		outfile = open(argv[argc - 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (outfile <= 0)
			ft_fail("Error opening file - main", 8);
		ft_here_we_are(argv[2]); // pass the delimiter
	}
	else
	{
		write(checkpoint, "checkpoint 2\n", 13);
		i = 2;
		infile = open(argv[1], O_RDONLY);
		if (infile < 0)
			ft_fail("Error opening input file\n", 9);
		outfile = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (outfile < 0)
			ft_fail("Error opening output file\n", 10);
		//if (infile <= 0 || outfile <= 0)
		//	ft_fail("Error opening file - main\n", 9); // comment out the specific ft_fails when you done.
		if (dup2(infile, STDIN_FILENO) < 0)
			ft_fail("Error redirecting input - main\n", 11);
	}
	write(checkpoint, "checkpoint 3\n", 13);
	while (i < argc - 2)
	{ // yes because we want too NOT execute the last function
		children(argv[i], envp);
		i++;
	}
	if ((dup2(outfile, STDOUT_FILENO)) < 0)
		ft_fail("Error redirecting output", 11);
	wrapped_execve(argv[i], envp);
	ft_fail("Error executing command", 12); // use of dup2() here is correct
}
void	children(char *arg, char **envp)
{
	int		pip[2];
	pid_t	pid;

	//write(2, "checkpoint 4\n", 13);
	if (pipe(pip) == -1)
		ft_fail("Error creating pipe", 13);
	pid = fork();
	//write(2, "checkpoint 4 - double\n", 22);
	if (pid == -1)
		ft_fail("Error creating fork", 14);
	if (pid == 0)
	{
		//write(2, "checkpoint c-6\n", 15);
		close(pip[0]);
		//write(2, "checkpoint c-7\n", 15);
		dup2(pip[1], STDOUT_FILENO); // this line causes a segfault (core dumped)
		//write(2, "checkpoint c-8\n", 15);
		wrapped_execve(arg, envp);
		//write(2, "checkpoint c-9\n", 15);
		ft_fail("execve failed -- CHILDREN", 15);
		//write(2, "checkpoint c-10\n", 15);
	}
	else
	{
		//write(2, "checkpoint p-6\n", 15);		
		close(pip[1]);
		//write(2, "checkpoint p-7\n", 15);
		// close(STDOUT_FILENO);
		//write(2, "checkpoint p-8\n", 15);
		// this closes the unused fd to avoid too many fd's
		dup2(pip[0], STDIN_FILENO);
		//write(2, "checkpoint p-9\n", 15);
		wait(NULL);
		//write(2, "checkpoint p-10\n", 16);
		// no free needed here since the child process is the one that alocates the strs
	}
}

void ft_printing_splited(char **splited)
{
	size_t i= 0;
	while(splited[i] != NULL)
	{
		//write(2, splited[i], ft_strlen(splited[i]));
		//write(2, "\n", 1);
		i++;
	}
	//write(2, "got to the end\n", 15);
}

void	wrapped_execve(char *arg, char **envp)
{
	char	**splited;
	char	*path;

	splited = ft_split(arg, ' '); 
	//write(2, "checkpoint 5\n", 13);
	if (splited == NULL)
	{
		//write(2, "checkpoint - entered splitted", 29); // remove
		ft_fail("ft_split failed - wrapped execve", 16); 
	}
	path = get_path(splited, envp);
	//write(2, "checkpoint: left get_path\n", 26);
	if (path == NULL) /// check if this is NULL
	{
		write(2, "the path variable == NULL\n", 26); // remove this later
		free_dbl_ptrs(splited, NULL, NULL);
		ft_fail("get_path failed - wrapped execve", 17);
	}
	execve(path, splited, envp);

	////////////////////////////////////////////////////////////////////////////////////////
	// If we get here, execve failed - check errno
    if (errno == ENOENT)
        write(2, "execve failed: No such file or directory\n", 41);
    else if (errno == EACCES)
        write(2, "execve failed: Permission denied\n", 33);
    else if (errno == ENOEXEC)
        write(2, "execve failed: Exec format error\n", 33);
    else
    {
        //write(2, "execve failed with errno: ", 26);
        ft_putnbr_fd(errno, 2);
        //write(2, "\n", 1);
    }
    
    // Also use perror for more detail
    perror("execve");
	// remove the above later //////////////////////////////////////////////////////////////



	//free_dbl_ptrs(splited, NULL, NULL);// - so the splitted is bad? 
	free(path); // need to remove this later
	ft_fail("execve failed", 18);
}




void	ft_here_we_are(char *delimeter)
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
		// don't need to worry if returns NULL becuase is dealt with in called function
		{
			if (ft_strncmp(line, delimeter, ft_strlen(delimeter)) == 0)
				break ; // og uses(EXIT_SUCCESS)->this also works but JIC
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
		if (c != '\n')
			buf[i] = c;
		i++;
	}
	if (red == -1)
		return (free(buf), ft_fail("read failed - pipex_rd_nxt_line", 22), -1);
	// this might give erorrs later
	buf[i - 1] = '\n';
	buf[i] = '\0';
	*line = buf;
	return (red);
}
