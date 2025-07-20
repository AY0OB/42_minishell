#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_ch;
	unsigned char	*src_ch;
	size_t			i;

	if (!dest)
		return (NULL);
	dest_ch = (unsigned char *)dest;
	src_ch = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		dest_ch[i] = src_ch[i];
		i++;
	}
	return (dest);
}
