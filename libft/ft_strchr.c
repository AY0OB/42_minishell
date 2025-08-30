/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 22:44:47 by amairia           #+#    #+#             */
/*   Updated: 2025/07/27 22:44:48 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
