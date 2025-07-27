/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 22:43:42 by amairia           #+#    #+#             */
/*   Updated: 2025/07/27 22:43:42 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_ch;
	unsigned char	*s2_ch;

	if (!s1 || !s2)
		return (0);
	s1_ch = (unsigned char *)s1;
	s2_ch = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (s1_ch[i] != s2_ch[i])
			return (s1_ch[i] - s2_ch[i]);
		i++;
	}
	return (0);
}
