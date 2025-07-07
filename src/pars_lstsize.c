#include "../include/minishell.h"

int	pars_lstsize(t_pars *lst)
{
	size_t	cpt;

	if (!lst)
		return (0);
	cpt = 0;
	while (lst)
	{
		cpt++;
		lst = lst->next;
	}
	return (cpt);
}
