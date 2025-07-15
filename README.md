# pipex
pipex project for 42

next to do
* then get a pipex tester online and profit

Next

Things to ask people as 42 before handing in: 
* the buffer size in the pipex_rd_nxt_lne()
-- I put as 9999, however IDK if that is good, i put as INT_MAX earlier, however chat said it would fail. 
* Makefile good ? (both the root/tpipex  Makefile and the includes/libft makefile) and how you did the touch Makeefile thing? 
Before hanading in 
* remove the comments in ur functions
* remove the -fsanatize flag in the makefile
* make sure that the whole thing recompiles if the Makefile file is touched


Later:
* think about integrating the gnl function in your libft --> (just so that you can move the librairy w/ everything in the future)





int	main(int argc, char *argv[], char **envp)
{
	int	infile;
	int	outfile;
	int	i;

	if (argc < 5)
		ft_fail("Usage, \
			need at least two commands: ./pipex file1 cmd1 cmd2 ... cmdn file2",
				6);
	if (!(ft_strncmp(argv[1], "here_doc", 8)))
	{
		if (argc < 6)
			ft_fail("Usage: ./pipex here_doc LIMITER cmd1 cmd2 ... cmdn file2",
				7);
		i = 3;
		outfile = open(argv[argc - 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (outfile <= 0)
			ft_fail("Error opening file - main", 8);
		ft_here_we_are(argv[2]);
	}
	else
	{
		i = 2;
		infile = open(argv[1], O_RDONLY);
		if (infile < 0)			ft_fail("Error opening input file\n", 9);
		outfile = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (outfile < 0)
			ft_fail("Error opening output file\n", 10);
		if (dup2(infile, STDIN_FILENO) < 0)
			ft_fail("Error redirecting input - main\n", 11);
	}
	while (i < argc - 2)
	{
		children(argv[i], envp);
		i++;
	}
	if ((dup2(outfile, STDOUT_FILENO)) < 0)
		ft_fail("Error redirecting output", 11);
	wrapped_execve(argv[i], envp);
	ft_fail("Error executing command", 12); // use of dup2() here is correct
}



