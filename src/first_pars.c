#include "../include/minishell.h"

static void	skip_quote(char *line, int *i, char c)
{
	++*i;
	while (line[*i] && line[*i] != c)
		++*i;
	if (line[*i])
		++*i;
}

static void	skip_token(char *line, int *i, int token)
{
	if (token == -1)
	{
		while (line[*i] && verif_token(line, *i) == -1 && ((line[*i] < 9
					|| line[*i] > 13) && line[*i] != 32) && line[*i] != '"'
			&& line[*i] != '\'')
			++*i;
		if (line[*i] && line[*i] == '"')
			skip_quote(line, i, '"');
		else if (line[*i] && line[*i] == '\'')
			skip_quote(line, i, '\'');
	}
	else
	{
		++*i;
		if (token == 3 || token == 4)
			++*i;
	}
}

static void	error_msg(int token)
{
	ft_printf("bash: syntax error near unexpected token '");
	if (token == 1)
		ft_printf(">'\n");
	else if (token == 2)
		ft_printf("<'\n");
	else if (token == 3)
		ft_printf(">>'\n");
	else if (token == 4)
		ft_printf("<<'\n");
	else if (token == 5)
		ft_printf("|'\n");
	else if (token == 6)
		ft_printf("newline'\n");
}

static int	set_pars(char *line, int *i, int *prev_is_token)
{
	int	tmp;

	*i = 0;
	skip_space(line, i);
	*prev_is_token = verif_token(line, *i);
	if (*prev_is_token == 5)
	{
		error_msg(5);
		return (-1);
	}
	skip_token(line, i, *prev_is_token);
	tmp = *i;
	while (line[tmp] && (line[tmp] == 32
			|| (line[tmp] >= 9 && line[tmp] <= 13)))
		tmp++;
	if (!line[tmp] && *prev_is_token != -1)
	{
		error_msg(6);
		return (-1);
	}
	return (0);
}

int	first_pars(char *line)
{
	int	prev_is_token;
	int	is_token;
	int	i;

	if (set_pars(line, &i, &prev_is_token) == -1)
		return (-1);
	while (line[i])
	{
		skip_space(line, &i);
		is_token = verif_token(line, i);
		if ((is_token != -1 && prev_is_token != -1 && prev_is_token != 5)
			|| (is_token == 5 && prev_is_token == 5))
		{
			error_msg(is_token);
			return (-1);
		}
		skip_token(line, &i, is_token);
		if (!line[i] && is_token != -1)
		{
			error_msg(6);
			return (-1);
		}
		prev_is_token = is_token;
	}
	return (1);
}
