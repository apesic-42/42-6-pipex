/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:23:36 by apesic            #+#    #+#             */
/*   Updated: 2024/11/11 15:06:19 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	c;
	size_t	d;
	char	*ma;

	c = 0;
	d = 0;
	if (!s1 || !s2)
		return (NULL);
	ma = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (ma == NULL)
		return (NULL);
	while (s1[c])
	{
		ma[c] = s1[c];
		c++;
	}
	while (s2[d])
	{
		ma[c + d] = s2[d];
		d++;
	}
	ma[c + d] = '\0';
	return (ma);
}

/* #include <stdio.h>

int	main(int c, char **v)
{
	(void)c;
	printf("res : %s", ft_strjoin(v[1], v[2]));
} */