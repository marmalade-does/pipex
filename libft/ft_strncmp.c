
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n > 0 && *s1 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

/*
void main()
{
	char *s1 = "This is srting A slfhosiboilndfisdfxiosdkfmx";
	char *s2 = "This is string B   lalala";

	int dif = ft_strncmp(s1, s2, 16);
	prtinf("%i", dif);
	return;
}
*/
