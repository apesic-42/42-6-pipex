/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 09:29:41 by apesic            #+#    #+#             */
/*   Updated: 2024/11/14 12:05:54 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_number(int n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	num;
	size_t	len;
	size_t	neg;

	num = n;
	neg = 0;
	if (n < 0)
	{
		neg = 1;
		num *= -1;
	}
	len = len_number(num) + neg;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[len] = num % 10 + '0';
		num /= 10;
	}
	if (neg == 1)
		str[0] = '-';
	return (str);
}

// int	main (void)
//  {
//  	int	n = 0;
//  	char *str;

//  	printf("%s\n", str = ft_itoa(n));
//  	return (0);
// }
