#include "../include/minishell.h"

static void	free_paths_array(char **array)
{
	int	i;

	if (!array)
		return;
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

static char	*find_in_paths(char *cmd, char **envp)
{
	char	**paths_array;
	char	*path_value;
	char	*full_path;
	int		i;

	(void)envp;
	path_value = getenv("PATH");
	if (!path_value)
		return (NULL);
	paths_array = ft_split(path_value, ':');
	if (!paths_array)
		return (NULL);
	i = 0;
	while (paths_array[i])
	{
		full_path = build_path(paths_array[i], cmd);
		if (full_path && access(full_path, X_OK) == 0)
		{
			free_paths_array(paths_array);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_paths_array(paths_array);
	return (NULL);
}

char	*get_command_path(char *cmd, char **envp)
{
	if (!cmd || !cmd[0])
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd)); // copie
		else
			return (NULL); // invalid
	}

	return (find_in_paths(cmd, envp));
}