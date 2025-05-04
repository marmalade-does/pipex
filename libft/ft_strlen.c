#include "libft.h"
#include <stdio.h>

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/*
void main()
{
	char *str = "This is a string"; 
	int len = strlen(str);
	printf("h%i", len);
	return;
}
*/