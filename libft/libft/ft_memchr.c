/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:08:54 by apesic            #+#    #+#             */
/*   Updated: 2024/11/07 11:42:24 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == ((unsigned char)c))
			return ((void *)&(((unsigned char *)s)[i]));
		i++;
	}
	return (NULL);
}

/* #include <string.h>
#include <stdio.h>

int	main(int c, char **v)
{
	(void)c;
	char *res = memchr(v[1], 'a', 4);
	if (res == NULL)
		printf("null\n");
	printf("%c\n", *res);
} */