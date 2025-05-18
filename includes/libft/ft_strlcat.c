/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroberts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 09:58:45 by lroberts          #+#    #+#             */
/*   Updated: 2025/01/03 09:58:46 by lroberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// this implementatioin is very sus, double-check

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dst_len;
	size_t	src_len;

	if (size == 0)
		return (ft_strlen(src));
	i = 0;
	j = 0;
	while (dst[i] != '\0' && i < size)
		i++;
	dst_len = i;
	src_len = ft_strlen(src);
	while (src[j] != '\0' && i < size - 1)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	if (i < size)
		dst[i] = '\0';
	return (dst_len + src_len);
}
