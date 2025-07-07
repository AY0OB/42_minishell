#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	res;

	res = ft_strlen(src);
	i = 0;
	while (i < size && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	if (size > res)
	{
		dst[i] = 0;
	}
	else
		dst[i - 1] = 0;
	return (res);
}
