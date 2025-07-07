#include "../include/minishell.h"

void	pars_lstadd_back(t_pars **lst, t_pars *new)
{
    t_pars	*tmp;
    if (!lst || !new)
        return ;
    if (!*lst) 
    {
        *lst = new;
        return ; 
    }
    tmp = pars_lstlast(*lst);
    tmp->next = new;
    new->prev = tmp;

}
