/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 20:13:54 by amairia           #+#    #+#             */
/*   Updated: 2025/09/06 16:13:30 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	add_key_value(t_env_var *var, char **envp, int i)
{
	char	*tmp;
	char	*tmp_key;
	char	*tmp_value;

	tmp = ft_calloc(sizeof(char), 1);
	if (!tmp)
		return ;
	tmp_key = ft_strjoin(tmp, var->key);
	if (!tmp_key)
	{
		free(tmp);
		return ;
	}
	tmp_value = ft_strjoin(tmp_key, "=");
	if (!tmp_value)
	{
		free(tmp);
		free(tmp_key);
		return ;
	}
	envp[i] = ft_strjoin(tmp_value, var->value);
	free(tmp);
	free(tmp_key);
	free(tmp_value);
}

static char	**get_env_list(t_list *env_list, int size_list)
{
	char		**envp;
	char		*tmp;
	char		*tmp_key;
	t_env_var	*var;
	int			i;

	i = 0;
	envp = ft_calloc(sizeof(char *), size_list + 1);
	if (!envp)
		return (NULL);
	while (i < size_list)
	{
		tmp = NULL;
		tmp_key = NULL;
		var = env_list->content;
		add_key_value(var, envp, i);
		env_list = env_list->next;
		i++;
	}
	return (envp);
}

void	ft_execve(t_all *all, char **cmd_path, char ***cmd)
{
	char	**envp;
	int		i;

	envp = get_env_list(all->env_list, ft_lstsize(all->env_list));
	signal(SIGQUIT, SIG_DFL);
	execve(cmd_path[0], cmd[0], envp);
	perror("execve");
	i = 0;
	while (envp && envp[i])
		free(envp[i++]);
	if (envp)
		free(envp);
	free(cmd_path[0]);
	free(cmd[0]);
	close(all->data.og_in);
	close(all->data.og_out);
	if (all->data.std_in != 0)
		close(all->data.std_in);
	if (all->data.std_out != 1)
		close(all->data.std_out);
	clear_all(all, NULL);
	exit(126);
}

char	**feed_cmd(t_all *all)
{
	char	**cmd;
	int		i;
	int		curr_done;
	t_pars	*lst;

	lst = *(all->lst);
	cmd = ft_calloc(sizeof(char *), pars_lstsize(lst) + 1);
	if (!cmd)
		return (NULL);
	curr_done = 0;
	while (lst && curr_done < all->data.pipe_done)
	{
		if (lst->type == T_PIPE)
			curr_done++;
		lst = lst->next;
	}
	i = 0;
	while (lst && lst->type != T_PIPE)
	{
		if (lst->type == T_WORD)
			cmd[i++] = lst->content;
		lst = lst->next;
	}
	return (cmd);
}

void	clear_fd(t_all *all)
{
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
