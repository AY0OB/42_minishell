#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int	c;

	if (fd < 0)
		return ;
	if (n < 0 && n != -2147483648)
	{
		n *= -1;
		write(fd, "-", 1);
	}
	else if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
	}
	if (n != -2147483648)
	{
		c = (n % 10) + '0';
		n = n / 10;
		if (n != 0)
			ft_putnbr_fd(n, fd);
		write(fd, &c, 1);
	}
}
