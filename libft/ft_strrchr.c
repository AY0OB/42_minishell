#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	if (c == 0)
		return ((char *)(s + i));
	c = c % 128;
	while (i >= 0)
		if ((int)c == s[i--])
			return ((char *)(s + i + 1));
	return (NULL);
}
