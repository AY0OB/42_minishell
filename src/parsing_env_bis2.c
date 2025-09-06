/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env_bis2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:52:29 by amairia           #+#    #+#             */
/*   Updated: 2025/08/10 18:12:23 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*next_content(t_pars *lst, int j)
{
	char	*next_content;
	int		i;

	i = 0;
	if (lst->content[j] == '\0')
		return (NULL);
	next_content = ft_calloc(sizeof(char), ft_strlen(lst->content) + 1);
	if (!next_content)
		return (NULL);
	while (lst->content[j])
		next_content[i++] = lst->content[j++];
	return (next_content);
}

static void	change_bis(char *content, int *j)
{
	++*j;
	while (content[*j] && content[*j] != 32
		&& (content[*j] < 9 || content[*j] > 13)
		&& content[*j] != '$')
		++*j;
}

static char	*change_content(t_pars *lst, char *env_var, int *index, int i)
{
	char	*new_content;
	int		j;
	int		i_new;
	char	*n_content;

	new_content = set_char(ft_strlen(env_var) * 5, ft_strlen(lst->content) + 1);
	j = 0;
	i_new = 0;
	while (lst->content[j] && new_content)
	{
		if (j == i)
		{
			change_bis(lst->content, &j);
			while (env_var[*index] && env_var[*index] != 32
				&& (env_var[*index] < 9 || env_var[*index] > 13))
				new_content[i_new++] = env_var[(*index)++];
			n_content = next_content(lst, j);
			free(lst->content);
			lst->content = new_content;
			return (n_content);
		}
		else
			new_content[i_new++] = lst->content[j++];
	}
	return (NULL);
}

static char	*supp_env(t_pars *lst, int i)
{
	char	*n_content;
	int		j;

	j = i;
	j++;
	while (lst->content[j] && lst->content[j] != 32
		&& (lst->content[j] < 9 || lst->content[j] > 13)
		&& lst->content[j] != '$')
		j++;
	n_content = next_content(lst, j);
	lst->content[i] = '\0';
	return (n_content);
}

void	feed_new_lst(t_pars *lst, char *env_var, int i)
{
	t_pars	*new;
	int		index;
	char	*next_content;

	index = 0;
	new = NULL;
	if (env_var[0] != 32 && (env_var[0] < 9 || env_var[0] > 13))
	{
		next_content = change_content(lst, env_var, &index, i);
		modif_env(env_var, &index);
	}
	else
	{
		next_content = supp_env(lst, i);
		skip_space(env_var, &index);
	}
	if (next_content)
	{
		new = pars_lstnew(next_content, false);
		new->type = T_WORD;
	}
	if (new)
		set_new_lst(&lst, &new, env_var, index);
	else
		set_new_lst(&lst, NULL, env_var, index);
}
