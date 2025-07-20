/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env_bis2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:47:53 by amairia           #+#    #+#             */
/*   Updated: 2025/06/18 18:20:04 by amairia          ###   ########.fr       */
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
