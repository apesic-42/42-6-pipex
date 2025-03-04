/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:14:46 by apesic            #+#    #+#             */
/*   Updated: 2024/11/07 15:15:06 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}

/* #include <stdio.h>
#include <string.h>
int main() {
    char str[50] = "Bonjour, voici une chaîne de test pour memset.";
	char str2[50] = "Bonjour, voici une chaîne de test pour memset.";
    printf("Avant bzero: %s\n", str);

    bzero(str + 8, 10);
	
    printf("Après bzero : %s\n", str);


	printf("Avant bzero2: %s\n", str2);

    ft_bzero(str2 + 8, 10);
	
    printf("Après bzero 2: %s\n", str2);

    return (0);
} */
