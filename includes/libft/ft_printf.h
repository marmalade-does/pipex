/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroberts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 16:47:48 by lroberts          #+#    #+#             */
/*   Updated: 2025/05/18 10:36:23 by lroberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

// Standard C Libraries

# include <unistd.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>

// ft_printf.c
int	ft_printf(const char *str, ...);
int	h_pct(const char *str, int *idx, va_list *args, int *len);
int	h_chr(const char *str, int *idx, int *len);

// print_types.c
int	put_charsum(const char c, int *len);
int	str(const char *str, int *len);
int	number(int nb, int *len);
int	unsigned_int(unsigned int u, int *len);

// print_hexptry.c
int	rec_ptr(size_t ptr, int *len);
int	print_ptr(size_t ptr, int *len);
int	hexadecimal_up(unsigned int x, int *len);
int	hexadecimal_low(unsigned int x, int *len);

#endif
