#include "libft.h"

int	ft_isprint(int c)
{
	if (c == 127 || (c >= 0 && c <= 31) || c <= 0 || c >= 127)
		return (0);
	else
		return (16384);
}
