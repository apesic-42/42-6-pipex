/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_hexa_ll.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:17:15 by apesic            #+#    #+#             */
/*   Updated: 2024/11/27 18:43:15 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	len_number(unsigned long long n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 16;
		i++;
	}
	return (i);
}

static int	in_hexa(unsigned long long i)
{
	static char	hexa[17] = "0123456789abcdef";

	return (hexa[i]);
}

char	*ft_itoa_hexa_ll(unsigned long long num)
{
	char	*str;
	size_t	len;

	len = len_number(num);
	str = (char *)ft_calloc(sizeof(char), (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[len] = in_hexa(num % 16);
		num /= 16;
	}
	return (str);
}
