#include "libft.h"

int	conv_hexa(unsigned long nb, char *hexa_case)
{
	char	buffer[20];
	int		i;
	int		size;

	nb = (unsigned long)nb;
	if (nb == 0)
	{
		ft_putchar_fd('0', 1);
		return (1);
	}
	i = 0;
	while (nb > 0)
	{
		buffer[i++] = hexa_case[nb % 16];
		nb /= 16;
	}
	size = 0;
	while (--i >= 0)
	{
		ft_putchar_fd(buffer[i], 1);
		size++;
	}
	return (size);
}

static int	check_conv(va_list lst, int cpt, char c)
{
	if (c == 'c')
		cpt = ft_put_c(lst, cpt);
	else if (c == 's')
		cpt = ft_put_s(lst, cpt);
	else if (c == 'p')
		cpt = ft_put_p(lst, cpt);
	else if (c == 'd')
		cpt = ft_put_d(lst, cpt);
	else if (c == 'i')
		cpt = ft_put_i(lst, cpt);
	else if (c == 'u')
		cpt = ft_put_u(lst, cpt);
	else if (c == 'x')
		cpt = ft_put_x(lst, cpt);
	else if (c == 'X')
		cpt = ft_put_x_up(lst, cpt);
	else if (c == '%')
	{
		ft_putchar_fd('%', 1);
		cpt++;
	}
	return (cpt);
}

static int	put_res(va_list lst, const char *str, size_t i, int cpt)
{
	while (str[i])
	{
		while (str[i] != '%' && str[i])
		{
			ft_putchar_fd(str[i++], 1);
			cpt++;
		}
		if (str[i] && str[i + 1] && (str[i + 1] == 'c' || str[i + 1] == 's'
				|| str[i + 1] == 'p' || str[i + 1] == 'd' || str[i + 1] == 'i'
				|| str[i + 1] == 'u' || str[i + 1] == 'x' || str[i + 1] == 'X'
				|| str[i + 1] == '%'))
		{
			cpt = check_conv(lst, cpt, str[i + 1]);
			i += 2;
		}
		else if (str[i] && str[i] == '%')
			i++;
	}
	return (cpt);
}

int	ft_printf(const char *str, ...)
{
	va_list	lst;
	int		cpt;
	size_t	i;

	if (!str)
		return (-1);
	i = 0;
	cpt = 0;
	va_start(lst, str);
	cpt = put_res(lst, str, i, cpt);
	va_end(lst);
	return (cpt);
}
