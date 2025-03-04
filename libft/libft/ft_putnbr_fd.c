/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:43:49 by apesic            #+#    #+#             */
/*   Updated: 2024/11/14 12:06:17 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>
#include "libft.h"

static int	treat_before(long m, int fd)
{
	if (m < 0)
	{
		write(fd, "-", 1);
		m *= -1;
	}
	return (m);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	a;
	long	m;

	if (fd < 0)
		return ;
	if (n == INT_MIN)
		ft_putstr_fd("-2147483648", fd);
	else
	{
		m = n;
		m = treat_before(m, fd);
		if (m >= 10)
		{
			ft_putnbr_fd(m / 10, fd);
		}
		a = m % 10 + 48;
		ft_putchar_fd(a, fd);
	}
}
/* 
#include <stdlib.h>
int main (int c, char **v)
{
	(void)c;
	ft_putnbr_fd(atoi(&v[1][0]), 1);
}  
// erreur avec fd negatif pour la francinette
*/