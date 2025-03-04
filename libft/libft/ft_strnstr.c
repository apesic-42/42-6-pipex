/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:05:53 by apesic            #+#    #+#             */
/*   Updated: 2024/11/06 16:11:10 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	y;

	i = 0;
	y = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (big[i] != '\0' && i < len)
	{
		while (big[i] == little[y] && i < len)
		{
			if (little[y + 1] == '\0')
				return ((char *)&big[i - y]);
			i++;
			y++;
		}
		i = i - y;
		y = 0;
		i++;
	}
	return (NULL);
}

/* #include <stdio.h>
#include <bsd/string.h>

int main (int c, char **v)
{
	(void)c;
	int a = 7;
	printf("%s\n", strnstr(v[1], v[2], a));
	printf("%s\n", ft_strnstr(v[1], v[2], a));
} */