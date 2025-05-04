#include "../includes/pipex.h"

void child_exec_bash(char **cmd, char **envp, int **pip1, int **pip2, int i);
void ft_initialise_pipe(int (*pip1)[2], int (*pip2)[2]);
void ft_open_first_file(char *argv, int **pip1);



/* ### 1. Program Initialization
- Parse command line arguments
- Determine if it's a regular mode or here_doc mode
- Validate argument count (at least 5 for regular mode, at least 6 for here_doc)
 */
main(int argc, char *argv[], char **envp)
{
    int pip1[2];
	int pip2[2];
	char **split;
	int i;

	ft_initialise_pipe(&pip2, &pip1);
	ft_open_first_file(argv[1], &pip1);
	i = 2; // [0] is command; [1] is the file name
	while(i < argc - 1) // becuase the last one is the output file
	{
		split = ft_split(argv[i]);
		child_exec_bash(split, envp, &pip1, &pip2, i); // using i here isn't correct
		i++;
	} 
	// Execute "ping -c 5 google.com" and redirect output to the pipe
	// ft_exec_bash(argv[0], &fd, argv, envp);
	// Execute "grep rtt" and redirect input from the pipe
	// ft_exec_bash(fd[0], STDOUT_FILENO, "grep", "rtt", NULL);

	ft_write_pipes(argv[argc - 1], &pip1, &pip2, i - 2); // i-1 is the number of arguments that we executed. 
	ft_close_all_pipes(&pip1, &pip2);

    // Wait for all child processes to finish
    while(i > 2)
	{
		wait(NULL);
		i--;
	}
    return (0);
}

/**
 * @brief Executes a command in a child process with input/output redirection.
 * 
 * @param cmd The command to execute (array of strings).
 * @param envp The environment variables.
 * @param pip1 Pointer to the first pipe.
 * @param pip2 Pointer to the second pipe.
 * @param i The index of the current command.
 */
void child_exec_bash(char **cmd, char **envp, int **pip1, int **pip2, int i)
{
	pid_t pid;
	int *input_pipe;
	int *output_pipe;

	if(i % 2 == 0)
	{
		input_pipe = *pip1;
		output_pipe = *pip2;
	}
	else
	{
		input_pipe = *pip2;
		output_pipe = *pip1;
	}
	pid = fork();
	if (pid < 0)
	{
		perror("error with fork");
		exit(66);
	}
	if (pid == 0)
	{
		close(input_pipe[1]); // Close the write end of the input pipe
		close(output_pipe[0]); // Close the read end of the output pipe

		if (dup2(input_pipe[0], STDIN_FILENO) == -1 || dup2(output_pipe[1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		
		execve(cmd[0], cmd, envp);
		perror("execve failed");
		exit(33);
	}
	close(input_pipe[0]); // Close the read end of the input pipe in the parent
	close(output_pipe[1]); // Close the write end of the output pipe in the parent
}


/**
 * @brief Writes the final output from the last pipe to the output file.
 * 
 * @param file_output The name of the output file.
 * @param pip1 Pointer to the first pipe.
 * @param pip2 Pointer to the second pipe.
 * @param cmd_count The number of commands executed.
 */
void ft_write_pipes(char *file_output, int **pip1, int **pip2, int cmd_count)
{
	if (cmd_count % 2 == 0)
		ft_hack_write(file_output, pip2);
	else
		ft_hack_write(file_output, pip1);
}


/**
 * @brief Writes data from a pipe to the output file.
 * 
 * @param file_output The name of the output file.
 * @param pip Pointer to the pipe.
 */
void ft_hack_write(char *file_output, int **pip)
{
    int fd;
    char buffer[1024];
    ssize_t bytes_read;

    fd = open(file_output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror("open output file failed");
        exit(1);
    }

    close((*pip)[1]); // Close the write end of the pipe
    while ((bytes_read = read((*pip)[0], buffer, sizeof(buffer))) > 0)
    {
        if (write(fd, buffer, bytes_read) != bytes_read)
        {
            perror("write to output file failed");
            close(fd);
            exit(1);
        }
    }

    if (bytes_read < 0)
    {
        perror("read from pipe failed");
    }

    close(fd);
    close((*pip)[0]); // Close the read end of the pipe
}

/**
 * @brief Closes all pipes to release resources.
 * 
 * @param pip1 Pointer to the first pipe.
 * @param pip2 Pointer to the second pipe.
 */
void ft_close_all_pipes(int **pip1, int **pip2)
{
	close((*pip1)[0]);
    close((*pip1)[1]);
    close((*pip2)[0]);
    close((*pip2)[1]);
	return ;

}

void ft_open_first_file(char *argv, int **pip1)
{
    int fd;

    fd = open(argv, O_RDONLY);
    if (fd < 0)
    {
        perror("open first file failed");
        exit(99);
    }
    if (dup2(fd, (*pip1)[0]) == -1) // Redirect file to pipe's read end
    {
        perror("dup2 failed");
        exit(99);
    }
    close(fd);
}


/**
 * @brief Initializes two pipes for inter-process communication.
 * 
 * @param pip1 Pointer to the first pipe.
 * @param pip2 Pointer to the second pipe.
 */
void ft_initialise_pipe(int (*pip1)[2], int (*pip2)[2])
{
	if(pipe((*pip1)) < 0 || pipe((*pip2)) < 0)
	{
		perror("something wrong with pipe initialisation");
		exit(9889); // can eleav easily since no fd are mad and no memory is allocated.
	} 
}


