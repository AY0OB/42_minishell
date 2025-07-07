#include "../include/minishell.h"

void	clear_all(t_all *all, char *line)
{
	if (line)
		free(line);
	pars_lstclear(all->lst);
	ft_lstclear(&all->env_list, free_env_var);
	clear_history();
	free(all);
}
