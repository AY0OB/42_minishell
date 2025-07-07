/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:05:54 by amairia           #+#    #+#             */
/*   Updated: 2025/07/07 19:05:59 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
