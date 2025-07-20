#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*s_int;
	size_t			i;
	unsigned char	ch;

	if (!s)
		return (NULL);
	ch = (unsigned char)c;
	s_int = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		s_int[i] = ch;
		i++;
	}
	return (s);
}
