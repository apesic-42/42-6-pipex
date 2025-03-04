/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:39:35 by apesic            #+#    #+#             */
/*   Updated: 2024/11/07 14:35:28 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s1)[i] > ((unsigned char *)s2)[i])
			return (1);
		if (((unsigned char *)s1)[i] < ((unsigned char *)s2)[i])
			return (-1);
		i++;
	}
	return (0);
}

/* #include <string.h>
#include <stdio.h>

int	main(int c, char **v)
{
	(void)c;
	(void)v;
	char arr1[5] = {'a', 'b', '\0', 'd', 'l'};
	char arr2[5] = {'a', 'b', '\0', 'd', 'x'};


	printf("%d\n", memcmp(arr1, arr2, 5));

	printf("%d\n", ft_memcmp(arr1, arr2, 5));
	// pas la meme sortit mais on s'en fout, le man :
	//The memcmp() function returns an integer less than, equal to,
		or greater than zero if the first n  bytes
	//   of s1 is found, respectively, to be less than, to match,
		or be greater than the first n bytes of s2.

	// For  a nonzero return value,
	//	the sign is determined by the sign of the
		// difference between the first pair
	//   of bytes (interpreted as unsigned char) that differ in s1 and s2.

}  */