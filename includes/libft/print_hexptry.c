/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexptry.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroberts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 22:24:56 by lroberts          #+#    #+#             */
/*   Updated: 2025/05/18 10:36:21 by lroberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	rec_ptr(size_t ptr, int *len)
{
	const char	*hex_arr = "0123456789abcdef";

	if (ptr >= 16)
	{
		if (rec_ptr(ptr / 16, len) == -1)
			return (-1);
	}
	if (put_charsum(hex_arr[ptr % 16], len) == -1)
		return (-1);
	return (0);
}

// too many functions from here on

int	print_ptr(size_t ptr, int *len)
{
	if (ptr == 0)
	{
		if (str("(nil)", len) == -1)
			return (-1);
	}
	else
	{
		if (str("0x", len) == -1)
			return (-1);
		if (rec_ptr(ptr, len) == -1)
			return (-1);
	}
	return (0);
}

int	hexadecimal_up(unsigned int x, int *len)
{
	const char	*hex_arr = "0123456789ABCDEF";

	if (x == 0)
	{
		if (put_charsum('0', len) == -1)
			return (-1);
		return (0);
	}
	if (x >= 16)
	{
		if (hexadecimal_up(x / 16, len) == -1)
			return (-1);
	}
	if (put_charsum(hex_arr[x % 16], len) == -1)
		return (-1);
	return (0);
}

int	hexadecimal_low(unsigned int x, int *len)
{
	const char	*hex_arr = "0123456789abcdef";

	if (x == 0)
	{
		if (put_charsum('0', len) == -1)
			return (-1);
		return (0);
	}
	if (x >= 16)
	{
		if (hexadecimal_low(x / 16, len) == -1)
			return (-1);
	}
	if (put_charsum(hex_arr[x % 16], len) == -1)
		return (-1);
	return (0);
}
