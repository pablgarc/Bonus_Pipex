/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablgarc <pablgarc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 10:03:24 by pablgarc          #+#    #+#             */
/*   Updated: 2022/09/18 16:46:47 by pablgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s1;
	unsigned char	c1;
	size_t			i;

	s1 = (unsigned char *) s;
	c1 = (unsigned char) c;
	i = 0;
	while (i < n)
	{
		if (*s1 == c1)
			return ((void *)s1);
		s1++;
		i++;
	}
	return (0);
}
