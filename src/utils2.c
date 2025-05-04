#include "../includes/pipex.h"

void	pip_write(char *name, int fd_in, int hd)
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
		perror("error opening / final pipe -- loser  :p");
		exit(66); // This is probably wrong, need to check freeing memory and fd and stuff.
	}
	// Read from fd_in and write to fd_out
	red = 1;
	while ((red = read(fd_in, buffer, BUFFER_SIZE)) > 0)
	{
		if(write(fd_out, buffer, red) < 0)
		{
			perror("write() failed on your ass >:) ");
			exit(29383);
		}
	}
	if(red < 0)
	{
		perror("read() failed on your ass >:) ");
		exit(239);
	}
}


