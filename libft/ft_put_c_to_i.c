#include "libft.h"

int	ft_put_c(va_list lst, int cpt)
{
	char	content;

	content = va_arg(lst, int);
	ft_putchar_fd(content, 1);
	cpt++;
	return (cpt);
}

int	ft_put_s(va_list lst, int cpt)
{
	char	*content;

	content = va_arg(lst, char *);
	if (!content)
	{
		ft_putstr_fd("(null)", 1);
		cpt += 6;
	}
	else
	{
		ft_putstr_fd(content, 1);
		cpt += ft_strlen(content);
	}
	return (cpt);
}

int	ft_put_p(va_list lst, int cpt)
{
	unsigned long	content;

	content = va_arg(lst, unsigned long);
	if (!content)
	{
		ft_putstr_fd("(nil)", 1);
		cpt += 5;
	}
	else
	{
		ft_putstr_fd("0x", 1);
		cpt += conv_hexa(content, "0123456789abcdef") + 2;
	}
	return (cpt);
}

int	ft_put_d(va_list lst, int cpt)
{
	int		content;
	char	*str;

	content = va_arg(lst, int);
	str = ft_itoa(content);
	ft_putstr_fd(str, 1);
	cpt += ft_strlen(str);
	free(str);
	return (cpt);
}

int	ft_put_i(va_list lst, int cpt)
{
	int		content;
	char	*str;

	content = va_arg(lst, int);
	str = ft_itoa(content);
	ft_putstr_fd(str, 1);
	cpt += ft_strlen(str);
	free(str);
	return (cpt);
}
