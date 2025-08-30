/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_lstadd_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 23:44:26 by amairia           #+#    #+#             */
/*   Updated: 2025/07/19 23:48:50 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	pars_lstadd_back(t_pars **lst, t_pars *new)
{
	t_pars	*tmp;

	if (!lst || !new)
		return (-1);
	if (!*lst)
	{
		*lst = new;
		return (0);
	}
	tmp = pars_lstlast(*lst);
	tmp->next = new;
	new->prev = tmp;
	return (0);
}
