#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_ch;
	unsigned char	*src_ch;
	size_t			i;

	if (!dest || !src)
		return (NULL);
	dest_ch = (unsigned char *)dest;
	src_ch = (unsigned char *)src;
	if (dest > src && src + n > dest)
	{
		i = n;
		while (i > 0)
		{
			i--;
			dest_ch[i] = src_ch[i];
		}
		return (dest);
	}
	i = 0;
	while (i < n)
	{
		dest_ch[i] = src_ch[i];
		i++;
	}
	return (dest);
}
