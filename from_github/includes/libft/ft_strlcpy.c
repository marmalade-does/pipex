/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroberts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 09:58:56 by lroberts          #+#    #+#             */
/*   Updated: 2025/05/18 19:03:49 by lroberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Copies up to @p size - 1 characters from the string pointed to by @p src to the buffer pointed to by @p dest, null-terminating the result.
 *
 * This function is designed to be safer and more consistent than `strncpy`.
 * It guarantees null-termination of the destination buffer (as long as @p size is greater than 0).
 * It also returns the total length of the source string, not the number of bytes copied.
 *
 * @param dest A pointer to the destination buffer where the string will be copied.
 * @param src A pointer to the source string to be copied.
 * @param size The size of the destination buffer. This should include space for the null terminator.
 * @return The total length of the string pointed to by @p src, excluding the null terminator.
 * If @p size is 0, the function iterates through @p src to calculate its length and returns that value without writing to @p dest.
 */
size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
	{
		while (src[i])
			i++;
		return (i);
	}
	while (src[i] != '\0' && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i);
}
