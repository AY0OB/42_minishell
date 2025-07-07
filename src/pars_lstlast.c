#include "../include/minishell.h"

t_pars	*pars_lstlast(t_pars *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}

	return (lst);
}
