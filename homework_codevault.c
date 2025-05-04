
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <a.out.h>


int main (int argc, char **argv)
{
	int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int fd1[2];
	int fd2[2];
	pid_t pid1, pid2;
	int sum1 = 0, sum2 = 0, total_sum = 0;

	if (pipe(fd1) == -1 || pipe(fd2) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	pid1 = fork();
	if (pid1 == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (pid1 == 0) {
		// First child process
		close(fd1[0]); // Close unused read end
		for (int i = 0; i < 5; i++) {
			sum1 += arr[i];
		}
		write(fd1[1], &sum1, sizeof(sum1));
		close(fd1[1]); // Close write end after writing
		exit(EXIT_SUCCESS);
	} else {
		pid2 = fork();
		if (pid2 == -1) {
			perror("fork");
			exit(EXIT_FAILURE);
		}

		if (pid2 == 0) {
			// Second child process
			close(fd2[0]); // Close unused read end
			for (int i = 5; i < 10; i++) {
				sum2 += arr[i];
			}
			write(fd2[1], &sum2, sizeof(sum2));
			close(fd2[1]); // Close write end after writing
			exit(EXIT_SUCCESS);
		} else {
			// Parent process
			close(fd1[1]); // Close unused write end
			close(fd2[1]); // Close unused write end

			read(fd1[0], &sum1, sizeof(sum1));
			read(fd2[0], &sum2, sizeof(sum2));

			close(fd1[0]); // Close read end after reading
			close(fd2[0]); // Close read end after reading

			total_sum = sum1 + sum2;
			printf("Total sum: %d\n", total_sum);

			// Wait for child processes to finish
			wait(NULL);
			wait(NULL);
		}
	}


}



