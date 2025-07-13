
#include "./includes/libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int pipex_rd_nxt_line(char **line);


void	ft_fail(char *errmsg, int fail_num)
{
	perror(errmsg);
	exit(fail_num);
}


int main(void)
{
	char *line;
	char *delimeter = "STOP"; // Example delimiter, change as needed

	while (pipex_rd_nxt_line(&line) > 0)
	{
		printf("Read line: %s", line);
		if (strncmp(line, delimeter, strlen(delimeter)) == 0)
		{
			free(line);
			break;
		}
		free(line);
	}
	return (0);
}


