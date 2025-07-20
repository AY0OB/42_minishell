#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	ch;

	ch = (unsigned char)c;
	if (ch == 0)
	{
		return ((char *)(s + ft_strlen(s)));
	}
	i = 0;
	while (s[i])
		if (ch == s[i++])
			return ((char *)(s + i - 1));
	return (NULL);
}
