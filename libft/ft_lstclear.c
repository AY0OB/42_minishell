#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
    t_list	*current;
    t_list	*next_node;

    if (!lst)
        return ;
    current = *lst;
    while (current)
    {
        next_node = current->next;
        if (del)
        	del(current->content);
    	free(current);
        current = next_node;
    }
    *lst = NULL;
}