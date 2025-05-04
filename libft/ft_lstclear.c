#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next_1;

	if (!lst || !del)
		return ;
	while (*lst != NULL)
	{
		next_1 = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = next_1;
	}
	*lst = NULL;
}

/* og implementation
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current_0;
	t_list	*next_1;

	if(!lst || !del)
		return ;
	current_0 = *lst;
	while(current_0 != NULL)
	{
		next_1 = current_0 -> next;
		del(current_0 -> content);
		free(current_0);
		current_0 = next_1;
	}
	*lst = NULL;
}
*/
