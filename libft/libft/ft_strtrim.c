/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 09:51:43 by apesic            #+#    #+#             */
/*   Updated: 2024/11/11 15:08:00 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strtrim(char const *s1, char const *set)
{
	int		s;
	int		e;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	s = 0;
	e = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[s]) && s <= e)
		s++;
	if (s > e)
		return (ft_strdup(s1 + e + 1));
	while (ft_strchr(set, s1[e]) && e >= 0)
		e--;
	str = malloc(e - s + 2);
	if (!str)
		return (NULL);
	ft_strlcpy(str, &s1[s], e - s + 2);
	return (str);
}
/* #include <stdio.h>

int main(int c, char **v)
{
	(void)c;
	printf("res : %s\n", ft_strtrim(v[1], v[2]));
} */