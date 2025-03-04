/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:45:03 by apesic            #+#    #+#             */
/*   Updated: 2024/11/14 12:06:44 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

static void	place_st(char *dst, const char *src, size_t siz)
{
	size_t	i;

	i = 0;
	while (i < siz - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

size_t	ft_strlcpy(char *dst, const char *src, size_t siz)
{
	size_t	size;

	if (siz == 0)
		return (ft_strlen(src));
	place_st(dst, src, siz);
	size = ft_strlen(src);
	return (size);
}

// #include <string.h>
// #include <stdio.h>
// #include <bsd/string.h>
// int main (int c, char **v)
// {
//     (void)c;

//     // char *ok = v[1];
//     // char *le = v[2];
//     // char *ok2 = v[1];
//     // char *le2 = v[2];
//     //ft_strlcpy(v[1], v[2], 2);
//     ft_strlcpy(v[1], "aaa", 0);
//     printf("f : %s\n", v[1]);

//     strlcpy(v[2], "aaa", 0);
//     printf("v : %s\n", v[2]);
// }
