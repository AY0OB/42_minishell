/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_open.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 16:37:40 by amairia           #+#    #+#             */
/*   Updated: 2025/09/05 16:38:47 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	closeifopen(t_all *all, int check)
{
	if (all->data.std_in != 0 && check == 0)
	{
		close(all->data.std_in);
		all->data.std_in = 0;
		return ;
	}
	if (all->data.std_out != 1 && check == 1)
	{
		close(all->data.std_out);
		all->data.std_out = 1;
		return ;
	}
}

static int	trytoopen_bis(t_pars *lst, t_all *all, int fd)
{
	if (lst->type == T_REDIR_OUT)
	{
		fd = open(lst->next->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror(lst->next->content);
			return (-1);
		}
		closeifopen(all, 1);
		all->data.std_out = fd;
	}
	if (lst->type == T_APPEND)
	{
		fd = open(lst->next->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			perror(lst->next->content);
			return (-1);
		}
		closeifopen(all, 1);
		all->data.std_out = fd;
	}
	return (0);
}

int	trytoopen(t_pars *lst, t_all *all, int fd)
{
	if (lst->type == T_REDIR_IN)
	{
		fd = open(lst->next->content, O_RDONLY);
		if (fd == -1)
		{
			perror(lst->next->content);
			return (-1);
		}
		closeifopen(all, 0);
		all->data.std_in = fd;
	}
	if (lst->type == T_HEREDOC)
	{
		fd = open(lst->content, O_RDONLY);
		if (fd == -1)
		{
			perror(lst->content);
			return (-1);
		}
		closeifopen(all, 0);
		all->data.std_in = fd;
	}
	return (trytoopen_bis(lst, all, fd));
}
