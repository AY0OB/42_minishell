/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_pars_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 00:07:58 by amairia           #+#    #+#             */
/*   Updated: 2025/07/20 00:07:59 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	quote_end(char *line, char quote, int *i)
{
	++*i;
	while (line[*i] && line[*i] != quote)
	{
		++*i;
	}
	if (!line[*i])
	{
		ft_printf("bash: syntax error quote %c\n", quote, *i);
		return (-1);
	}
	else
		return (1);
}

int	check_quote(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			if (quote_end(line, line[i], &i) == -1)
				return (-1);
		}
		i++;
	}
	return (1);
}
