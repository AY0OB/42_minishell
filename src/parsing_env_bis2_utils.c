/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env_bis2_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 16:18:43 by amairia           #+#    #+#             */
/*   Updated: 2025/09/06 16:14:41 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	modif_env(char *env, int *i)
{
	while (env[*i] && env[*i] != 32
		&& (env[*i] < 9 || env[*i] > 13))
		i++;
	skip_space(&env[*i], i);
}

char	*set_char(int i, int j)
{
	char	*res;

	res = ft_calloc(sizeof(char), i + j);
	return (res);
}

static void	set_new_lst_bis(t_pars **lst, t_pars **lst_env,
		t_pars **new, t_pars **tmp_next)
{
	(*lst_env)->type = T_WORD;
	(*lst)->next = (*lst_env);
	(*lst_env)->prev = (*lst);
	if (new)
	{
		(*lst_env)->next = (*new);
		(*new)->prev = (*lst_env);
		(*new)->next = (*tmp_next);
		(*new)->tab = ft_calloc(sizeof(int),
				ft_strlen((*new)->content) * 2 + 2);
		(*new)->dtab = ft_calloc(sizeof(int),
				ft_strlen((*new)->content) * 2 + 2);
		if (*tmp_next)
			(*tmp_next)->prev = (*new);
	}
	else
	{
		(*lst_env)->next = (*tmp_next);
		if (*tmp_next)
			(*tmp_next)->prev = (*lst_env);
	}
}

static void	one_space(char *str, int *i)
{
	int	check;

	check = 0;
	while (str[*i] && ((str[*i] >= 9 && str[*i] <= 13) || str[*i] == 32))
	{
		++*i;
		check = 1;
	}
	if (check == 1 && str[*i])
		--*i;
}

void	set_new_lst(t_pars **lst, t_pars **new, char *env_var, int i)
{
	char	*content;
	int		j;
	t_pars	*tmp_next;
	t_pars	*lst_env;

	if (i == -1)
		i = 0;
	tmp_next = (*lst)->next;
	(*lst)->next = NULL;
	if (tmp_next)
		tmp_next->prev = NULL;
	content = ft_calloc(sizeof(char), ft_strlen(env_var) + 1);
	j = 0;
	while (env_var[i] && content)
	{
		one_space(env_var, &i);
		content[j++] = env_var[i++];
	}
	lst_env = pars_lstnew(content, false);
	if (new)
		set_new_lst_bis(lst, &lst_env, new, &tmp_next);
	else
		set_new_lst_bis(lst, &lst_env, NULL, &tmp_next);
}
