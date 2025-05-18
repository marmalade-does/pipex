/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroberts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 16:29:24 by lroberts          #+#    #+#             */
/*   Updated: 2025/05/18 10:36:18 by lroberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	put_charsum(const char c, int *len)
{
	if (write(1, &c, 1) == -1)
		return (-1);
	(*len)++;
	return (0);
}

int	str(const char *str, int *len)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		if (write(1, "(null)", 6) == -1)
			return (-1);
		(*len) += 6;
		return (0);
	}
	while (str[i] != '\0')
	{
		if (put_charsum(str[i], len) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int	number(int nb, int *len)
{
	if (nb == INT_MIN)
	{
		if (write(1, "-2147483648", 11) == -1)
			return (-1);
		(*len) += 11;
		return (0);
	}
	if (nb < 0)
	{
		if (put_charsum('-', len) == -1)
			return (-1);
		nb *= -1;
	}
	if (nb >= 10)
	{
		if (number(nb / 10, len) == -1)
			return (-1);
	}
	if (put_charsum((nb % 10 + '0'), len) == -1)
		return (-1);
	return (0);
}

int	unsigned_int(unsigned int u, int *len)
{
	if (u >= 10)
	{
		if (unsigned_int(u / 10, len) == -1)
			return (-1);
	}
	if (put_charsum(u % 10 + '0', len) == -1)
		return (-1);
	return (0);
}
