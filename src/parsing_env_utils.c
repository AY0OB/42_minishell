/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:47:53 by amairia           #+#    #+#             */
/*   Updated: 2025/08/10 18:21:25 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_envbis	set_envbis(void)
{
	t_envbis	info;

	info.j = 0;
	info.k = 0;
	info.l = 0;
	return (info);
}

int	check_tab(int *tab, int *dtab, int len_tab)
{
	int	i;

	i = 0;
	if (!tab || !dtab)
		return (0);
	while (i < len_tab)
	{
		if (tab[i] != 0 || dtab[i] != 0)
			return (-1);
		i++;
	}
	return (0);
}

int	end_env(char *str, t_envbis info, int end_quote)
{
	info.j++;
	if (str[info.j] == '$')
		return (info.j + 1);
	while (str[info.j] && (str[info.j] < 9 || str[info.j] > 13)
		&& str[info.j] != 32 && info.j < end_quote
		&& str[info.j] != '\'' && str[info.j] != '$')
	{
		info.j++;
	}
	return (info.j);
}

int	check_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
			return (-1);
		else
			i++;
	}
	return (0);
}
