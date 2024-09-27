/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablgarc <pablgarc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 23:05:23 by pablgarc          #+#    #+#             */
/*   Updated: 2022/09/30 17:32:05 by pablgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*dest;
	unsigned int	i;
	unsigned int	j;

	if (!s1 || !s2)
		return (0);
	dest = (char *)malloc(sizeof(char) * (ft_strlen((char *)s1)
				+ ft_strlen((char*)s2) + 1));
	if (!dest)
		return (0);
	i = 0;
	j = 0;
	while (s1[i] != 0)
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2[j] != 0)
	{
		dest[i] = s2[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}
