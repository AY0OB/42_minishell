/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_lstclear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:11:20 by amairia           #+#    #+#             */
/*   Updated: 2025/07/14 00:32:25 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	clear_here_doc(t_pars **lst)
{
	t_pars	*tmp_lst;

	tmp_lst = *lst;
	if (!tmp_lst)
		return ;
	while (tmp_lst)
	{
		if (tmp_lst->type == T_HEREDOC)
		{
			if (tmp_lst->content)
				unlink((const char *)tmp_lst->content);
		}
		tmp_lst = tmp_lst->next;
	}
}

void	pars_lstclear(t_all *all)
{
	t_pars	**lst;
	t_pars	*tmp_next;

	lst = all->lst;
	if (!lst)
		return ;
	clear_here_doc(lst);
	if (*lst)
	{
		while (*lst)
		{
			tmp_next = (*lst)->next;
			if ((*lst)->content)
				free((*lst)->content);
			if ((*lst)->tab)
				free((*lst)->tab);
			if ((*lst)->dtab)
				free((*lst)->dtab);
			free(*lst);
			*lst = tmp_next;
		}
	}
	all->lst = NULL;
	if (lst)
		free(lst);
}
