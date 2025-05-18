/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroberts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 09:53:22 by lroberts          #+#    #+#             */
/*   Updated: 2025/01/03 09:53:23 by lroberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_obj;
	t_list	*current;

	if (!lst || !f || !del)
		return (NULL);
	new_list = ft_lstnew(f(lst->content));
	if (!new_list)
		return (NULL);
	current = new_list;
	lst = lst->next;
	while (lst)
	{
		new_obj = ft_lstnew(f(lst->content));
		if (!new_obj)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		current->next = new_obj;
		current = new_obj;
		lst = lst->next;
	}
	return (new_list);
}

// this implementation has a head node WITH data, see if that's correct

/*
// Sample deletion function
void delete_content(void *content)
{
    free(content); // Free the string content
}

// Helper function to print the list
void print_list(t_list *lst)
{
    while (lst)
    {
        printf("%s -> ", (char *)lst->content);
        lst = lst->next;
    }
    printf("NULL\n");
}

void *uppercase(void *content)
{
    char *str = (char *)content;
    char *new_str = strdup(str); // Duplicate the string
    if (!new_str)
        return NULL;

    for (int i = 0; new_str[i]; i++)
        if (new_str[i] >= 'a' && new_str[i] <= 'z')
            new_str[i] -= 32; // Convert to uppercase

    return new_str;
}

// Main function to test ft_lstmap
int main(void)
{
    // Create a linked list
    t_list *list = ft_lstnew(strdup("hello"));
    list->next = ft_lstnew(strdup("world"));
    list->next->next = ft_lstnew(strdup("libft"));
    list->next->next->next = NULL;

    printf("Original list:\n");
    print_list(list);

    // Apply ft_lstmap with the uppercase function
    t_list *new_list = ft_lstmap(list, &uppercase, &delete_content);

    printf("\nTransformed list:\n");
    print_list(new_list);

    // Free both lists
    ft_lstclear(&list, &delete_content);
    ft_lstclear(&new_list, &delete_content);

    return 0;
}*/
