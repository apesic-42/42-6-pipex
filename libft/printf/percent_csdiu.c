/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   percent_csdiu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:17:33 by apesic            #+#    #+#             */
/*   Updated: 2024/11/28 16:05:25 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	percent_c(int arg)
{
	write(1, &arg, 1);
	return (1);
}

int	percent_s(char *arg)
{
	int	i;

	i = 0;
	if (arg == NULL)
		arg = "(null)";
	while (arg[i] != '\0')
	{
		ft_putchar_fd(arg[i], 1);
		i++;
	}
	return (i);
}

int	percent_d(int arg)
{
	char	*nb;
	int		len;

	nb = ft_itoa(arg);
	ft_putstr_fd(nb, 1);
	len = ft_strlen(nb);
	free(nb);
	return (len);
}

int	percent_i(int arg)
{
	char	*nb;
	int		len;

	nb = ft_itoa(arg);
	ft_putstr_fd(nb, 1);
	len = ft_strlen(nb);
	free(nb);
	return (len);
}

int	percent_u(long long arg)
{
	int		len;

	len = ft_putnumber_u(arg);
	return (len);
}
