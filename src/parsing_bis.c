/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:09:21 by amairia           #+#    #+#             */
/*   Updated: 2025/07/07 19:09:23 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	feed_lst_type(t_pars *lst, int is_token)
{
	if (is_token == -1)
		lst->type = T_WORD;
	else if (is_token == 1) // >
		lst->type = T_REDIR_OUT;
	else if (is_token == 2) // <
		lst->type = T_REDIR_IN;
	else if (is_token == 3) // >>
		lst->type = T_APPEND;
	else if (is_token == 4) // <<
		lst->type = T_HEREDOC;
	else if (is_token == 5) // |
		lst->type = T_PIPE;
}
