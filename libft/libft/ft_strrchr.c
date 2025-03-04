/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:05:05 by apesic            #+#    #+#             */
/*   Updated: 2024/11/11 15:09:55 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// #include <stdio.h>

char	*ft_strrchr(const char *s, int c)
{
	int	ize;

	ize = ft_strlen(s);
	while (ize >= 0)
	{
		if (s[ize] == (char)c)
		{
			return ((char *)&s[ize]);
		}
		ize--;
	}
	return (NULL);
}

// int main (int c, char **ok)
// {
//     (void)c;
//     printf("%s, %c\n", ok[1], ok[2][0]);
// 	printf("%s\n", ft_strrchr(ok[1], ok[2][0]));
// }
