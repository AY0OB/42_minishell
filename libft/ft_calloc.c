#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;

	if (nmemb == 0 || size == 0)
	{
		res = malloc(1);
		ft_bzero(res, 1);
		return (res);
	}
	if (nmemb > 2147483647 || size > 2147483647 || nmemb * size > 2147483647)
		return (NULL);
	res = malloc(size * nmemb);
	if (!res)
		return (NULL);
	ft_bzero(res, size * nmemb);
	return (res);
}
