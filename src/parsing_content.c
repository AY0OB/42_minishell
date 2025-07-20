/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_content.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 23:33:04 by amairia           #+#    #+#             */
/*   Updated: 2025/07/19 23:33:06 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_content	set_data(char *line, int i, int j, int k)
{
	t_content	data;
	char		quote;
	int			inclu_quote;

	j = 0;
	if (k > 0)
		quote = line[k - 1];
	else
		quote = line[k];
	if (quote == '\'' || quote == '"')
		inclu_quote = 1;
	else
		inclu_quote = 0;
	data.quote = quote;
	data.i = i;
	data.j = j;
	data.k = k;
	data.inclu_quote = inclu_quote;
	return (data);
}

static void	feed_content_bis(char *line, char *content, t_content *d)
{
	if (d->inclu_quote)
	{
		while (line[d->k] != d->quote && d->k < d->i)
			content[d->j++] = line[d->k++];
		d->k++;
		if (line[d->k] == d->quote
			&& (line[d->k + 1] == '\'' || line[d->k + 1] == '"'))
		{
			d->quote = line[d->k + 1];
			d->k++;
		}
		else
			d->inclu_quote = 0;
	}
	else
	{
		while (line[d->k] != '\'' && line[d->k] != '"' && d->k < d->i)
			content[d->j++] = line[d->k++];
		if (line[d->k] == '\'' || line[d->k] == '"')
		{
			d->inclu_quote = 1;
			d->quote = line[d->k];
			d->k++;
		}
	}
}

static char	*feed_content(char *line, int i, int j, int k)
{
	t_content	d;
	char		*content;

	content = ft_calloc(sizeof(char), j + 1);
	if (!content)
	{
		ft_printf("Alloc error\n");
		return (NULL);
	}
	d = set_data(line, i, j, k);
	while (d.k < d.i)
	{
		feed_content_bis(line, content, &d);
	}
	return (content);
}

int	feed_lst_content(t_pars **lst, char *line, int *i, bool hdq)
{
	char	*content;
	int		j;
	int		k;

	k = *i;
	if (line[*i] == '\'' || line[*i] == '"')
		k++;
	j = 0;
	if (line[*i] == '\'' || line[*i] == '"')
		hdq = set_index(line, i, &j, line[*i]);
	else
		hdq = set_index_bis(line, i, &j, false);
	content = feed_content(line, *i, j, k);
	if (!content)
		return (-1);
	if (line[*i] == '\'' || line[*i] == '"')
		++*i;
	if (pars_lstadd_back(lst, pars_lstnew(content, hdq)) == -1)
		return (-1);
	feed_lst_type(pars_lstlast(*lst), -1);
	if (set_int_quote(pars_lstlast(*lst), line, k, (*i) - 1) == -1)
		return (-1);
	if (set_int_dquote(pars_lstlast(*lst), line, k, (*i) - 1) == -1)
		return (-1);
	return (1);
}
