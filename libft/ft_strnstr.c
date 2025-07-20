#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	char	*res;
	size_t	litt_len;
	size_t	big_len;

	res = (char *)big;
	if (little[0] == 0)
		return (res);
	litt_len = ft_strlen(little);
	big_len = len;
	i = 0;
	while (i < len && big[i])
	{
		if (big[i] == little[0])
			if (ft_strncmp(big + i, little, litt_len) == 0
				&& big_len >= litt_len)
				return (res + i);
		i++;
		big_len--;
		if (big_len == 0)
			break ;
	}
	return (NULL);
}
