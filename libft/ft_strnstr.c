/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablgarc <pablgarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 12:08:55 by pablgarc          #+#    #+#             */
/*   Updated: 2024/06/07 00:09:42 by pablgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t		i;
	size_t		j;
	const char	*str2;

	str2 = str;
	i = 0;
	if (to_find[0] == '\0')
		return ((char *) str2);
	if (len == 0)
		return (0);
	while (str2[i])
	{
		j = 0;
		while (str2[i + j] == to_find[j] && (i + j) < len)
		{
			if (str[i + j] == '\0' && to_find[j] == '\0')
				return ((char *) &str2[i]);
			j++;
		}
		if (to_find[j] == '\0')
			return ((char *) str2 + i);
		i++;
	}
	return (0);
}
