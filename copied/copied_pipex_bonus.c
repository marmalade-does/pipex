
#include "pipex.h"


// His silly code uses a child process in the here_doc file, however this ins't needed.


void	child_process(char *argv, char **envp);
void	here_doc(char *limiter, int argc);

//-- main
// checks if there is at least 5 args
// checks if this is a here_doc assignment
// does all the intermediate command executions (does the open std file stuff if not here_doc)
// does the final command execution 

// -- child_process
// creates child process to do the ft_execute command
// make sure you get the pipes right

// -- ft_execute command
// 


/* Main function that run the childs process with the right file descriptor
 or display an error message if arguments are wrong. It will run here_doc
 function if the "here_doc" string is find in argv[1] */
int	main(int argc, char **argv, char **envp)
{
	int	i;
	int	filein;
	int	fileout;

	if (argc < 5)
		usage();
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		i = 3;
		fileout = open(argv[1], O_WRONLY | O_CREAT | O_APPEND, 0777);
		here_doc(argv[2], argc);
	}
	else
	{
		i = 2;
		fileout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		filein = open(argv[1], O_RDONLY);
		dup2(filein, STDIN_FILENO);
	}
	while (i < argc - 2)
		child_process(argv[i++], envp); // you are allowed to this ugly looping over the child process because pipe(fd[2]) connections are global(!!) 
	dup2(fileout, STDOUT_FILENO);
	execute(argv[argc - 2], envp);
}

/* Child process that create a fork and a pipe, put the output inside a pipe
 and then close with the exec function. The main process will change his stdin
 for the pipe file descriptor. */
 void	child_process(char *argv, char **envp)
 {
	 pid_t	pid;
	 int		fd[2];
 
	 if (pipe(fd) == -1)
		 error();
	 pid = fork();
	 if (pid == -1)
		 error();
	 if (pid == 0)
	 {
		 close(fd[0]);
		 dup2(fd[1], STDOUT_FILENO);
		 execute(argv, envp);
	 }
	 else
	 {
		 close(fd[1]);
		 dup2(fd[0], STDIN_FILENO);
		 waitpid(pid, NULL, 0);
	 }
 }
 
/* Function who make a child process that will read from the stdin with
get_next_line until it find the limiter word and then put the output inside a
pipe. The main process will change his stdin for the pipe file descriptor. */
void	here_doc(char *limiter, int argc)
{
	pid_t	reader;
	int		fd[2];
	char	*line;

	if (argc < 6)
		usage();
	if (pipe(fd) == -1)
		error();
	reader = fork();
	if (reader == 0)
	{
		close(fd[0]);
		while (get_next_line(&line))
		{
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
				exit(EXIT_SUCCESS);
			write(fd[1], line, ft_strlen(line));
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
}
 
/* Function that will read input from the terminal and return line. */
int	get_next_line(char **line)
{
	char	*buffer;
	int		i;
	int		r;
	char	c;

	i = 0;
	r = 0;
	buffer = (char *)malloc(10000);
	if (!buffer)
		return (-1);
	r = read(0, &c, 1);
	while (r && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		r = read(0, &c, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	free(buffer);
	return (r);
}
