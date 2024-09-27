/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablgarc <pablgarc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:25:31 by pablgarc          #+#    #+#             */
/*   Updated: 2022/10/15 18:12:29 by pablgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_pos(int n)
{
	long long	n2;

	n2 = n;
	if (n < 0)
		return (n2 * -1);
	return (n2);
}

int	ft_intlen(int n)
{
	int			len;
	long long	n2;

	len = 1;
	n2 = ft_pos(n);
	while (n2 > 9)
	{
		n2 = n2 / 10;
		len++;
	}
	return (len);
}

void	ft_write(char *str, int len, int n)
{
	while (n > 9)
	{
		str[len] = (n % 10) + '0';
		n = n / 10;
		len--;
	}
	str[len] = n + '0';
}

char	*ft_itoa(int n)
{
	long long		n2;
	int				len;
	char			*str;

	n2 = ft_pos(n);
	len = ft_intlen(n);
	if (n == -2147483648)
		return (ft_strdup ("-2147483648"));
	if (n < 0)
	{
		str = malloc((len + 2) * sizeof(char));
		if (!str)
			return (0);
		len++;
		str[0] = '-';
	}
	else
	{
		str = malloc((len + 1) * sizeof(char));
		if (!str)
			return (0);
	}
	str[len--] = '\0';
	ft_write(str, len, n2);
	return (str);
}
