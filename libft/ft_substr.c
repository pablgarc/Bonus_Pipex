/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 21:52:02 by pablgarc          #+#    #+#             */
/*   Updated: 2023/10/28 23:18:15 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	j;
	size_t	l;

	l = ft_strlen(s);
	if (start > l)
		len = 0;
	else if ((len + start) > l)
		len = l - start;
	sub = (char *) malloc((len + 1));
	if (!sub || !s)
		return (0);
	i = 0;
	j = start;
	while (i < len && j < l)
	{
		sub[i] = s[j];
		i++;
		j++;
	}
	sub[i] = '\0';
	return (sub);
}
