#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	del(lst->content);
	free(lst);
}
// MAKE SURE YOU DOUBLE CHECK THIS FUNCTION WHEN YOU GET INTO 42, SOME OF THIS SHIT IS LIKE HELLA STUPID

// del(*void) is used to free the memory allocated to *content (the studd at the end of the ptr)
// free(lst) then frees the s_list structure (including deleting the *next)
// if done in the middle of a list (say x) this would create a (x-1) dangling pointer and a ()