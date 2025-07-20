#include "libft.h"

static char	*feed_res(char *res, char *s1, char const *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j])
		res[i++] = s2[j++];
	free(s1);
	return (res);
}

char	*ft_strjoin_free(char *s1, char const *s2)
{
	char	*res;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] || s2[j])
	{
		if (s1[i])
			i++;
		if (s2[j])
			j++;
	}
	res = ft_calloc(i + j + 1, sizeof(char));
	if (!res)
		return (NULL);
	return (feed_res(res, s1, s2));
}
