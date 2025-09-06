/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 01:12:24 by amairia           #+#    #+#             */
/*   Updated: 2025/09/04 20:23:39 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	free_paths_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static char	*build_path(char *dir_path, char *cmd)
{
	char	*path_with_slash;
	char	*full_path;

	path_with_slash = ft_strjoin(dir_path, "/");
	if (!path_with_slash)
		return (NULL);
	full_path = ft_strjoin(path_with_slash, cmd);
	free(path_with_slash);
	return (full_path);
}

static bool	verif_free_paths(char *path_value, char **paths_array)
{
	if (!paths_array)
	{
		free(path_value);
		return (false);
	}
	return (true);
}

static char	*find_in_paths(char *cmd, int i, t_list *env_list)
{
	char	**paths_array;
	char	*path_value;
	char	*full_path;

	path_value = ft_getenv("PATH", env_list);
	if (!path_value)
		return (NULL);
	paths_array = ft_split(path_value, ':');
	if (!verif_free_paths(path_value, paths_array))
		return (NULL);
	while (paths_array[i])
	{
		full_path = build_path(paths_array[i], cmd);
		if (full_path && access(full_path, X_OK) == 0)
		{
			free_paths_array(paths_array);
			free(path_value);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_paths_array(paths_array);
	free(path_value);
	return (NULL);
}

char	*get_command_path(char *cmd, t_list *env_list)
{
	if (!cmd || !cmd[0])
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	return (find_in_paths(cmd, 0, env_list));
}
