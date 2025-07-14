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
		close(pip[1]);
		exit(0);  // Important: child should exit -- whhy?
	}
	else
	{
		close(pip[1]);
		wait(NULL); // other person used waitpid
		dup2(pip[0], STDIN_FILENO);
		close(pip[0]); // why ??? 
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