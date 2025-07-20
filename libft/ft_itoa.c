#include "libft.h"

static size_t	nb_num(int nb)
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

char	*ft_itoa(int n)
{
	char		*res;
	int			unit;
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
