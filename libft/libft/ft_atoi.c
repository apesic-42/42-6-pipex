/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:12:05 by apesic            #+#    #+#             */
/*   Updated: 2024/11/14 13:47:22 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

long	ft_atoi(const char *str)
{
	long	res;
	int		sign;
	int		i;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign *= -1;
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (2147483648);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
		if ((res > INT_MAX && sign == 1) || (res > (2147483648) && sign == -1))
			return (2147483648);
	}
	if (str[i])
		return (2147483648);
	return (res * sign);
}

//  #include <stdlib.h>
// #include <stdio.h>

// int main (int c, char **v)
// {
// 	(void)c;
// 	(void)v;
// 	printf("%d\n", atoi("\t\n\r\v\f  469 \n"));
// 	printf("%d\n", ft_atoi("\t\n\r\v\f  469 \n"));
// 	//ft_atoi("\t\n\r\v\f  469 \n")
// }
/* #include <stdlib.h>
int main(int ac, char **av)
{
	(void) ac;
	int a = atoi(av[1]);
	//ft_atoi(av[1]);
	return 0;
} */
