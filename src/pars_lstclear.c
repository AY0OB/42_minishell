#include "../include/minishell.h"

void	pars_lstclear(t_pars **lst)
{
	t_pars	*current;
	t_pars	*next_node;

	if (!lst)
		return ;

	current = *lst;
	while (current != NULL)
	{
		next_node = current->next;
	
		if (current->content)
			free(current->content);
		if (current->tab)
			free(current->tab);
		if (current->dtab)
			free(current->dtab);

		free(current);
		current = next_node;
	}
	*lst = NULL;
}
