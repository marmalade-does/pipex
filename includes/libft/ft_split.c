/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroberts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 09:57:29 by lroberts          #+#    #+#             */
/*   Updated: 2025/01/03 09:57:32 by lroberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <unistd.h>

static size_t	word_len(const char *str, char delim);
static size_t	count_words(const char *str, char delim);

char	**ft_split(char const *str, char delim)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	**mat;

	i = 0;
	k = 0;
	mat = (char **)malloc(sizeof(char *) * (count_words(str, delim) + 1));
	if (!str || !(mat))
		return (NULL);
	while (i < count_words(str, delim))
	{
		while (str[k] == delim)
			k++;
		mat[i] = (char *)malloc(sizeof(char) * (word_len(&str[k], delim) + 1));
		if (!(mat[i]))
			return (NULL);
		j = 0;
		while (str[k] != delim && str[k])
			mat[i][j++] = str[k++];
		mat[i][j] = '\0';
		i++;
	}
	mat[i] = NULL;
	return (mat);
}

static size_t	word_len(const char *str, char delim)
{
	size_t	len;

	len = 0;
	while (*str == delim)
		str++;
	while (*str != delim && *str++)
		len++;
	return (len);
}

static size_t	count_words(const char *str, char delim)
{
	size_t	count;

	count = 0;
	while (*str)
	{
		while (*str == delim)
			str++;
		if (*str && *str != delim)
		{
			count++;
			while (*str != delim && *str)
				str++;
		}
	}
	return (count);
}

/* int	main(void)
{
	char	**result;
	char	*test_str;
	char	delim;
	size_t	i;

	test_str = "hello   world   split this   string";
	delim = ' ';
	i = 0;
	// Call ft_split
	result = ft_split(test_str, delim);
	// Check and print the results
	if (!result)
	{
		printf("Error: ft_split returned NULL.\n");
		return (1);
	}
	printf("Original string: \"%s\"\n", test_str);
	printf("Split result:\n");
	while (result[i])
	{
		printf("result[%zu] = \"%s\"\n", i, result[i]);
		i++;
	}
	// Free allocated memory
	i = 0;
	while (result[i])
		free(result[i++]);
	free(result);
	return (0);
}
 */
