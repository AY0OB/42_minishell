/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_bis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 11:23:22 by amairia           #+#    #+#             */
/*   Updated: 2025/08/27 11:33:51 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_redirection_bis(t_command *cmd, enum e_type type)
{
	if (type == T_REDIR_OUT)
	{
		if (cmd->redirect_out)
			free(cmd->redirect_out);
	}
	else if (type == T_REDIR_IN)
	{
		if (cmd->redirect_in)
			free(cmd->redirect_in);
	}
	else if (type == T_APPEND)
	{
		if (cmd->append_out)
			free(cmd->append_out);
	}
	else if (type == T_HEREDOC)
	{
		if (cmd->heredoc_lim)
			free(cmd->heredoc_lim);
	}
}
