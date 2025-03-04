/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:24:08 by apesic            #+#    #+#             */
/*   Updated: 2024/11/07 11:41:57 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}

// #include <stdio.h>
// #include <ctype.h>
// int main(int c, char** v)
// {
//     (void)c;
//     (void)v;
//     printf("vrai : %d et ft: %d\n", isprint(127), ft_isprint(127));
// }
