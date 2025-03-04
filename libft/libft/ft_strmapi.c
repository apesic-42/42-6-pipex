/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:58:41 by apesic            #+#    #+#             */
/*   Updated: 2024/11/11 16:58:29 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ma;
	int		i;

	ma = (char *)malloc(ft_strlen(s) * sizeof(char) + 1);
	if (ma == NULL)
		return (ma);
	i = 0;
	while (s[i])
	{
		ma[i] = f(i, s[i]);
		i++;
	}
	ma[i] = '\0';
	return (ma);
}
/*
char	exemple(unsigned int ok, char le)
{
	(void)ok;
	return (char)(le - 32);
}
#include <stdio.h>

 int main (int c, char **v)
{
	(void)c;
	printf("ma : %s\n", ft_strmapi(v[1], exemple));
} */