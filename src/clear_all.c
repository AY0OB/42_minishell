/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 23:50:37 by amairia           #+#    #+#             */
/*   Updated: 2025/07/27 08:35:14 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	clear_all(t_all *all, char *line)
{
	if (line)
		free(line);
	if (!all)
		return ;
	pars_lstclear(all);
	ft_lstclear(&all->env_list, free_env_var);
	clear_history();
	if (all)
		free(all);
}
