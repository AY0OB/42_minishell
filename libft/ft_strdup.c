#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*res;
	int		i;

	i = 0;
	while (src[i])
		i++;
	res = (char *)malloc(sizeof(char) * (i + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (src[i])
	{
		res[i] = src[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
