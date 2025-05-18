/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroberts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 09:52:46 by lroberts          #+#    #+#             */
/*   Updated: 2025/01/03 10:02:53 by lroberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	del(lst->content);
	free(lst);
}
// MAKE SURE YOU DOUBLE CHECK THIS FUNCTION 
// ---- WHEN YOU GET INTO 42, SOME OF THIS SHIT IS LIKE HELLA STUPID

// del(*void) is used to free 
// ---- the memory allocated to *content (the studd at the end of the ptr)
// free(lst) then frees the s_list structure (including deleting the *next)
// if done in the middle of a 
// ---- list (say x) this would create a (x-1) dangling pointer and a ()
