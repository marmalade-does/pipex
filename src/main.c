#include "../includes/pipex.h"

void child_exec_bash(char **cmd, char **envp, int **pip1, int **pip2, int i);
void ft_initialise_pipe(int (*pip1)[2], int (*pip2)[2]);
void ft_open_first_file(char *argv, int **pip1);

int main(int argc, char *argv[], char **envp)
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





void ft_write_pipes(char *file_output, int **pip1, int **pip2, int cmd_count)
{
	if (cmd_count % 2 == 0)
		ft_hack_write(file_output, pip2);
	else
		ft_hack_write(file_output, pip1);
}
ft_hack_write(char *file_output, int **pip)
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

	if((fd = open(argv, O_RDONLY)) < 0)
	{	
		perror("open first file failed");
		exit(99); // I think I need to close all the file descriptors first.
	}
	(*pip1)[1] = fd;
}

void ft_initialise_pipe(int (*pip1)[2], int (*pip2)[2])
{
	if(pipe((*pip1)) < 0 || pipe((*pip2)) < 0)
	{
		perror("something wrong with pipe initialisation");
		exit(9889); // can eleav easily since no fd are mad and no memory is allocated.
	} 
}


