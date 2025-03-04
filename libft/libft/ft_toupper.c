/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:41:49 by apesic            #+#    #+#             */
/*   Updated: 2024/11/07 14:34:10 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c -= 32);
	return (c);
}

/* #include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int c, char **v)
{
	(void)c;
	printf("%d\n", toupper(v[1][0]));
	printf("%d\n", ft_toupper(v[1][0]));
} */