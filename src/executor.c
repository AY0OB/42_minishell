/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolavale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:15:47 by rolavale          #+#    #+#             */
/*   Updated: 2025/08/29 16:45:59 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	closeifopen(t_all *all, int check)
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

int	trytoopen_bis(t_pars *lst, t_all *all, int fd)
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

char	**feed_cmd(t_all *all)
{
	char	**cmd;
	int		i;
	t_pars	*lst;

	lst = *(all->lst);
	cmd = ft_calloc(sizeof(char *), pars_lstsize(lst) + 1);
	if (!cmd)
		return (NULL);
	i = 0;
	while (lst && lst->type != T_PIPE)
	{
		if (lst->type == T_WORD)
			cmd[i++] = lst->content;
		lst = lst->next;
	}
	return (cmd);
}

void	builtin(t_all *all)
{
	int	exitcode;
	char	**cmd;

	cmd = feed_cmd(all);
	if (!cmd)
		return ;
	exitcode = execute_builtin(cmd, all);
	free(cmd);
	if (all->faile_open)
		all->last_exit_status = 1;
	else
		all->last_exit_status = exitcode;
}

void	dup_redir_built(t_all *all)
{
	int	og_in;
	int	og_out;

	og_in = dup(STDIN_FILENO);
	og_out = dup(STDOUT_FILENO);
	if (all->data.std_in != 0)
		dup2(all->data.std_in, STDIN_FILENO);
	if (all->data.std_out != 1)
		dup2(all->data.std_out, STDOUT_FILENO);
	builtin(all);
	all->faile_open = false;
	dup2(og_in, STDIN_FILENO);
	dup2(og_out, STDOUT_FILENO);
	close(og_in);
	close(og_out);
	if (all->data.std_in != 0)
	{
		close(all->data.std_in);
		all->data.std_in = 0;
	}
	if (all->data.std_out != 1)
	{
		close(all->data.std_out);
		all->data.std_out = 1;
	}
}

void	set_redirections_built(t_pars *lst, t_all *all)
{
	while (lst)
	{
		if (check_redir(lst->type) == 1)
		{
			if (trytoopen(lst, all, 0) == -1)
			{
				all->faile_open = true;
				if (all->data.std_in != 0)
				{
					close(all->data.std_in);
					all->data.std_in = 0;
				}
				if (all->data.std_out != 1)
				{
					close(all->data.std_out);
					all->data.std_out = 1;
				}
				all->last_exit_status = 1;
				return ;
			}
		}
		lst = lst->next;
	}
	dup_redir_built(all);
}

static int	builtin_check(t_pars **lst)
{
	t_pars	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (tmp->type == T_WORD)
		{
			if (is_builtin(tmp->content))
				return (1);
			else
				return (-1);
		}
		tmp = tmp->next;
	}
	return (-1);
}

int	executor(char **envp, t_all *all)
{
	if (all->pipe == false && builtin_check(all->lst) == 1)
		set_redirections_built(*(all->lst), all);
	else if (all->pipe == false)
		set_redirections(*(all->lst), all, envp);
	//else
		//simple_command();
	return (0);
}
