/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 23:32:09 by amairia           #+#    #+#             */
/*   Updated: 2025/08/10 16:50:06 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	clear_one(t_pars *lst)
{
	t_pars	*next;
	t_pars	*prev;

	prev = lst->prev;
	next = lst->next;
	if (lst->content)
		free(lst->content);
	if (lst->tab)
		free(lst->tab);
	if (lst->dtab)
		free(lst->dtab);
	free(lst);
	if (prev && next)
	{
		prev->next = next;
		next->prev = prev;
	}
}

static void	clear_lst(t_pars **lst)
{
	t_pars	*tmp;
	t_pars	*tmp_next;

	tmp = *lst;
	while (tmp)
	{
		tmp_next = tmp->next;
		if (tmp->content[0] == '\0')
		{
			clear_one(tmp);
		}
		tmp = tmp_next;
	}
}

static int	feed_lst_token(t_pars **lst, int is_token, int *i)
{
	char	*content;

	content = ft_calloc(sizeof(char), 3);
	if (!content)
		ft_printf("Alloc error\n");
	if (!content)
		return (-1);
	if (is_token == 1 || is_token == 3)
		content[0] = '>';
	if (is_token == 2 || is_token == 4)
		content[0] = '<';
	if (is_token == 3)
		content[1] = '>';
	if (is_token == 4)
		content[1] = '<';
	if (is_token == 5)
		content[0] = '|';
	if (is_token == 1 || is_token == 2 || is_token == 5)
		++*i;
	if (is_token == 3 || is_token == 4)
		*i = *i + 2;
	if (pars_lstadd_back(lst, pars_lstnew(content, false)) == -1)
		return (-1);
	feed_lst_type(pars_lstlast(*lst), is_token);
	return (0);
}

int	parsing(char *line, t_pars **lst)
{
	int		i;
	int		is_token;

	i = 0;
	is_token = -1;
	while (line[i])
	{
		skip_space(line, &i);
		is_token = verif_token(line, i);
		if (line[i] && is_token == -1)
		{
			if (feed_lst_content(lst, line, &i, false) == -1)
				return (-1);
		}
		else if (line[i])
			if (feed_lst_token(lst, is_token, &i) == -1)
				return (-1);
	}
	pars_env(lst);
	if (here_doc(lst) == -1)// ajout d'une fonction qui gère tout les here_doc et qui remplace le "<<" here_doc par le nom du fichier a ouvrir et qui supprime le doc_stop de la liste chainée
		return (-1);
	clear_lst(lst);
	return (0);
}
