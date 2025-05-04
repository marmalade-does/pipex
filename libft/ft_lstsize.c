#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*ptr;

	i = 0;
	ptr = lst;
	while (ptr)
	{
		ptr = (ptr->next);
		i++;
	}
	return (i);
}

/* recursive way of
int			ft_lstsize(t_list *lst);
{
	return (rec_size(lst, 0));
}

static int	rec_size(t_list *node, int count)
{
	if (count > 9999)
	{
		write(1, "this list is tooo loooongggg <3", 31);
		return(count);
	}
	if(next_nd == NULL)
		return (count);
	return (rec_size(node -> next, count + 1));
}
*/