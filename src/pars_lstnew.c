/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_lstnew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 23:50:02 by amairia           #+#    #+#             */
/*   Updated: 2025/07/19 23:50:03 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_pars	*pars_lstnew(char *content, bool hdq)
{
	t_pars	*mylist;

	mylist = malloc(sizeof(t_pars));
	if (!mylist)
	{
		ft_printf("Alloc error\n");
		return (NULL);
	}
	mylist->content = content;
	mylist->type = T_UNKNOWN;
	mylist->hdq = hdq;
	mylist->tab = NULL;
	mylist->dtab = NULL;
	mylist->prev = NULL;
	mylist->next = NULL;
	return (mylist);
}
