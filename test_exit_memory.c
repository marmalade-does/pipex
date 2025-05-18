

#include <stdlib.h>
#include <stdio.h>

int main()
{
	// Allocate memory
	void *memory = malloc(1024); // Allocating 1024 bytes

	if (memory == NULL) {
		printf("Memory allocation failed\n");
		exit(1);
	}

	// Exit the program
	exit(0);
}