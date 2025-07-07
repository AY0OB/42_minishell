#include "../../include/minishell.h"
#include <limits.h> // pour PATH_MAX

int	builtin_pwd(void)
{
	char	buffer[PATH_MAX]; // buffer

	// getcwd pour le chemin courant
	if (getcwd(buffer, PATH_MAX) != NULL)
	{
		// print
		ft_putstr_fd(buffer, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (0);
	}
	else
	{
		perror("minishell: pwd");
		return (1);
	}
}