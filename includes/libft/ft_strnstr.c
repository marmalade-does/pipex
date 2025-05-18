/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroberts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 10:00:12 by lroberts          #+#    #+#             */
/*   Updated: 2025/01/03 10:00:13 by lroberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// apparently the stadard lib doesn't handle cases where needle == NULL

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	size_t	j;
	char	*editable_haystack;

	editable_haystack = (char *)haystack;
	i = 0;
	j = 0;
	if (needle == NULL || needle[0] == '\0')
		return (editable_haystack);
	while (editable_haystack[i] != '\0' && i < n)
	{
		if (editable_haystack[i] == needle[j])
		{
			while (editable_haystack[i + j] == needle[j] && i + j < n)
			{
				if (needle[j + 1] == '\0')
					return (editable_haystack + i);
				j++;
			}
			j = 0;
		}
		i++;
	}
	return (NULL);
}
