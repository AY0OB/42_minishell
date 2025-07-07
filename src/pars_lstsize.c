/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_lstsize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:11:55 by amairia           #+#    #+#             */
/*   Updated: 2025/07/07 19:11:57 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
