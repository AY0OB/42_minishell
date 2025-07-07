/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:14:31 by amairia           #+#    #+#             */
/*   Updated: 2025/07/07 20:14:37 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_index_bis(char *line, int *i, int *size)
{
	while (line[*i] && line[*i] != 32 && (line[*i] < 9 || line[*i] > 13)
		&& line[*i] != '\'' && line[*i] != '"' && verif_token(line, *i) == -1)
	{
		++*i;
		++*size;
	}
	if (line[*i] && (line[*i] == '\'' || line[*i] == '"'))
		set_index(line, i, size, line[*i]);
}

void	set_index(char *line, int *i, int *size, char quote)
{
	++*i;
	while (line[*i] && line[*i] != quote)
	{
		++*i;
		++*size;
	}
	if (line[*i + 1] == '\'' || line[*i + 1] == '"')
	{
		++*i;
		set_index(line, i, size, line[*i]);
	}
	else if (line[*i + 1] != 32 && (line[*i + 1] < 9 || line[*i + 1] > 13)
		&& line[*i + 1])
	{
		++*i;
		set_index_bis(line, i, size);
	}
}

int	verif_token(char *line, int i)
{
	int	res;

	res = -1;
	if (line[i] == '>' && (line[i + 1] != '>' || !line[i + 1]))
		res = 1;
	if (line[i] == '<' && (line[i + 1] != '<' || !line[i + 1]))
		res = 2;
	if (line[i] == '>' && (line[i + 1] == '>' && line[i + 1]))
		res = 3;
	if (line[i] == '<' && (line[i + 1] == '<' && line[i + 1]))
		res = 4;
	if (line[i] == '|')
		res = 5;
	return (res);
}

int	*tmp_index(int i)
{
	static int	tmp;

	tmp = i;
	return (&tmp);
}

void	skip_space(char *str, int *i)
{
	while (str[*i] && ((str[*i] >= 9 && str[*i] <= 13) || str[*i] == 32))
		++*i;
}
