/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablgarc <pablgarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:49:43 by pablgarc          #+#    #+#             */
/*   Updated: 2024/09/22 13:09:08 by pablgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	size_t	i;
	char	*dest2;
	char	*src2;

	dest2 = (char *) dest;
	src2 = (char *) src;
	i = 0;
	if (!dest && !src)
		return (0);
	if (src < dest)
	{
		i = 1;
		while (i < (len + 1))
		{
			dest2[len - i] = src2[len - i];
			i++;
		}
	}
	else
	{
		while (i++ < len)
			(*dest2++) = (*src2++);
	}
	return (dest);
}
