/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   percent_pxXpercent.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:16:54 by apesic            #+#    #+#             */
/*   Updated: 2024/12/04 17:51:02 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	percent_p(unsigned long long arg)
{
	char	*nb;
	int		len;

	if (arg == 0)
	{
		ft_putstr_fd("(nil)", 1);
		len = 5;
		return (len);
	}
	ft_putstr_fd("0x", 1);
	len = 2;
	nb = ft_itoa_hexa_ll(arg);
	ft_putstr_fd(nb, 1);
	len += ft_strlen(nb);
	free(nb);
	return (len);
}

int	percent_x(unsigned int arg)
{
	char	*nb;
	int		len;

	nb = ft_itoa_hexa(arg);
	ft_putstr_fd(nb, 1);
	len = ft_strlen(nb);
	free(nb);
	return (len);
}

int	percent_xx(unsigned int arg)
{
	char	*nb;
	int		len;

	nb = ft_itoa_hexa_upper(arg);
	ft_putstr_fd(nb, 1);
	len = ft_strlen(nb);
	free(nb);
	return (len);
}

int	percent_percent(void)
{
	write(1, &"%", 1);
	return (1);
}
