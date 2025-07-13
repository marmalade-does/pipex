#include "../includes/pipex.h"

/**
 * @brief Reads data from an input file descriptor and writes it to an output file.
 * 
 * This function reads data from the input file descriptor `fd_in` and writes it
 * to the output file specified by `name`. If the file already exists, it is
 * truncated. The function handles errors during file operations and exits
 * with an appropriate error code if an error occurs.
 * 
 * @param name The name of the output file.
 * @param fd_in The input file descriptor to read from.
 * @param hd Unused parameter (reserved for future use).
 */
void pip_write(char *name, int fd_in, int hd)
{
    int		fd_out;
    int		red;
    char	buffer[BUFFER_SIZE + 1];

    buffer[BUFFER_SIZE] = '\0';
    // Open the output file in append or write mode
    unlink(name);
    fd_out = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    // Error handling for file descriptors
    if (fd_out < 0 || fd_in < 0)
    {
        perror("error opening / final pipe -- loser >:( ");
        exit(66); // This is probably wrong, need to check freeing memory and fd and stuff.
    }
    // Read from fd_in and write to fd_out
    red = 1;
    while ((red = read(fd_in, buffer, BUFFER_SIZE)) > 0)
    {
        if (write(fd_out, buffer, red) < 0)
        {
            perror("write() failed on your ass");
            exit(29383);
        }
    }
    if (red < 0)
    {
        perror("read() failed");
        exit(239);
    }
}


