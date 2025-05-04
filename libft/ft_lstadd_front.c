#include "libft.h"

// need to check documentation
// --- if(!(*lst))
// --- --- then should I make new the fist (new) elemnt
// in the list (like in add_back)
// Do the safety check in the front?

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new == NULL)
		return ;
	new->next = *lst;
	*lst = new;
}
