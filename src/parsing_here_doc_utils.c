/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_here_doc_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 17:20:47 by amairia           #+#    #+#             */
/*   Updated: 2025/08/21 21:28:58 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	aff_ctrld(char *doc_stop)
{
	ft_printf(HD_END, doc_stop);
	return (0);
}

void	hd_ctrlc(int sig)
{
	(void)sig;
	rl_replace_line("	", 1);
	rl_done = 1;
}
