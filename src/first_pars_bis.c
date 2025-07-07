#include "../include/minishell.h"

static int	quote_end(char *line, char quote, int *i)
{
	++*i;
	while (line[*i] && line[*i] != quote)
	{
		++*i;
	}
	if (!line[*i])
	{
		ft_printf("bash: syntax error quote %c\n", quote, *i);
		return (-1);
	}
	else
		return (1);
}

int	check_quote(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			if (quote_end(line, line[i], &i) == -1)
				return (-1);
		}
		i++;
	}
	return (1);
}
