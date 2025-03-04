/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:55:19 by apesic            #+#    #+#             */
/*   Updated: 2024/11/04 14:55:21 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = c;
		i++;
	}
	return (s);
}

// #include <stdio.h>
// int main() {
//     char str[50] = "Bonjour, voici une chaîne de test pour memset.";
//     printf("Avant memset: %s\n", str);

//     ft_memset(str + 8, '*', 5);
//     printf("Après memset : %s\n", str);

//     return (0);
// }
