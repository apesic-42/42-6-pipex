/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnumber_u.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:29:27 by apesic            #+#    #+#             */
/*   Updated: 2024/11/28 17:29:43 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	powerf(int b)
{
	unsigned int	c;

	c = 1;
	while (b > 0)
	{
		c = c * 10;
		b = b - 1;
	}
	return (c);
}

int	ft_putnumber_u(int a)
{
	unsigned int	nu;
	int				var;
	int				i;
	int				en_attendant;
	unsigned int	n;

	n = (unsigned int)a;
	nu = (unsigned int)a;
	i = 0;
	while (nu >= 10)
	{
		nu = nu / 10;
		i = i + 1;
	}
	en_attendant = i;
	while (i > 0)
	{
		nu = n / powerf(i);
		var = nu + 48;
		write(1, &var, 1);
		n = n % powerf(i--);
	}
	nu = n + 48;
	write(1, &nu, 1);
	return (en_attendant + 1);
}
