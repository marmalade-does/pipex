#include "pipex_copied.h"

void	child_process_1(char **argv, char **envp, int *fd);
void	child_process_2(char **argv, char **envp, int *fd);

/* Main function that runs two child processes or displays an error
   message if arguments are wrong */
int	main(int argc, char **argv, char **envp)
{
    int		fd[2];
    pid_t	pid1, pid2;

    if (argc == 5)
    {
        if (pipe(fd) == -1) // Create a pipe
            error();
        
        // First child process
        pid1 = fork();
        if (pid1 == -1)
            error();
        if (pid1 == 0)
            child_process_1(argv, envp, fd); // Execute the first command

        // Second child process
        pid2 = fork();
        if (pid2 == -1)
            error();
        if (pid2 == 0)
            child_process_2(argv, envp, fd); // Execute the second command

        // Parent process waits for both child processes to finish
        close(fd[0]);
        close(fd[1]);
        waitpid(pid1, NULL, 0);
        waitpid(pid2, NULL, 0);
    }
    else
    {
        ft_putstr_fd("\033[31mError: Bad arguments\n\e[0m", 2);
        ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
    }
    return (0);
}

/* First child process: takes the input file, writes output to the pipe */
void	child_process_1(char **argv, char **envp, int *fd)
{
    int		filein;

    filein = open(argv[1], O_RDONLY);
    if (filein == -1)
        error();
    dup2(fd[1], STDOUT_FILENO); // Redirect stdout to the write end of the pipe
    dup2(filein, STDIN_FILENO); // Redirect stdin to the input file
	close(fd[0]); // Close the read end of the pipe
    execute(argv[2], envp); // Execute the first command
}

/* Second child process: takes input from the pipe, writes output to the output file */
void	child_process_2(char **argv, char **envp, int *fd)
{
    int		fileout;

    fileout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (fileout == -1)
        error();
    dup2(fd[0], STDIN_FILENO); // Redirect stdin to the read end of the pipe
    dup2(fileout, STDOUT_FILENO); // Redirect stdout to the output file
    close(fd[1]); // Close the write end of the pipe
    execute(argv[3], envp); // Execute the second command
}
