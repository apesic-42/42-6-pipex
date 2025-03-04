/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:46:40 by apesic            #+#    #+#             */
/*   Updated: 2024/12/02 10:24:39 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	treat_percent(const char *n, va_list args)
{
	int	len;

	len = 0;
	if (*n == 'c')
		len += percent_c(va_arg(args, int));
	if (*n == 's')
		len += percent_s(va_arg(args, char *));
	if (*n == 'd')
		len += percent_d(va_arg(args, int));
	if (*n == 'i')
		len += percent_i(va_arg(args, int));
	if (*n == 'u')
		len += percent_u(va_arg(args, long long));
	if (*n == 'p')
		len += percent_p(va_arg(args, unsigned long long));
	if (*n == 'x')
		len += percent_x(va_arg(args, unsigned int));
	if (*n == 'X')
		len += percent_xx(va_arg(args, unsigned int));
	if (*n == '%')
		len += percent_percent();
	return (len);
}

static int	treat(const char *n, va_list args, int len)
{
	while (*n)
	{
		if (ft_strncmp(n, "%", 1) == 0)
		{
			len += treat_percent(n + 1, args);
			n++;
		}
		else
		{
			write(1, n, 1);
			len++;
		}
		n++;
	}
	return (len);
}

int	ft_printf(const char *n, ...)
{
	va_list	args;
	int		len;

	len = 0;
	va_start(args, n);
	if (!n)
		return (-1);
	len = treat(n, args, len);
	va_end(args);
	return (len);
}

/* #include <limits.h>
int	main(int argc, char **argv)
{
	int a, b;
	(void)argc;
	(void)argv;

	// Test pour caractère, chaîne, entier signé, entier non signé,
	// a = printf("Vrai : ok%sr   %ck, int : %d, int : %i, uint : %u, ptr : %p,
	//		hex : %x, HEX : %X, pourcent : %%\n", "pp", 'o', -15, 456368713,
	//		3000000000U, (void *)&ptr, 255, 255);
	//b = ft_printf("Faux : ok%sr   %ck, int : %d, int : %i, uint : %u, ptr : %p,
	//		hex : %x, HEX : %X, pourcent : %%\n", "pp", 'o', -15, 456368713,
	//		3000000000U, (void *)&ptr, 255, 255);
 

 	a =    printf(" NULL %s NULL \n", NULL);
	b = ft_printf(" NULL %s NULL \n", NULL);
	printf("printf retourné : %d\nft_printf retourné : %d\n", a, b);
} */