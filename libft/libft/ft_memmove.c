/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:49:14 by apesic            #+#    #+#             */
/*   Updated: 2024/11/14 12:06:09 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

static void	*ft_memcpy_right(void *dest, const void *src, size_t n)
{
	unsigned char	*s;
	unsigned char	*d;

	if (dest == 0 && src == 0)
		return (dest);
	s = (unsigned char *)src;
	d = (unsigned char *)dest;
	s += n - 1;
	d += n - 1;
	while (n--)
		*d-- = *s--;
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s = (const unsigned char *)src;

	d = (unsigned char *)dest;
	if (d < s)
		ft_memcpy(dest, src, n);
	else
		ft_memcpy_right(dest, src, n);
	return (dest);
}

// #include <string.h>
// int main (int c, char **v)
// {
//     (void)c;
//     (void)v;

//     char ok[7] = "okokok";
//     char ok2[7] = "okokok";
//     // char le[7] = "lelele";
//     // char *ok = v[1];
//     // char *le = v[2];
//     // char *ok2 = v[1];
//     // char *le2 = v[2];
//     memmove(ok, &ok[2], 4);
//     printf("%s\n", ok);
//     ft_memmove(ok2, &ok2[2], 4);
//     printf("%s\n", ok2);
// }

// #include <string.h>
// #include <stdio.h>
// int main (int c, char **v)
// {
//     (void)c;
//     (void)v;

// char *src = "thi\xffs i\xfas \0a g\xde\xadood \0nyan\0cat\0 !\r\n";
// int size = 33;
// char dst1[0xF0];
// char dst2[0xF0];

// memmove(dst1, src, size);
// printf("1 : %s\n", dst1);
// ft_memmove(dst2, src, size);
// printf("2 : %s\n", dst2);

// }
/* Errors in memmove:
Test 1:
	if (dest != ft_memmove(dest, "consectetur", 5))
		write(1, "dest's adress was not returned\n", 31);
	write(1, dest, 22);
Expected (cat -e test01.output):
conseipsum dolor sit a
Your result (cat -e user_output_test01):
orem ctetur^@olor sit a
Test 2:
	if (dest != ft_memmove(dest, "con\0sec\0\0te\0tur", 10))
		write(1, "dest's adress was not returned\n", 31);
	write(1, dest, 22);
Expected (cat -e test02.output):
con^@sec^@^@t dolor sit a
Your result (cat -e user_output_test02):
orem ipsum dolor sit a
Test 3:
	if (dest != ft_memmove(dest, src, 8))
		write(1, "dest's adress was not returned\n", 31);
	write(1, dest, 22);
Expected (cat -e test03.output):
lorem ipum dolor sit a
Your result (cat -e user_output_test03):
orem ipssum dolor sit  */
