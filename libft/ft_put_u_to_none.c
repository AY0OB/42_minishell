/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_u_to_none.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 22:44:12 by amairia           #+#    #+#             */
/*   Updated: 2025/07/27 22:44:16 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	nb_num(long int nb)
{
	size_t	cpt;

	if (nb >= 0)
		cpt = 1;
	else if (nb < 0)
		cpt = 2;
	while (nb / 10 != 0)
	{
		nb = nb / 10;
		cpt++;
	}
	return (cpt);
}

static char	*ft_itoa_unsigned(long int n)
{
	char		*res;
	long int	unit;
	size_t		cpt;
	long int	nb;

	nb = (long int)n;
	cpt = nb_num(nb);
	res = ft_calloc(cpt + 1, sizeof(char));
	if (!res)
		return (NULL);
	res[0] = '-';
	if (nb < 0)
		nb = -nb;
	else if (nb == 0)
		res[0] = '0';
	while (nb != 0)
	{
		cpt--;
		unit = nb % 10;
		res[cpt] = unit + '0';
		nb = nb / 10;
	}
	return (res);
}

int	ft_put_u(va_list lst, int cpt)
{
	unsigned int	content;
	char			*str;

	content = va_arg(lst, unsigned int);
	str = ft_itoa_unsigned(content);
	ft_putstr_fd(str, 1);
	cpt += ft_strlen(str);
	free(str);
	return (cpt);
}

int	ft_put_x(va_list lst, int cpt)
{
	unsigned int	content;

	content = va_arg(lst, unsigned int);
	cpt += conv_hexa(content, "0123456789abcdef");
	return (cpt);
}

int	ft_put_x_up(va_list lst, int cpt)
{
	unsigned int	content;

	content = va_arg(lst, unsigned int);
	cpt += conv_hexa(content, "0123456789ABCDEF");
	return (cpt);
}
