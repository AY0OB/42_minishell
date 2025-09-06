/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_bis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 16:42:24 by amairia           #+#    #+#             */
/*   Updated: 2025/09/05 16:45:16 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_redir(enum e_type type)
{
	if (type == T_REDIR_IN)
		return (1);
	if (type == T_REDIR_OUT)
		return (1);
	if (type == T_APPEND)
		return (1);
	if (type == T_HEREDOC)
		return (1);
	return (-1);
}

void	builtin(t_all *all)
{
	int		exitcode;
	char	**cmd;

	cmd = feed_cmd(all);
	if (!cmd)
		return ;
	exitcode = execute_builtin(cmd, all, 127);
	free(cmd);
	if (all->faile_open)
		all->last_exit_status = 1;
	else
		all->last_exit_status = exitcode;
}

void	dup_redir_built(t_all *all)
{
	all->data.og_in = dup(STDIN_FILENO);
	all->data.og_out = dup(STDOUT_FILENO);
	if (all->data.std_in != 0)
		dup2(all->data.std_in, STDIN_FILENO);
	if (all->data.std_out != 1)
		dup2(all->data.std_out, STDOUT_FILENO);
	builtin(all);
	all->faile_open = false;
	dup2(all->data.og_in, STDIN_FILENO);
	dup2(all->data.og_out, STDOUT_FILENO);
	close(all->data.og_in);
	close(all->data.og_out);
	clear_fd(all);
}
