/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:33:13 by apesic            #+#    #+#             */
/*   Updated: 2024/11/07 14:34:38 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	u;
	unsigned char	o;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (i < n)
	{
		u = (unsigned char)s1[i];
		o = (unsigned char)s2[i];
		if (u != o)
			return (u - o);
		if (u == '\0')
			return (0);
		i++;
	}
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

// #include <string.h>

// #include <stdio.h>
// int	main(int c, char **v)
// {
// 	(void)c;
// 	(void)v;
// 	//printf("%d\n", strncmp(v[1], v[2], 4));
// 	// printf("%d\n", ft_strncmp(v[1], v[2], 4));

// 	printf("fa : %d\n", ft_strncmp("abcdef", "abc\375xx", 5));
// 	printf("vr : %d\n", strncmp("abcdef", "abc\375xx", 5));
// 	// "test\200", "test\0", 6
// }
