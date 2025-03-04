/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:56:36 by apesic            #+#    #+#             */
/*   Updated: 2024/11/13 14:38:46 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] != (unsigned char)c)
	{
		if (s[i] == '\0')
			return ((char *) 0);
		i++;
	}
	return ((char *) &s[i]);
}

//#include <stdio.h>

/* int main (int c, char **v)
{
 	char	*ok = "teste";
	char	e;
	e = '\0'; 
	(void)c;
	(void)v;
	ft_strchr("teste", '\0');
	// printf("%ld\n", ft_strchr(v[1], v[2][0]) - v[1]);
 }
 */
