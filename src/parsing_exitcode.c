/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_exitcode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:36:16 by amairia           #+#    #+#             */
/*   Updated: 2025/09/02 20:24:10 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	add_env_exitcode(t_pars *lst, char *str, int check)
{
	char	*new_content;
	int		i;
	int		j;
	int		i_new;

	new_content = ft_calloc(sizeof(char), ft_strlen(lst->content) + 10);
	if (!new_content)
		return ;
	i = 0;
	j = 0;
	i_new = 0;
	while (lst->content[i])
	{
		if (i == check)
		{
			while (str[j])
				new_content[i_new++] = str[j++];
			i += 2;
		}
		else
			new_content[i_new++] = lst->content[i++];
	}
	free(lst->content);
	lst->content = new_content;
}

static int	verif_in_quote(t_pars *lst, int i)
{
	size_t	len;
	size_t	j;

	len = ft_strlen((const char *)lst->content);
	j = 0;
	while (j < len - 1)
	{
		if (lst->dtab[j] == i + 1)
			return (-1);
		j++;
	}
	j = 0;
	while (j + 1 < len - 1)
	{
		if (i >= lst->tab[j] && i < lst->tab[j + 1])
			return (-1);
		if (i > lst->tab[j + 1])
			return (1);
		j += 2;
	}
	return (1);
}

static void	check_env(t_pars *lst, int exitcode)
{
	int		i;
	char	*str;

	i = 0;
	while (lst->content[i])
	{
		if (lst->content[i] == '$' && lst->content[i + 1] == '?'
			&& verif_in_quote(lst, i) != -1)
		{
			str = ft_itoa(exitcode);
			if (str)
				add_env_exitcode(lst, str, i);
			free(str);
			i = 0;
		}
		else
			i++;
	}
}

void	pars_exitcode(t_pars **lst, int exitcode, int pipe_done)
{
	t_pars	*lst_tmp;
	int		curr_done;

	lst_tmp = *lst;
	curr_done = 0;
	while (lst_tmp && curr_done < pipe_done)
	{
		if (lst_tmp->type == T_PIPE)
			curr_done++;
		lst_tmp = lst_tmp->next;
	}
	while (lst_tmp)
	{
		if (lst_tmp->type == T_PIPE)
			break ;
		if (lst_tmp->tab)
		{
			check_env(lst_tmp, exitcode);
		}
		lst_tmp = lst_tmp->next;
	}
}
