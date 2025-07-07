/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_lstnew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:11:49 by amairia           #+#    #+#             */
/*   Updated: 2025/07/07 19:11:51 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_pars	*pars_lstnew(char *content)
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
	mylist->tab = NULL;
	mylist->dtab = NULL;
	mylist->norm = 0;
	mylist->prev = NULL;
	mylist->next = NULL;
	return (mylist);
}
