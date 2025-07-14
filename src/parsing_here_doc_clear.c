/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_here_doc_clear.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:05:48 by amairia           #+#    #+#             */
/*   Updated: 2025/07/11 15:40:13 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	clear_doc_stop(t_pars *lst)
{
	t_pars	*to_clear;
	t_pars	*new_next;

	to_clear = NULL;
	to_clear = lst->next;
	new_next = NULL;
	if (lst->next->next)
		new_next = lst->next->next;
	if (new_next)
	{
		lst->next = new_next;
		new_next->prev = lst;
	}
	else
		lst->next = NULL;
	if (to_clear->content)
		free(to_clear->content);
	if (to_clear->tab)
		free(to_clear->tab);
	if (to_clear->dtab)
		free(to_clear->dtab);
	free(to_clear);
}
