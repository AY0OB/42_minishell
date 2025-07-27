/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 22:43:38 by amairia           #+#    #+#             */
/*   Updated: 2025/07/27 22:43:38 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_ch;
	size_t			i;
	unsigned char	ch;

	ch = (unsigned char)c;
	s_ch = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (s_ch[i] == ch)
			return (s_ch + i);
		i++;
	}
	return (NULL);
}
