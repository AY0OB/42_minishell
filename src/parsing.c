/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 23:32:09 by amairia           #+#    #+#             */
/*   Updated: 2025/09/03 21:48:07 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

static void	check_pipe(t_pars **lst, t_all *all)
{
	t_pars	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (tmp->type == T_PIPE)
		{
			all->pipe = true;
			return ;
		}
		else
			all->pipe = false;
		tmp = tmp->next;
	}
}

static void	add_typefile(t_pars **lst_all)
{
	t_pars	*lst;

	lst = *lst_all;
	while (lst)
	{
		if (lst->type == T_APPEND || lst->type == T_REDIR_IN
			|| lst->type == T_REDIR_OUT)
			lst->next->type = T_FILE;
		lst = lst->next;
	}
}

int	parsing(char *line, t_pars **lst, t_all *all)
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
	check_pipe(lst, all);
	pars_env(lst, all);
	pars_exitcode(lst, all->last_exit_status, 0);
	if (here_doc(lst, all->env_list) == -1)
		return (1);
	add_typefile(lst);
	return (0);
}
