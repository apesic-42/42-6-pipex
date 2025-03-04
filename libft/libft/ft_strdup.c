/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:21:28 by apesic            #+#    #+#             */
/*   Updated: 2024/11/25 15:53:48 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	size_t	si;
	size_t	i;
	char	*ma;

	si = ft_strlen(s);
	ma = malloc((int)si + 1);
	if (ma == NULL)
		return (NULL);
	i = 0;
	while (i < si)
	{
		ma[i] = s[i];
		i++;
	}
	ma[i] = '\0';
	return (ma);
}
/* 
 #include <string.h>
#include <stdio.h>

 int main (int c, char **v)
 {
	(void)c;
	(void)v;
	char *b = ft_strdup("x");

	printf("res2 : %s\n", b);
	free(b);
}  */