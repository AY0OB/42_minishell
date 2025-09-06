/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_here_doc_env.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 11:20:49 by amairia           #+#    #+#             */
/*   Updated: 2025/07/11 15:04:44 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	sizeof_prev_env(char *line, int i)
{
	int	len;

	len = 0;
	while (line[i] && (line[i] < 9 || line[i] > 13) && line[i] != 32
		&& line[i] != '\'' && line[i] != '"' && line[i] != '$')
	{
		i++;
		len++;
	}
	return (len + 2);
}

static int	sizeof_newline(char *line, char *env)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (line[i] && line[i] != '$')
	{
		i++;
		len++;
	}
	if (line[i] == '$')
		i++;
	while (line[i] && (line[i] < 9 || line[i] > 13) && line[i] != 32
		&& line[i] != '\'' && line[i] != '"' && line[i] != '$')
		i++;
	while (line[i])
	{
		len++;
		i++;
	}
	if (env)
		len += ft_strlen((const char *)env);
	return (len + 3);
}

static char	*set_new_line(char *line, char *env, int i)
{
	char	*new_line;
	int		j;
	int		i_new;

	new_line = ft_calloc(sizeof(char), sizeof_newline(line, env));
	if (!new_line)
		return (NULL);
	i = 0;
	j = 0;
	i_new = 0;
	while (line[i] && line[i] != '$')
		new_line[i_new++] = line[i++];
	if (line[i] == '$')
		i++;
	while (line[i] && (line[i] < 9 || line[i] > 13) && line[i] != 32
		&& line[i] != '\'' && line[i] != '"' && line[i] != '$')
		i++;
	if (env)
	{
		while (env[j])
			new_line[i_new++] = env[j++];
	}
	while (line[i])
		new_line[i_new++] = line[i++];
	return (new_line);
}

static int	change_line(char **line, int i, t_list *env_list)
{
	char	*prev_env;
	char	*env;
	char	*new_line;
	int		j;

	prev_env = ft_calloc(sizeof(char), sizeof_prev_env(*line, i));
	if (!prev_env)
		return (-1);
	j = 0;
	while (line[0][i] && (line[0][i] < 9 || line[0][i] > 13) && line[0][i] != 32
		&& line[0][i] != '\'' && line[0][i] != '"' && line[0][i] != '$')
		prev_env[j++] = line[0][i++];
	env = ft_getenv(prev_env, env_list);
	free(prev_env);
	new_line = set_new_line(*line, env, i);
	if (env)
		free(env);
	if (!new_line)
		return (-1);
	free(*line);
	*line = new_line;
	return (0);
}

void	check_env_hd(char **line, t_list *env_list)
{
	int		i;

	i = 0;
	while (line[0][i])
	{
		if (line[0][i] == '$')
		{
			change_line(line, i + 1, env_list);
			i = 0;
		}
		i++;
	}
}
