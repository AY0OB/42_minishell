/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_content_tab.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:09:51 by amairia           #+#    #+#             */
/*   Updated: 2025/07/07 19:09:52 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_tab	set_data(int i, int j, int tab_i, int loc_quote)
{
	t_tab	tab;

	tab.i = i;
	tab.j = j;
	tab.tab_i = tab_i;
	tab.loc_quote = loc_quote;
	return (tab);
}

static int	*set_tab_size(char *line, int i, int *in_quote, char *quote)
{
	int	*tab;
	int	size;

	*in_quote = 1;
	size = 0;
	if (i > 0)
	{
		*quote = line[i - 1];
		if (line[i - 1] == '\'' || line[i - 1] == '"')
			set_index(line, tmp_index(i - 1), &size, line[i - 1]);
		else
		{
			*in_quote = 0;
			*quote = ' ';
			set_index_bis(line, tmp_index(i), &size);
		}
	}
	else
	{
		*in_quote = 0;
		*quote = ' ';
		set_index_bis(line, tmp_index(i), &size);
	}
	tab = ft_calloc(sizeof(int), even_nb(size) + 2);
	return (tab);
}

static void	feed_tab_bis(char *line, t_tab *t)
{
	if (line[t->i] == '\'' || line[t->i] == '"')
	{
		t->quote = line[t->i];
		t->in_quote = 1;
		t->i++;
	}
	else
		t->in_quote = 0;
}

static void	feed_tab(char *line, int *tab, t_tab *t)
{
	if (t->in_quote)
	{
		if (t->quote == '\'' && line[t->i] != '\'')
			tab[t->tab_i++] = t->loc_quote;
		while (line[t->i] != t->quote && t->i++ < t->j)
			t->loc_quote++;
		if (t->quote == '\'' && line[t->i - 1] != '\'')
			tab[t->tab_i++] = t->loc_quote;
		t->i++;
		feed_tab_bis(line, t);
	}
	else
	{
		while (line[t->i] != '\'' && line[t->i] != '"' && t->i < t->j)
		{
			t->loc_quote++;
			t->i++;
		}
		if ((line[t->i] == '\'' || line[t->i] == '"') && t->i < t->j)
		{
			t->in_quote = 1;
			t->quote = line[t->i];
			t->i++;
		}
	}
}

int	set_int_quote(t_pars *lst, char *line, int i, int j)
{
	int		*tab;
	int		in_quote;
	char	quote;
	t_tab	t;

	tab = set_tab_size(line, i, &in_quote, &quote);
	if (!tab)
	{
		ft_printf("Alloc error\n");
		return (-1);
	}
	t = set_data(i, j, 0, 0);
	t.in_quote = in_quote;
	t.quote = quote;
	while (t.i < t.j)
	{
		feed_tab(line, tab, &t);
	}
	lst->tab = tab;
	return (0);
}
