#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s)
		return (NULL);
	if (start >= (unsigned int)ft_strlen(s))
		return (ft_strdup(""));
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	i = start;
	j = 0;
	while (s[i] && j < len)
	{
		str[j] = s[i];
		j++;
		i++;
	}
	str[j] = '\0';
	return (str);
}
