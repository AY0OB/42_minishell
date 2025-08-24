/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 21:05:54 by amairia           #+#    #+#             */
/*   Updated: 2025/08/24 22:29:49 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool    ft_tofind(char *str, char *to_find)
{
    int    i;

    i = 0;
    while (to_find[i])
    {
        if (to_find[i] != str[i])
            return (false);
        i++;
    }
    if (str[i] != '=')
        return (false);
    return (true);
}

static int    size_envvar(char *str)
{
    int    i;
    int    j;

    i = 0;
    j = 0;
    while (str[i] && str[i] != '=')
        i++;
    i += 2;
    while (str[i] && str[i] != '"')
    {
        i++;
        j++;
    }
    return (j);
}

char	*ft_fill_env(char *content)
{
	int 	i;
	int 	j;
	char	*env_content;

	i = 0;
	j = 0;
	env_content = ft_calloc(sizeof(char), size_envvar(content) + 1);
        if (!env_content)
        	return (NULL);
	while (content[j] != '=')
		j++;
	j += 2;
	while (content[j] && content[j] != '"')
	{
		env_content[i] = content[j];
		i++;
		j++;
	}
	return (env_content);
}

static void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

char    *ft_getenv(char *env_name, t_list *env_list)
{
    char	*env_content;
    char	**array;
    int		i;

    i = 0;
	array = env_list_to_array(env_list, ft_lstsize(env_list));
    while (array[i])
    {
        if (array[i][0] == env_name[0])
        {
            if (ft_tofind(array[i], env_name))
            {
		env_content = ft_fill_env(array[i]);
		free_array(array);
		return (env_content);
            }
        }
        i++;
    }
    free_array(array);
    return (NULL);
}
