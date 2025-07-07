/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:09:29 by amairia           #+#    #+#             */
/*   Updated: 2025/07/07 19:46:33 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	feed_lst_token(t_pars **lst, int is_token, int *i)
{
	char	*content;
	t_pars	*new_node; // var temp

	content = ft_calloc(sizeof(char), 3);
	if (!content)
	{
		ft_printf("Alloc error\n");
		return (-1);
	}
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
	new_node = pars_lstnew(content);
	if (!new_node)
	{
		free(content);
		return (-1);
	}
	pars_lstadd_back(lst, new_node);
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
			if (feed_lst_content(lst, line, &i) == -1)
				return (-1);
		}
		else if (line[i])
			if (feed_lst_token(lst, is_token, &i) == -1)
				return (-1);
	}
	pars_env(lst);
	//normalization(lst);
	return (0);
}
